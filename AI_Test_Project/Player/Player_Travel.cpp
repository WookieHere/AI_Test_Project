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
#define     COST_INPUT_NUM     8


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
    double layer_2_cost = 0;
    total_cost += this->Player_data->Player_genes->time_weight * input[3];
    total_cost += this->Player_data->Player_genes->travel_weight * input[0];
    total_cost += this->Player_data->Player_genes->work_weight * input[2];
    total_cost += this->Player_data->Player_genes->turning_rate * input[4];
    total_cost += this->Player_data->Player_genes->distance_weight * input[1];
    
    //layer 2
    layer_2_cost += this->Player_data->Player_genes->key_2 * input[5];
    layer_2_cost += this->Player_data->Player_genes->distance_2 * input[6];
    layer_2_cost += this->Player_data->Player_genes->velocity_2 * input[7];
    total_cost += layer_2_cost * this->Player_data->Player_genes->layer_2;
    
    return total_cost;
}

double Player::modifyCost(mesh_node* current_node)
{
    //genetics are already loaded
    Coordinate new_loc = {0,0};
    Coordinate current_location = this->Player_data->Player_position;
    Coordinate destination = this->Player_data->Player_Destination;
    //just for readability those coordinates are set.
    this->Player_data->wind_vector = this->Input_Console->getVector(&current_location);
    
    new_loc.X = ((current_node->data->Coord->X - (this->used_config.x_size/2)) * this->used_config.roughness) + current_location.X;
    new_loc.Y = ((current_node->data->Coord->Y - (this->used_config.y_size/2)) * this->used_config.roughness) + current_location.Y;
    //define new location
    
    if(new_loc.X == 0 && new_loc.Y == 0)
    {
        return INFINITY;
    }
    
    double distance_traveled = getDistance(&current_location, &new_loc);
    double distance_delta = (getDistance(&current_location, &destination) - getDistance(&new_loc, &destination)); //the -1 is so that the program will select for a higher values as being a good thing
    
    unit_vector* new_direction = connectCoords(&current_location, &new_loc);
    double velocity_delta = this->getWork(&new_loc, this->Player_data->wind_vector, new_direction);
    
    
    
    double time_taken = this->getTimeAdded(distance_traveled);

    this->time_register[0] = time_taken;    //this stores the time in a temp register
    
    if(velocity_delta < 0)
    {
        this->fuel_register[0] = time_taken * velocity_delta * this->used_config.Plane_mass;
    }else
    {
        this->fuel_register[0] = 0;
    }
    
    double turn_rate = this->getTurnRate(new_direction, this->Player_data->travel_direction);
    
    double key_change_delta = this->getKeyChanges(new_loc);
    //key_change_delta *= velocity_delta;
    
    double* cost_input_array = (double*)malloc(sizeof(double) * COST_INPUT_NUM);
    cost_input_array[0] = distance_traveled;
    cost_input_array[1] = distance_delta;
    //cost_input_array[2] = fuel_register[0];
    cost_input_array[2] = 1;
    cost_input_array[3] = time_register[0];
    cost_input_array[4] = turn_rate;
    cost_input_array[5] = key_change_delta;
    cost_input_array[6] = distance_delta;
    cost_input_array[7] = velocity_delta;
    
    double Node_Cost = interactGenetics(cost_input_array);
    current_node->data->Cost = Node_Cost;

    free(cost_input_array);
    cost_input_array = NULL;
    free(new_direction);
    new_direction = NULL;
    
    return Node_Cost;
    //this function interacts with the genetics and simulates plane flight to
    //generate a cost for decision making
}

mesh_node* Player::costMeshAssign(Cost_mesh* mesh)
{
    mesh_node* returned_node = mesh->origin;
    mesh_node* column_holder = mesh->origin;
    mesh_node* traversal_node = mesh->origin;
    //Coordinate temp_coord = {0,0};
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
    //free(column_holder);
    //free(traversal_node);
    //free(returned_node);
    //column_holder = NULL;
    //traversal_node = NULL;
    this->time_taken += this->time_register[1];
    this->fuel_used += this->fuel_register[1];
    return returned_node;
}

void Player::generateReferenceFrame()
{
    Coordinate old_pos = this->Player_data->Player_position;
    this->reference_frame = create_cost_mesh(this->used_config.x_size, this->used_config.y_size);
    
    mesh_node* new_position_node = this->costMeshAssign(this->reference_frame); //this will assign a cost to each node in the mesh
    //that also returns a mesh node of the new node to go to
    this->Player_data->Player_position.X = ((new_position_node->data->Coord->X - (this->used_config.x_size/2)) * this->used_config.roughness) + Player_data->Player_position.X;
    this->Player_data->Player_position.Y = ((new_position_node->data->Coord->Y - (this->used_config.y_size/2)) * this->used_config.roughness) + Player_data->Player_position.Y;
    //the above sets the new position of the player
    this->Player_data->travel_direction = connectCoords(&old_pos, &this->Player_data->Player_position);
    //sets the new travel direction
    
    addToRoute(this->Player_data->Player_position);
    //this adds the new position to the route
    
    this->distance_to_destination = getDistance(&this->Player_data->Player_position, &this->Player_data->Player_Destination);
    this->dist_to_key = this->Input_Console->getDistKeyFrame(&this->Player_data->Player_position, &this->Player_data->Player_position);
    
    //free(new_position_node);
    //new_position_node = NULL;
    freeCostMesh(this->reference_frame);
    
}

void Player::travel()
{
    int i = 0;
    Coordinate origin = this->Player_data->Player_position;
    
    double max_turn_distance = sqrt((.5) * (pow(this->used_config.x_size * this->used_config.roughness, 2) + pow(this->used_config.y_size * this->used_config.roughness, 2)));
    
    //that's the max distance traveled per turn
    double original_rect = (this->Player_data->Player_Destination.X - origin.X) * (this->Player_data->Player_Destination.Y - origin.Y);
    double original_dist = getDistance(&this->Player_data->Player_Destination, &origin);
    //the area of the rectangle containing the origin and destination
    
    while(this->distance_to_destination > 10)
    {
        generateReferenceFrame();
        i++;
        //printf("%d = i\n", i);
        if(this->distance_to_destination > (original_dist * 2))
        {
            //to make sure the AI is moving in the right direction
            
            this->time_taken = INFINITY;
            this->freeRoute();
            printf("Particle was killed\n");
            break;
        }else if(i > (original_rect/2)/max_turn_distance)
        {
             //this is to make sure the AI is at least moving
             //the time taken part is to select against these at all costs
             this->time_taken = INFINITY;
             this->freeRoute();
             printf("Particle was killed\n");
             break;
        }
    }
    if(this->time_taken != INFINITY)
    {
        printf("Breakpoint active\n");
        //breakpoint
    }
    /*
    printf("Player_X: %f\n", this->Player_data->Player_position.X);
    printf("Player_Y: %f\n", this->Player_data->Player_position.Y);
    printf("Turn no. %d\n", i);
    printf("------------------------\n");
     */
    this->Output_route->addToRoster(this);
}
