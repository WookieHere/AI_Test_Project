//
//  Output_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Output_Handler.hpp"
#include <stdio.h>

Output_handler::Output_handler(Player_head* head)
{
    this->player_roster = (Player_head*)malloc(sizeof(Player_head));
    this->player_roster->length = 0;
    this->post_breeding_players = (Player_head*)malloc(sizeof(Player_head));
    this->post_breeding_players->length = 0;
    this->User_config = (Config*)malloc(sizeof(Config));
    this->output_log = "output.log";
}
Output_handler::~Output_handler()
{
    /*deallocate the whole list of players in player head*/
    Player_node* traversal_node = (Player_node*)malloc(sizeof(Player_node));
    Player_node* temp = (Player_node*)malloc(sizeof(Player_node));
    traversal_node = this->player_roster->next_node;
    temp = this->player_roster->next_node;
    for(int i = 0; i < this->player_roster->length - 1; i++)
    {
        temp = traversal_node; //temporary holder
        traversal_node = traversal_node->next_node;
        free(temp->ranked_player);
        temp->next_node = NULL;
    }
    free(this->player_roster);
    this->player_roster = NULL;
    /*deallocate post breeding players*/
    traversal_node = this->post_breeding_players->next_node;
    temp = this->post_breeding_players->next_node;
    for(int i = 0; i < this->post_breeding_players->length; i++)
    {
        temp = traversal_node; //temporary holder
        traversal_node = traversal_node->next_node;
        free(temp->ranked_player);
        temp->next_node = NULL;
    }
    free(this->post_breeding_players);
    this->post_breeding_players = NULL;
    /*deallocate user config*/
    //free(this->User_config);  //this is not a pointer
}

void Output_handler::printPlayerRoute(Coordinate_head* Route)
{
    FILE* output_file = fopen(this->output_log, "rw");
    Coordinate_node* traversal_node = Route->next_node;
    if(output_file != NULL)
    {
        for(int i = 0; i < Route->length; i++)
        {
            fprintf(output_file, "%.3f,%.3f\n", traversal_node->Coordinate->X, traversal_node->Coordinate->Y);
            traversal_node = traversal_node->next_node;
        }
        fprintf(output_file, "\n\n");
    }else
    {
        //printf("Could not open output file\n");
    }
    
}
//structure for text file is:
//1 2
//2 3
//3 4

//1 2
//...   (where the number pairs are coordinates

void Output_handler::printRoutes()
{
    Player_node* traversal_node = this->player_roster->next_node;
    for(int i = 0; i < this->player_roster->length; i++)
    {
        this->printPlayerRoute(traversal_node->ranked_player->getRoute());
        traversal_node = traversal_node->next_node;
    }
}

bool Output_handler::addToRoster(Player* player)
{
    if(this->player_roster->length == 0)
    {
        this->player_roster->next_node = (Player_node*)malloc(sizeof(Player_node));
        this->player_roster->next_node->ranked_player = player;
        this->player_roster->length++;
        return 0;
    }
    Player_node* traversal_node = this->player_roster->next_node;
    for(int i = 0; i < this->player_roster->length; i++)
    {
        if(player->getTimeTaken() >= traversal_node->ranked_player->getTimeTaken())
        {
            traversal_node = traversal_node->next_node;
        }else
        {
            break;
        }
    }
    //traversal_node now points at place where player should be
    Player_node* new_node = (Player_node*)malloc(sizeof(Player_node));
    new_node->next_node = traversal_node->next_node;
    traversal_node->next_node = new_node;
    new_node->ranked_player = traversal_node->ranked_player;
    traversal_node->ranked_player = player;
    this->player_roster->length++;
    //places the player into it's correct position in ranking based on time taken
    return 0;
}

bool Output_handler::addToRoster(Player* player, Player_head* head)
{
    Player_node* traversal_node = (Player_node*)malloc(sizeof(Player_node));
    
    if(head->length == 0)
    {
        head->next_node = (Player_node*)malloc(sizeof(Player_node));
        head->next_node->ranked_player = player;
        head->length++;
        return 0;
    }
    traversal_node = head->next_node;
    
    for(int i = 0; i < head->length - 1; i++)
    {
        if(player->getTimeTaken() >= traversal_node->ranked_player->getTimeTaken())
        {
            traversal_node = traversal_node->next_node;
        }else
        {
            break;  //for the intial roster this will not sort
        }
    }
    //traversal_node now points at place where player should be
    Player_node* new_node = (Player_node*)malloc(sizeof(Player_node));
    if(traversal_node->next_node != NULL)
    {
        new_node->next_node = traversal_node->next_node;
    }
    
    traversal_node->next_node = new_node;
    new_node->ranked_player = traversal_node->ranked_player;
    traversal_node->ranked_player = player;
    //places the player into it's correct position in ranking based on time taken
    return 0;
}
    
  
Player_head* Output_handler::getNewPlayers()
{
    this->printRoutes();
    this->breedPlayers();
    return this->post_breeding_players;
}
