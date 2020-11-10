//
//  Input_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//
#include <stdlib.h>
#include "Input_Handler.hpp"
#include "Linked_List_Handler.hpp"
#include "Random_Generator.hpp"
#include "Player.hpp"
#include "Output_Handler.hpp"

Input_handler::Input_handler(Coordinate* Origin, Coordinate* Destination, Output_handler* Output, const char* filename)
{
    this->User_config = (Config*)malloc(sizeof(Config));
    this->Output = Output;
    this->Player_Origin = Origin;
    this->Destination_Coord = Destination;
    this->generation_count = 0;
    this->User_config->heightmap_img = NULL;
    this->User_config->turbulence_map = filename;
    this->User_config->generation_size = 20;
    this->User_config->generation_end_count = 200;
    this->User_config->x_size = 9;     //reference frame dimensions (try to make it an odd number)
    this->User_config->y_size = 9;
    this->User_config->roughness = 2;       //2 meters per node
    this->User_config->Avg_Thrust = 252000;     //DEFINITELY a placeholder. avg thrust for a 747 Boeing (newtons)
    this->User_config->Minimum_Velocity = 294.98;    //minimum velocity in m/s
    this->User_config->Wind_Unit = .7874;    //m/s per 1 unit of wind vector (37/(127) * (1000/60))
    this->User_config->Wing_Area = 541.2;   //meters^2 for Boeing 747
    this->User_config->Pressure_Const = .613;   //P = .613V^2 where V is wind velocity
    this->User_config->Drag_Coefficient = .031; //no unit, C_o in equations of Boeing 747
    this->User_config->Max_Turn_Rate = .07;    //radians
    this->User_config->Plane_mass = 333747;
}

Input_handler::~Input_handler()
{
    /*just have to deallocate the User Config*/
    this->User_config->heightmap_img = NULL;
    this->User_config->turbulence_map = NULL;
    free(this->User_config);
}



Coordinate Input_handler::getDestination()
{
    return *Destination_Coord;
}

Config Input_handler::getConfig()
{
    return *this->User_config;
}

Coordinate Input_handler::getOrigin()
{
    return *this->Player_Origin;
}

int Input_handler::loop()
{
    if(this->generation_count == 0)
    {
        Player_head* Player_list = (Player_head*)malloc(sizeof(Player_head));
        Player_node* temp = createNodePlayer();
        Player_list->next_node = temp;
        Player* temp_player;
        double* rand_array = (double*)malloc(sizeof(Genetics)/sizeof(double));
        for(int i = 0; i < this->User_config->generation_size; i++)
        {
            temp_player = (Player*)malloc(sizeof(Player));
            rand_array = getRandomDoubleArray(-10000, 10000, 6);
            *temp_player = Player(this, Output);
            temp_player->manGenetics(rand_array);
            Player_list->length++;
            temp->ranked_player = temp_player;
            temp_player->updateData();
            temp_player->travel();
            temp->next_node = createNodePlayer();
            temp = temp->next_node;
            temp_player = NULL; //makes the first generation
        }
        this->generation_count = this->generation_count + 1;
    }else if(this->generation_count < this->User_config->generation_end_count)
    {
        Player_head* new_players = this->Output->getNewPlayers();
        Player_node* traversal_node = new_players->next_node;
        for(int i = 0; i < new_players->length; i++)
        {
            traversal_node->ranked_player->updateData();
            traversal_node->ranked_player->travel();
        }
        this->generation_count = this->generation_count + 1;
    }
    if(this->generation_count < this->User_config->generation_end_count)
    {
        this->loop();
    }
    return 0;
    
    
}
