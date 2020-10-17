//
//  Player.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 9/22/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

struct vector
{
    int X : 8;
    int Y : 8;
    int Z : 8;
    //This means 8 bits used for each direction, since it is pulled from a 8 bit RGB value.
};

struct Coordinate
{
    int X;
    int Y;
};

struct Player_data
{
    vector* wind_vector;
    Coordinate* Player_position;
    Coordinate* Player_Destination;
};

struct Coordinate_node
{
    Coordinate* Coordinate;
    node* next_node;        //this is a linked list that will be stored per-player
}

struct Coordinate_head
{
    int length;
    node* next_node;        //this will be used to store the list of coordinates the plane has reached
                            //Used by the output handler later.
}

class Player
{
    Player_data* Player_data;
    int distance_to_destination;    //Instead of calculating it every time, this will be an easier lookup
                                    //The rest of the analysis for cost will be done at each node
                                    //With the results being calculated by the Output_handler
    Coordinate_head* Route;
    Output_handler* Output_route; //This will be a class in Route_Constructor.hpp
    Input_handler* Input_Console; //This will contain the map files and update sensors
    
public:
    Player_data getPlayerData(); //This retrieves a copy of the current data
    void updateData();          //Uses the Input Handler to update position, vector, distance, etc.
};


#endif /* Player_h */
