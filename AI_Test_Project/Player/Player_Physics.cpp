//
//  Player_Physics.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/29/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "Player.hpp"

double Player::getTurnRate(unit_vector* A, unit_vector* B)
{
    double angle = acos(((A->X * B->X) + (A->Y * B->Y) + (A->Z * B->Z)) / (sqrt((pow(A->X, 2) + pow(A->Y, 2) + pow(A->Z, 2))) * sqrt((pow(B->X, 2)) + pow(B->Y, 2)) + pow(B->Z, 2)));
    if (angle > this->Input_Console->getConfig().Max_Turn_Rate)
    {
        return 100000;     //this should never be allowed to occur hence high arbitrary number
    }else
    {
        return 0;   //temporary fix (this does not work!)
    }
}

unit_vector* connectCoords(Coordinate* A, Coordinate* B)
{
    vector* new_vector = (vector*)malloc(sizeof(vector));
    new_vector->X = A->X - B->X;
    new_vector->Y = A->Y - B->Y;
    new_vector->Z = 0;
    unit_vector* new_unit_vector = toUnitVector(new_vector);
    return new_unit_vector; //this returns a vector that can connect two given points as a unit vector
}

Coordinate* subCoordinates(Coordinate* A, Coordinate* B)
{
    Coordinate* new_Coordinate = (Coordinate*)malloc(sizeof(Coordinate));
    new_Coordinate->X = A->X - B->X;
    new_Coordinate->Y = A->Y - B->Y;        //this just returns the difference between two coordinates
    return new_Coordinate;
}

Coordinate* addCoordinates(Coordinate* A, Coordinate* B)
{
    Coordinate* new_coord = createCoordinate();
    new_coord->X = A->X + B->X;
    new_coord->Y = A->Y + B->Y;
    return new_coord;
}

double Player::getTimeAdded(double Lost_work, double distance_traveled)
{
    //new_pos = last_pos + current_velocity(t) + force(t^2)
    //distance_traveled = 0 + current_velocity(t) + force(t^2)
    //0 = -distance_traveled + current_velocity(t) + force(t^2)
    //below will be quadratic equation for above
    //-B +/- sqrt(B^2 - 4AC)/2A
    //not used in this implementation
    return 1;
    
}

double Player::getWork(Coordinate* checked_dist, vector* wind)
{
    //the distance is from origin (0,0)
    //unit_vector* unit_wind = toUnitVector(wind)
    double meters_traveled = this->getDistance(checked_dist, &this->Player_data->Player_position); //not optimal technically
    //double velocity_X = this->Player_data->current_velocity * this->Player_data->travel_direction->X;
    //double velocity_Y = this->Player_data->current_velocity * this->Player_data->travel_direction->Y;
    //double velocity_Z = this->Player_data->current_velocity * this->Player_data->travel_direction->Z;
    
    double Force_X = this->Player_data->wind_vector->X;   //these might need tweaking from Wing Area
    double Force_Y = this->Player_data->wind_vector->Y;
    double Force_Z = this->Player_data->wind_vector->Z;
    double* Forces = (double*)malloc(sizeof(double) * 3); //to hold each dir's forces
    Forces[0] = Force_X;
    Forces[1] = Force_Y;
    Forces[2] = Force_Z;
    double lost_thrust = getLostWork(Forces);
    return lost_thrust;   //work lost from turbulance
}

double Player::getLostWork(double* array)
{
    //the array format is [0] = X, [1] = Y, [2] = Z
    double X = array[0];
    double Y = array[1];
    double Z = array[2];
    double delta_work = 0;  //positive is good
    
    double player_X = this->Player_data->travel_direction->X * this->Player_data->current_velocity;
    double player_Y = this->Player_data->travel_direction->Y * this->Player_data->current_velocity;
    double player_Z = this->Player_data->travel_direction->Z * this->Player_data->current_velocity;
    
    if(abs(player_X) > abs(X))
    {
        //magnitude of wind force is less than magnitude of thrust
        if(player_X * X > 0)
        {
            //same sign. helps the plane
            delta_work += X;
        }else
        {
            //different signs
            delta_work -= X;
        }
    }else
    {
        if(player_X * X > 0)
        {
            //same direction, the wind is greater than the travel work
            delta_work -= abs(X) - abs(player_X);
        }else
        {
            delta_work -= X;
            //different directions, magnitude is greater than travel work
        }
        //wind hurts the plane somehow
    }
    
    //do the same for Y
    if(abs(player_Y) > abs(Y))
    {
        //magnitude of wind force is less than magnitude of thrust
        if(player_Y * Y > 0)
        {
            //same sign. helps the plane
            delta_work += Y;
        }else
        {
            //different signs
            delta_work -= Y;
        }
    }else
    {
        if(Y * player_Y > 0)
        {
            //same direction, the wind is greater than the travel work
            delta_work -= abs(Y) - abs(player_Y);
        }else
        {
            delta_work -= Y;
            //different directions, magnitude is greater than travel work
        }
        //wind hurts the plane somehow
    }
    
    //do the same for Z
    if(abs(player_Z) > abs(Z))
    {
        //magnitude of wind force is less than magnitude of thrust
        if(player_Z * Z > 0)
        {
            //same sign. helps the plane
            delta_work += Z;
        }else
        {
            //different signs
            delta_work -= Z;
        }
    }else
    {
        if(Z * player_Z > 0)
        {
            //same direction, the wind is greater than the travel work
            delta_work -= abs(Z) - abs(player_Z);
        }else
        {
            delta_work -= Z;
            //different directions, magnitude is greater than travel work
        }
        //wind hurts the plane somehow
    }
    return delta_work;
}
/*
double Player::getForce(int wind_velocity)
{
    double Force = (pow(this->used_config.Wind_Unit * wind_velocity, 2) * this->used_config.Pressure_Const * this->used_config.Wing_Area * this->used_config.Drag_Coefficient);
    if(wind_velocity < 0)
    {
        Force = Force * -1;
    }
    return Force;
}*/ //this is fo rforce on STATIONARY objects -_-

/*double Player::getForce(int wind_velocity)
{
    
}*/

unit_vector* toUnitVector(vector* A)
{
    double magnitude = abs(A->X) + abs(A->Y) + abs(A->Z);
    unit_vector* result = (unit_vector*)malloc(sizeof(unit_vector));
    result->X = A->X / magnitude;
    result->Y = A->Y / magnitude;
    result->Z = A->Z / magnitude;
    return result;
}


