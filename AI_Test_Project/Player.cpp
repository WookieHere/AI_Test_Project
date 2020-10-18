//
//  Player.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "Player.hpp"
#define LAUNCH_VELOCITY 100 //placeholder


Player::Player(Input_handler* Input, Output_handler* Output)
{
    Coordinate* Origin = (Coordinate*)malloc(sizeof(Coordinate));
    Origin->X = 0;
    Origin->Y = 0;
    this->average_velocity = 0;
    this->Player_data->current_velocity = LAUNCH_VELOCITY;
    this->Player_data->Player_position = Origin;
    this->Player_data->fuel_use = 0;
    this->Input_Console = Input;
    this->Output_route = Output;
    this->Player_data->Player_Destination = (Coordinate*)malloc(sizeof(Coordinate));    //for updateData();
    this->Player_data->travel_direction->X = 0;
    this->Player_data->travel_direction->Y = 0;
    this->Player_data->travel_direction->Z = 0;
    this->distance_to_destination = 0;      //placeholder for updateData();
    this->Player_data->wind_vector = 0;     //for updateData();
}

void Player::updateData()
{
    this->Player_data->Player_Destination = Input_Console->getDestination();
    this->distance_to_destination = sqrt(pow((double)this->Player_data->Player_Destination->X, 2) + pow((double)this->Player_data->Player_Destination->Y, 2));
    this->Player_data->wind_vector = this->Input_Console->getVector(Player_data->Player_position); //This will not work with current implementation (it will always check 0,0 at first)
    
}
