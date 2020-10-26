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
#define XSIZE   9
#define YSIZE   9
#define MRANGE  2       //2 meters per node

unit_vector* toUnitVector(vector* A)
{
    double magnitude = abs(A->X) + abs(A->Y) + abs(A->Z);
    unit_vector* result = (unit_vector*)malloc(sizeof(unit_vector));
    result->X = A->X / magnitude;
    result->Y = A->Y / magnitude;
    result->Z = A->Z / magnitude;
    return result;
}

double Player::getWork(Coordinate distance, vector* wind)
{
    //the distance is from origin (0,0)
    unit_vector* wind_unit = toUnitVector(wind);
    double velocity_X = this->Player_data->current_velocity * this->Player_data->travel_direction->X;
    double velocity_Y = this->Player_data->current_velocity * this->Player_data->travel_direction->Y;
    double velocity_Z = this->Player_data->current_velocity * this->Player_data->travel_direction->Z;
}

void Player::modifyCost(mesh_node* current_node)
{
    //genetics are already loaded
    Coordinate new_loc;
    new_loc.X = (current_node->data->x * MRANGE) + Player_data->Player_position->X;
    new_loc.Y = (current_node->data->y * MRANGE) + Player_data->Player_position->Y;
    double distance_traveled = getDistance(*this->Player_data->Player_position, new_loc);
    
}

void Player::generateReferenceFrame()
{
    this->reference_frame = create_cost_mesh(XSIZE, YSIZE);
    doMesh(modifyCost, )
}
