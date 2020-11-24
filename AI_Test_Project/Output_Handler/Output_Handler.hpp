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
    
    
                                //(what image to use, color setup, etc.)
    Player_head* Player_list;

    Config* User_config;        //This will be a struct for defining how the output is managed
    
    const char* output_log;
    
public:
    Player_head* player_roster;     //current players
    Output_handler(Player_head* head);
    ~Output_handler();
    bool addToRoster(Player*);
    void crossOver(Player*, Player*);   //TEMPORARY in public for testing
    void rotateRoster();   //this sets the output to a new roster
    Player_head* getNewPlayers();   //to be called by the input handler
    void clearRoster(); //clears player roster
private:
    Player_head* post_breeding_players; //linked list of players for breeding
    void printPlayerRoute(struct Coordinate_head*);    
    void printRoutes();
    //void crossOver(Player*, Player*);
    void breedPlayers();
    bool addToRoster(Player*, Player_head*);
    void mutate(Player*);
};


#endif /* Output_Handler_hpp */
