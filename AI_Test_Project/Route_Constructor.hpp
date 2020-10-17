//
//  Route_Constructor.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 9/22/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Route_Constructor_hpp
#define Route_Constructor_hpp
#include "Mesh_Construction.hpp"
#include "Player.hpp"


struct Config
{
    FILE* heightmap_img;
    //some other stuff to be filled in later
};

struct Player_node
{
    Player* ranked_player;      //Might need to be a double pointer. Test later
    Player_node* next_node;
};

struct Player_head
{
    int length;
    Player_node* first_node;    //Linked list of players in order of best results
};

class Output_handler
{
    Coordinate_head* player_route;
    Config* User_config;        //This will be a struct for defining how the output is managed
                                //(what image to use, color setup, etc.)
    Player_head* Player_list;
    
    
public:
    Player_head* Rank_players(Player_head*);    //This will rank players by best time etc.
};

class Input_handler
{
    Config* User_config;
    
public:
    Coordinate getCoordinate(Player*);  //Like an update position. Mostly a placeholder
};


#endif /* Route_Constructor_h */
