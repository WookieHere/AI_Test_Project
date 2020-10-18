//
//  Player.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 9/22/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include "Route_Constructor.hpp"
#include "Input_Handler.hpp"
#include "Output_Handler.hpp"

struct vector
{
    int X : 8;
    int Y : 8;
    int Z : 8;
    //This means 8 bits used for each direction, since it is pulled from a 8 bit RGB value.
};
#include "Mesh_Construction.hpp"

struct Coordinate
{
    int X;
    int Y;
};



struct Genetics
{
    int time_weight;    //(work*time/distance + velocity/distance)^-1 AKA how long it took to get there
    int distance_weight;//change in distance to destination
    int height_weight;    //sin(change_in_height/distance)*Fuel_mileage_const
    int translation_weight; //(F-(F.dr))Fuel_mileage_const
    int accuracy_weight;    //guessed_work/real_work
    int turning_rate;       //last velocity vector vs current
};

struct Player_data
{
    Genetics* Player_genes;
    int current_velocity;   //running current velocity. dropping below a constant will result in fuel use
    int fuel_use;    //running total of force against vector
    vector* wind_vector;
    vector* travel_direction;
    Coordinate* Player_position;
    Coordinate* Player_Destination;
    //filled in with constants and everything later
};

struct Coordinate_node
{
    Coordinate* Coordinate;
    Coordinate_node* next_node;        //this is a linked list that will be stored per-player
};
struct Coordinate_head
{
    int length;
    Coordinate_node* next_node;        //this will be used to store the list of coordinates the plane has reached
                            //Used by the output handler later.
};

class Player
{
    struct Player_data* Player_data;
    int distance_to_destination;    //Instead of calculating it every time, this will be an easier lookup
    int average_velocity;
                                    //The rest of the analysis for cost will be done at each node
                                    //With the results being calculated by the Output_handler
    struct Cost_mesh* reference_frame;
    struct Coordinate_head* Route;
    class Output_handler* Output_route; //This will be a class in Route_Constructor.hpp
    class Input_handler* Input_Console; //This will contain the map files and update sensors
    
public:
    Player(Input_handler* Input, Output_handler* Output);       //there is only 1 Output handler/input handler in this implementation
    ~Player();
    struct Player_data getPlayerData(); //This retrieves a copy of the current data
    void updateData();          //Uses the Input Handler to update position, vector, distance, etc.
    
private:
    void generateReferenceFrame();
    
};


#endif /* Player_h */
