//
//  Output_Handler.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Output_Handler_hpp
#define Output_Handler_hpp
#include "Player.hpp"
#include "Input_Handler.hpp"
#include <stdlib.h>
#include <stdio.h>

struct Player_node
{
    Player* ranked_player;      //Might need to be a double pointer. Test later
    Player_node* next_node;
};

struct Player_head
{
    int length;
    Player_node* next_node;    //Linked list of players in order of best results
};

class Output_handler
{
    
    Player_head* player_roster;
    Config* User_config;        //This will be a struct for defining how the output is managed
    Player_head* post_breeding_players; //linked list of players for breeding
    const char* output_log;
    
public:
    Output_handler(Player_head* head);
    //~Output_handler();
    
    bool addToRoster(Player*);
    Player_head* getNewPlayers();   //to be called by the input handler
private:
    void printPlayerRoute(struct Coordinate_head*);    
    void printRoutes();
    void crossOver(Player*, Player*);
    void breedPlayers();
    bool addToRoster(Player*, Player_head*);
    void mutate(Player*);
};


#endif /* Output_Handler_hpp */
