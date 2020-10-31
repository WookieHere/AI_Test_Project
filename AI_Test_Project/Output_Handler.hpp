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
                                //(what image to use, color setup, etc.)
    Player_head* Player_list;
    
public:
    Player_head* rankPlayers(Player_head* head);    //This will rank players by best time etc.
    FILE* initPPM_file(const char* output_file, int width, int height); //makes the ppm file header
    void drawVector(FILE* output_file, Coordinate* A, Coordinate* B); //draw a line between two points
private:
    void crossOver(Player*, Player*);
    int getFitness(Player*);    //a low fitness is considered good in this algorithm
    
};


#endif /* Output_Handler_hpp */
