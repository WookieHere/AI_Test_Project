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
    double C = -1 * distance_traveled;
    double B = this->Player_data->current_velocity;
    //double C = this->used_config.Avg_Thrust + Lost_work;
    double A = Lost_work;

    double D =  ((-1 * B) + sqrt(pow(B, 2) - (4 * A * C)))/(2 * A);
    double E =  ((-1 * B) - sqrt(pow(B, 2) - (4 * A * C)))/(2 * A);
    if(D < 0 && E > 0)    //arbitrary to get rid of NaN's
    {
        //only D is negative
        return D;
    }else if(E < 0 && D < E)
    {
        //E is negative and of smaller magnitude
        return E;
    }else
    {
        //should be always negative. but it can default here
        return D;
    }
}

double Player::getWork(Coordinate* checked_dist, vector* wind)
{
    //the distance is from origin (0,0)
    //unit_vector* unit_wind = toUnitVector(wind)
    double meters_traveled = this->getDistance(checked_dist, &this->Player_data->Player_position); //not optimal technically
    //double velocity_X = this->Player_data->current_velocity * this->Player_data->travel_direction->X;
    //double velocity_Y = this->Player_data->current_velocity * this->Player_data->travel_direction->Y;
    //double velocity_Z = this->Player_data->current_velocity * this->Player_data->travel_direction->Z;
    double Force_Z = this->getForce(wind->Z);
    double Force_X = this->getForce(wind->X);   //these might need tweaking from Wing Area
    double Force_Y = this->getForce(wind->Y);
    double* Forces = (double*)malloc(sizeof(double) * 3); //to hold each dir's forces
    Forces[0] = Force_X;
    Forces[1] = Force_Y;
    Forces[2] = Force_Z;
    double lost_thrust = getLostWork(Forces, meters_traveled);
    return lost_thrust;   //work lost from turbulance
}

double Player::getLostWork(double* array, double meters_traveled)
{
    //the array format is [0] = X, [1] = Y, [2] = Z
    double lost_X = array[0] * meters_traveled;
    double lost_Y = array[1] * meters_traveled;
    double lost_Z = array[2] * meters_traveled;
    double delta_work = 0;  //positive is good
    
    double work_X = this->Player_data->travel_direction->X * this->used_config.Avg_Thrust * meters_traveled;
    double work_Y = this->Player_data->travel_direction->Y * this->used_config.Avg_Thrust * meters_traveled;
    double work_Z = this->Player_data->travel_direction->Z * this->used_config.Avg_Thrust * meters_traveled;
    
    if(abs(work_X) > abs(lost_X))
    {
        //magnitude of wind force is less than magnitude of thrust
        if(work_X * lost_X > 0)
        {
            //same sign. helps the plane
            delta_work += lost_X;
        }else
        {
            //different signs
            delta_work -= lost_X;
        }
    }else
    {
        if(lost_X * work_X > 0)
        {
            //same direction, the wind is greater than the travel work
            delta_work -= abs(lost_X) - abs(work_X);
        }else
        {
            delta_work -= lost_X;
            //different directions, magnitude is greater than travel work
        }
        //wind hurts the plane somehow
    }
    
    //do the same for Y
    if(abs(work_Y) > abs(lost_Y))
    {
        //magnitude of wind force is less than magnitude of thrust
        if(work_Y * lost_Y > 0)
        {
            //same sign. helps the plane
            delta_work += lost_Y;
        }else
        {
            //different signs
            delta_work -= lost_Y;
        }
    }else
    {
        if(lost_Y * work_Y > 0)
        {
            //same direction, the wind is greater than the travel work
            delta_work -= abs(lost_Y) - abs(work_Y);
        }else
        {
            delta_work -= lost_Y;
            //different directions, magnitude is greater than travel work
        }
        //wind hurts the plane somehow
    }
    
    //do the same for Z
    if(abs(work_Z) > abs(lost_Z))
    {
        //magnitude of wind force is less than magnitude of thrust
        if(work_Z * lost_Z > 0)
        {
            //same sign. helps the plane
            delta_work += lost_Z;
        }else
        {
            //different signs
            delta_work -= lost_Z;
        }
    }else
    {
        if(lost_Z * work_Z > 0)
        {
            //same direction, the wind is greater than the travel work
            delta_work -= abs(lost_Z) - abs(work_Z);
        }else
        {
            delta_work -= lost_Z;
            //different directions, magnitude is greater than travel work
        }
        //wind hurts the plane somehow
    }
    return delta_work;
}

double Player::getForce(int wind_velocity)
{
    double Force = (pow(this->used_config.Wind_Unit * wind_velocity, 2) * this->used_config.Pressure_Const * this->used_config.Wing_Area * this->used_config.Drag_Coefficient);
    if(wind_velocity < 0)
    {
        Force = Force * -1;
    }
    return Force;
}

unit_vector* toUnitVector(vector* A)
{
    double magnitude = abs(A->X) + abs(A->Y) + abs(A->Z);
    unit_vector* result = (unit_vector*)malloc(sizeof(unit_vector));
    result->X = A->X / magnitude;
    result->Y = A->Y / magnitude;
    result->Z = A->Z / magnitude;
    return result;
}


