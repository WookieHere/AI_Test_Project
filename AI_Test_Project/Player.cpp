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
#include "Linked_List_Handler.hpp"


Player::Player(Input_handler* Input, Output_handler* Output)
{
    //Coordinate* Origin = (Coordinate*)malloc(sizeof(Coordinate));
    this->Player_data = (Agent_data*)malloc(sizeof(Agent_data));
    this->Input_Console = Input;
    this->Output_route = Output;
    //Origin->X = 0;
    //Origin->Y = 0;
    //this->Player_data->Player_position = createCoordinate();
    //this->Player_data->Player_Destination = createCoordinate();
    this->Player_data->Player_position = this->Input_Console->getOrigin();
    this->Player_data->Player_Destination = this->Input_Console->getDestination();
    
    this->Player_data->travel_direction = createUnitVector();
    this->Player_data->travel_direction->X = 0;
    this->Player_data->travel_direction->Y = 0;
    this->Player_data->travel_direction->Z = 0;
    
    this->reference_frame = create_cost_mesh(this->Input_Console->getConfig().x_size, this->Input_Console->getConfig().y_size);
    this->reference_frame->x_width = this->Input_Console->getConfig().x_size;
    this->reference_frame->y_width = this->Input_Console->getConfig().y_size;
    
    this->Route = (Coordinate_head*)malloc(sizeof(Coordinate_head));
    this->Route->length = 0;
    this->Route->next_node = createNodeCoordinate();
    this->Route->next_node->Coordinate = &this->Player_data->Player_position;//needs to be fixed
    
    //this->average_velocity = 0;
    this->Player_data->current_velocity = 10000;
    //this->Player_data->Player_position = Origin;
    this->time_taken = 0;
    this->Player_data->fuel_use = 0;
           //for updateData();
    
    this->Player_data->wind_vector = createVector();
    this->distance_to_destination = 0;      //placeholder for updateData();
    this->Player_data->wind_vector = 0;     //for updateData();
    
    //set default values for genes
    //this->Player_data->Player_genes->accuracy_weight = 0;
    this->Player_data->Player_genes = (Genetics*)malloc(sizeof(Genetics));
    this->Player_data->Player_genes->change_constant = 0;
    this->Player_data->Player_genes->distance_weight = 1;
    this->Player_data->Player_genes->time_weight = 1;
    this->Player_data->Player_genes->travel_weight = 1;
    this->Player_data->Player_genes->turning_rate = 1;
    this->Player_data->Player_genes->work_weight = 1;
}

double Player::getDistance(Coordinate* A, Coordinate* B)
{
    double result = sqrt(pow(A->X - B->X, 2) + pow(A->Y - B->Y, 2));
    return result;
}

void Player::updateData()
{
    this->distance_to_destination = this->getDistance(&this->Player_data->Player_position, &this->Player_data->Player_Destination);
    this->Player_data->wind_vector = this->Input_Console->getVector(&this->Player_data->Player_position);
    //update current velocity
    //update fuel use
}

void Player::manGenetics(double* input_array)
{
    if(sizeof(*input_array)/sizeof(double) != 6)
    {
        input_array = (double*)realloc(input_array, sizeof(double) * 6);
    }
    Genetics new_genes =
    {
        input_array[0],
        input_array[1],
        input_array[2],
        input_array[3],
        input_array[4],
        input_array[5],
    };
    *this->Player_data->Player_genes = new_genes;
    /*
    double time_weight;    //(work*time/distance + velocity/distance)^-1 AKA how long it took to get there
    double travel_weight;
    double distance_weight;//change in distance to destination
    double work_weight;    //sin(change_in_height/distance)*Fuel_mileage_const = height weight
    // translation_weight; //(F-(F.dr))Fuel_mileage_const
    //double accuracy_weight;    //guessed_work/real_work
    double turning_rate;       //last velocity vector vs current
    double change_constant;     //generate key coordinate ranges via input console
    */
}

Genetics Player::getGenetics()
{
    return *this->Player_data->Player_genes;
}

