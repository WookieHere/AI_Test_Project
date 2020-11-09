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
#define     COST_INPUT_NUM     5


double Player::interactGenetics(double* input)
{
    /*
     cost_input_array[0] = distance_traveled;
     cost_input_array[1] = distance_delta;
     cost_input_array[2] = Lost_work;
     cost_input_array[3] = time_taken;
     cost_input_array[4] = turn_rate;
     */
    //just to simplify later lines
    for(int i = 0; i < COST_INPUT_NUM; i++)
    {
        //printf("input[%d] = %f\n", i, input[i]);
    }
    
    double total_cost = 0;
    total_cost += this->Player_data->Player_genes->time_weight * input[3];
    total_cost += this->Player_data->Player_genes->travel_weight * input[0];
    total_cost += this->Player_data->Player_genes->work_weight * input[2];
    total_cost += this->Player_data->Player_genes->turning_rate * input[4];
    total_cost += this->Player_data->Player_genes->distance_weight * input[1];
    return total_cost;
}

double Player::modifyCost(mesh_node* current_node)
{
    //genetics are already loaded
    Coordinate new_loc = {0,0};
    Config parameters = this->Input_Console->getConfig();   //get config
    Coordinate* current_location = &this->Player_data->Player_position;
    Coordinate* destination = &this->Player_data->Player_Destination;
    this->Player_data->wind_vector = this->Input_Console->getVector(current_location);
    //this is to simplify code in later steps
    
    new_loc.X = ((current_node->data->Coord->X - (parameters.x_size/2)) * parameters.roughness) + current_location->X;
    new_loc.Y = ((current_node->data->Coord->Y - (parameters.y_size/2)) * parameters.roughness) + current_location->Y;
    //define new location
    
    
    
    double distance_traveled = getDistance(current_location, &new_loc);
    double distance_delta = (getDistance(current_location, destination) - getDistance(&new_loc, destination)); //the -1 is so that the program will select for a higher values as being a good thing
    double Lost_work = this->getWork(&new_loc, this->Player_data->wind_vector);   //divide by 10000?
    double time_taken = this->getTimeAdded(Lost_work, distance_traveled);

    this->time_register[0] = time_taken;    //this stores the time in a temp register
    this->fuel_register[0] = Lost_work;
    
    double turn_rate = this->getTurnRate(connectCoords(current_location, &new_loc), this->Player_data->travel_direction);
    double* cost_input_array = (double*)malloc(sizeof(double) * COST_INPUT_NUM);
    cost_input_array[0] = distance_traveled;
    cost_input_array[1] = distance_delta;
    cost_input_array[2] = Lost_work;
    cost_input_array[3] = time_taken;
    cost_input_array[4] = turn_rate;
    //int key_change = getKeyChanges(&new_loc, this->Player_data->Player_position);
    double Node_Cost = interactGenetics(cost_input_array);
    current_node->data->Cost = Node_Cost;

    free((double*)cost_input_array);
    return Node_Cost;
    //this function interacts with the genetics and simulates plane flight to
    //generate a cost for decision making
}

mesh_node* Player::costMeshAssign(Cost_mesh* mesh)
{
    mesh_node* column_holder = create_mesh_node();
    mesh_node* traversal_node = create_mesh_node();
    mesh_node* returned_node = create_mesh_node();
    returned_node = mesh->origin;
    column_holder = mesh->origin;
    traversal_node = mesh->origin;
    double prev_min = 50000000;
    double temp_double = 0;
    for(int i = 0; i < mesh->y_width; i++)
    {
        for(int j = 0; j < mesh->x_width; j++)
        {
            temp_double = this->modifyCost(traversal_node);
            if(temp_double <= prev_min)
            {
                prev_min = temp_double;
                returned_node = traversal_node;
                this->time_register[1] = this->time_register[0];
                this->fuel_register[1] = this->fuel_register[0];
            }
            
            traversal_node = traversal_node->east_coord;
        }//goes through a row left to right
        column_holder = column_holder->south_coord;
        traversal_node = column_holder;
    }
    this->time_taken += this->time_register[1];
    this->fuel_used += this->fuel_register[1];
    return returned_node;
}

void Player::generateReferenceFrame()
{
    Config parameters = this->Input_Console->getConfig();
    this->reference_frame = create_cost_mesh(parameters.x_size, parameters.y_size);
    mesh_node* new_position_node = this->costMeshAssign(reference_frame); //this will assign a cost to each node in the mesh
    this->Player_data->Player_position.X = ((new_position_node->data->Coord->X - (parameters.x_size/2)) * parameters.roughness) + Player_data->Player_position.X;
    this->Player_data->Player_position.Y = ((new_position_node->data->Coord->Y - (parameters.y_size/2)) * parameters.roughness) + Player_data->Player_position.Y;
    //the above sets the new position of the player
    Coordinate_node temp = {(Coordinate*)malloc(sizeof(Coordinate)), NULL};// = (Coordinate_node*)malloc(sizeof(Coordinate_node));
    *temp.Coordinate = this->Player_data->Player_position;
    temp.next_node = this->Route->next_node;
    this->Route->next_node = &temp;
    //this adds the new position to the route

    this->distance_to_destination = getDistance(&this->Player_data->Player_position, &this->Player_data->Player_Destination);
    freeCostMesh(reference_frame);
    
}

void Player::travel()
{
    int i = 0;
    while(this->distance_to_destination > 10)
    {
        generateReferenceFrame();
        
        i++;
        //printf("%d = i\n", i);
        if(i > 1000)
        {
            break;
        }
    }
    /*
    printf("Player_X: %f\n", this->Player_data->Player_position.X);
    printf("Player_Y: %f\n", this->Player_data->Player_position.Y);
    printf("Turn no. %d\n", i);
    printf("------------------------\n");
     */
    this->Output_route->addToRoster(this);
}
