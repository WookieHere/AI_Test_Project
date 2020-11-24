//
//  Player.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Player.hpp"
#include "Linked_List_Handler.hpp"
#include "Random_Generator.hpp"


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
    this->used_config = this->Input_Console->getConfig();
    this->Player_data->Player_position = this->Input_Console->getOrigin();
    this->Player_data->Player_Destination = this->Input_Console->getDestination();
    
    this->Player_data->travel_direction = createUnitVector();
    this->Player_data->travel_direction->X = 0;
    this->Player_data->travel_direction->Y = 0;
    this->Player_data->travel_direction->Z = 0;
    
    this->reference_frame = (Cost_mesh*)malloc(sizeof(Cost_mesh));
    this->reference_frame->x_width = this->used_config.x_size;
    this->reference_frame->y_width = this->used_config.y_size;
    
    this->Route = (Coordinate_head*)malloc(sizeof(Coordinate_head));
    this->Route->length = 0;
    this->Route->next_node = createNodeCoordinate();
    this->Route->next_node->Coordinate = &this->Player_data->Player_position;//needs to be fixed
    
    //this->average_velocity = 0;
    this->Player_data->current_velocity = this->used_config.Minimum_Velocity;
    //this->Player_data->Player_position = Origin;
    this->time_taken = 0;
    this->time_register = (double*)malloc(sizeof(double) * 2);
    this->Player_data->fuel_use = 0;
    this->fuel_register = (double*)malloc(sizeof(double) * 2);
           //for updateData();
    
    this->Player_data->wind_vector = createVector();
    this->distance_to_destination = 0;      //placeholder for updateData();
    this->Player_data->wind_vector = 0;     //for updateData();
    
    //set default values for genes
    //this->Player_data->Player_genes->accuracy_weight = 0;
    this->Player_data->Player_genes = (Genetics*)malloc(sizeof(Genetics));
    //this->Player_data->Player_genes->change_constant = 0;
    this->Player_data->Player_genes->distance_weight = 1;
    this->Player_data->Player_genes->time_weight = 1;
    this->Player_data->Player_genes->travel_weight = 1;
    this->Player_data->Player_genes->turning_rate = 1;
    this->Player_data->Player_genes->work_weight = 1;
    this->Player_data->Player_genes->velocity_2 = 1;
    this->Player_data->Player_genes->distance_2 = 1;
    this->Player_data->Player_genes->key_2 = 1;
    
    this->Route = (Coordinate_head*)malloc(sizeof(Coordinate_head));
    this->Route->next_node = (Coordinate_node*)malloc(sizeof(Coordinate_node));
    this->Route->length = 1;
    this->Route->next_node->Coordinate = (Coordinate*)malloc(sizeof(Coordinate));
    *this->Route->next_node->Coordinate = this->Input_Console->getOrigin();
    
    this->dist_to_key = this->Input_Console->getDistKeyFrame(&this->Player_data->Player_position, &this->Player_data->Player_position);
    
}
Player::~Player()
{
    //printf("Deallocating Player:\n");
    /*deallocate the coordinates route*/
    freeRoute();
    
    free(this->Route);
    this->Route = NULL;
    /*deallocate time register*/
    free(this->time_register);
    this->time_register = NULL;
    /*deallocate fuel register*/
    free(this->fuel_register);
    this->fuel_register = NULL;
    /*deallocate the player's genes*/
    //freeCostMesh(this->reference_frame);
    //the cost mesh is deallocated after every allocation
    //do NOT free the input/output handlers
    if(this->Player_data != NULL)
    {
        free(this->Player_data->Player_genes);
        this->Player_data->Player_genes = NULL;
        free(this->Player_data->travel_direction);
        this->Player_data->travel_direction = NULL;
        free(this->Player_data->wind_vector);
        this->Player_data->wind_vector = NULL;
        free(this->Player_data);
        this->Player_data = NULL;
    }
    /*need to deallocate player data*/
}

double getDistance(Coordinate* A, Coordinate* B)
{
    double result = sqrt(pow(A->X - B->X, 2) + pow(A->Y - B->Y, 2));
    return result;
}

void Player::updateData()
{
    this->Player_data->Player_position = this->Input_Console->getOrigin();
    freeRoute();
    this->dist_to_key = this->Input_Console->getDistKeyFrame(&this->Player_data->Player_position, &this->Player_data->Player_position);
    
    this->used_config = this->Input_Console->getConfig();
    this->distance_to_destination = getDistance(&this->Player_data->Player_position, &this->Player_data->Player_Destination);
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
    for(int i = 0; i < 6; i++)
    {
        if(abs(input_array[i]) < 1)
        {
            input_array[i] += getRandomDouble(-100, 100);
        }
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

Coordinate_head* Player::getRoute()
{
    return this->Route;
}

double Player::getTimeTaken()
{
    return this->time_taken;
}

double Player::getFuelUsed()
{
    return this->fuel_used;
}

void Player::replaceGenes(Genetics new_genes)
{
    *this->Player_data->Player_genes = new_genes;
}

void Player::freeRoute()
{
    if(Route != NULL)
    {
        Coordinate_node* temp = this->Route->next_node;
        Coordinate_node* trail = this->Route->next_node;
        for(int i = 0; i < this->Route->length; i++)
        {
            trail = temp;
            temp = temp->next_node;
            free(trail->Coordinate);
            trail = NULL;
        }
        this->Route->length = 0;
    }
}

void Player::addToRoute(Coordinate point)
{
    Coordinate_node* temp = (Coordinate_node*)malloc(sizeof(Coordinate_node));
    temp->Coordinate = (Coordinate*)malloc(sizeof(Coordinate));
    *temp->Coordinate = point;
    temp->next_node = this->Route->next_node;
    this->Route->next_node = temp;
    this->Route->length++;
}//this adds like a stack
