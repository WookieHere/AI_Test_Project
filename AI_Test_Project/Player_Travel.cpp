//
//  Player_Travel.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/26/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "Player.hpp"

unit_vector* toUnitVector(vector* A)
{
    double magnitude = abs(A->X) + abs(A->Y) + abs(A->Z);
    unit_vector* result = (unit_vector*)malloc(sizeof(unit_vector));
    result->X = A->X / magnitude;
    result->Y = A->Y / magnitude;
    result->Z = A->Z / magnitude;
    return result;
}

double Player::getForce(int wind_velocity, Config* parameters)
{
    double Force = pow(parameters->Wind_Unit * wind_velocity, 2) * parameters->Pressure_Const * parameters->Wing_Area * parameters->Drag_Coefficient;
    if(wind_velocity < 0)
    {
        Force = Force * -1;
    }
    return Force;
}

double Player::getLostWork(double Force, double meters_traveled, Config* parameters)
{
    double lost_work = (parameters->Avg_Thrust * meters_traveled) - (sin(acos((Force * meters_traveled) / (parameters->Avg_Thrust * meters_traveled))) * parameters->Avg_Thrust * meters_traveled);    //this is the value of thrust lost in work
    return lost_work;
}

double Player::getWork(Coordinate* checked_dist, vector* wind)
{
    //the distance is from origin (0,0)
    //unit_vector* unit_wind = toUnitVector(wind);
    Config parameters = this->Input_Console->getConfig();
    Coordinate origin = {static_cast<double>(parameters.x_size / 2), static_cast<double>(parameters.y_size / 2)};
    double meters_traveled = this->getDistance(*checked_dist, origin); //not optimal technically
    //double velocity_X = this->Player_data->current_velocity * this->Player_data->travel_direction->X;
    //double velocity_Y = this->Player_data->current_velocity * this->Player_data->travel_direction->Y;
    //double velocity_Z = this->Player_data->current_velocity * this->Player_data->travel_direction->Z;
    double Force_Z = this->getForce(wind->Z, &parameters);
    double Force_X = this->getForce(wind->X, &parameters);   //these might need tweaking from Wing Area
    double Force_Y = this->getForce(wind->Y, &parameters);
    double lost_thrust_Z = getLostWork(Force_Z, meters_traveled, &parameters);
    double lost_thrust_X = getLostWork(Force_X, meters_traveled, &parameters);
    double lost_thrust_Y = getLostWork(Force_Y, meters_traveled, &parameters);
    return lost_thrust_X + lost_thrust_Y + lost_thrust_Z;   //work lost from turbulance
}

double Player::getTimeAdded(double Lost_work, double distance_traveled)
{
    //new_pos = last_pos + current_velocity(t) + force(t^2)
    //distance_traveled = 0 + current_velocity(t) + force(t^2)
    //0 = -distance_traveled + current_velocity(t) + force(t^2)
    //below will be quadratic equation for above
    //-B +/- sqrt(B^2 + 4AC)/2A
    double D =  (((-1) * this->Player_data->current_velocity) + sqrt(pow(this->Player_data->current_velocity, 2) + (4 * (-1 * distance_traveled) * (Lost_work / distance_traveled))))/ (2 * (-1 * distance_traveled));
    double E =  (((-1) * this->Player_data->current_velocity) - sqrt(pow(this->Player_data->current_velocity, 2) + (4 * (-1 * distance_traveled) * (Lost_work / distance_traveled))))/ (2 * (-1 * distance_traveled));
    if(D > E)
    {
        return D;
    }else
    {
        return E;
    }
}

double Player::getTurnRate(unit_vector* A, unit_vector* B)
{
    double angle = acos(((A->X * B->X) + (A->Y * B->Y) + (A->Z * B->Z)) / (sqrt((pow(A->X, 2) + pow(A->Y, 2) + pow(A->Z, 2))) * sqrt((pow(B->X, 2)) + pow(B->Y, 2)) + pow(B->Z, 2)));
    if (angle > this->Input_Console->getConfig().Max_Turn_Rate)
    {
        return 1000000;     //this should never be allowed to occur hence high arbitrary number
    }else
    {
        return angle;
    }
}

void Player::modifyCost(mesh_node* current_node)
{
    //genetics are already loaded
    Coordinate new_loc;
    Config parameters = this->Input_Console->getConfig();
    new_loc.X = (current_node->data->Coord->X * parameters.roughness) + Player_data->Player_position->X;
    new_loc.Y = (current_node->data->Coord->Y * parameters.roughness) + Player_data->Player_position->Y;
    double distance_traveled = getDistance(*this->Player_data->Player_position, new_loc);
    double Lost_work = this->getWork(subCoordinates(this->Player_data->Player_position, &new_loc), this->Input_Console->getVector(&new_loc));
    double time_taken = this->getTimeAdded(Lost_work, distance_traveled);
    vector* direction_vector = (vector*)malloc(sizeof(vector));
    direction_vector->X = current_node->data->Coord->X * parameters.roughness;
    direction_vector->Y = current_node->data->Coord->Y * parameters.roughness;
    direction_vector->Z = 0;
    unit_vector* unit_dir = toUnitVector(direction_vector);
    //double turn_rate = this->getTurnRate(this->Player_data->travel_direction, subCoordinates(&new_loc, this->Player_data->travel_direction))
    
    
    
}

void Player::generateReferenceFrame()
{
    Config parameters = this->Input_Console->getConfig();
    this->reference_frame = create_cost_mesh(parameters.x_size, parameters.y_size);
    doMesh(this->modifyCost, reference_frame);  //this will assign a cost to each node in the mesh
}
