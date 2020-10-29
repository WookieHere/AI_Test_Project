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
    signed int X : 8;
    signed int Y : 8;
    signed int Z : 8;
    //This means 8 bits used for each direction, since it is pulled from a 8 bit RGB value.
    //the max value of a direction is (255-1)/2 * 37 (km/h)
};

struct unit_vector
{
    double X;
    double Y;
    double Z;
};
#include "Mesh_Construction.hpp"

struct Coordinate
{
    double X;
    double Y;
};

unit_vector* toUnitVector(vector* A);
Coordinate* subCoordinates(Coordinate* A, Coordinate* B);
Coordinate* addCoordinates(Coordinate* A, Coordinate* B);
unit_vector* connectCoords(Coordinate* A, Coordinate* B);
unit_vector* createUnitVector();
Coordinate* createCoordinate();
vector* createVector();


struct Genetics
{
    double time_weight;    //(work*time/distance + velocity/distance)^-1 AKA how long it took to get there
    double travel_weight;
    double distance_weight;//change in distance to destination
    double work_weight;    //sin(change_in_height/distance)*Fuel_mileage_const = height weight
    // translation_weight; //(F-(F.dr))Fuel_mileage_const
    //double accuracy_weight;    //guessed_work/real_work
    double turning_rate;       //last velocity vector vs current
    double change_constant;     //generate key coordinate ranges via input console
};

struct Agent_data
{
    Genetics* Player_genes;
    double current_velocity;   //running current velocity. dropping below a constant will result in fuel use
    double fuel_use;    //running total of force against vector
    vector* wind_vector;
    unit_vector* travel_direction;   //unit vector of player direction
    Coordinate Player_position;
    Coordinate Player_Destination;
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
    Agent_data* Player_data;
    double distance_to_destination;    //Instead of calculating it every time, this will be an easier lookup
    //double average_velocity;
                                    //The rest of the analysis for cost will be done at each node
                                    //With the results being calculated by the Output_handler
    double time_taken;  //in seconds
    struct Cost_mesh* reference_frame;
    struct Coordinate_head* Route;
    class Output_handler* Output_route; //This will be a class in Route_Constructor.hpp
    class Input_handler* Input_Console; //This will contain the map files and update sensors
    
public:
    Player(Input_handler* Input, Output_handler* Output);       //there is only 1 Output handler/input handler in this implementation
    //~Player();
    struct Player_data getPlayerData(); //This retrieves a copy of the current data
    void updateData();          //Uses the Input Handler to update position, vector, distance, etc.
    double getDistance(Coordinate*, Coordinate*); //outputs the distance between two coords
    //double getWork(Coordinate distance, vector* wind);
    void travel();
    void manGenetics(double*);
    
private:
    void generateReferenceFrame();
    double modifyCost(struct mesh_node*);
    double getWork(Coordinate*, vector*);
    //unit_vector* toUnitVector(vector*);
    double getForce(int, Config*);
    double getLostWork(double, double, Config*);
    //Coordinate* subCoordinates(Coordinate*, Coordinate*);
    double getTimeAdded(double, double);
    double getTurnRate(unit_vector*, unit_vector*);
    //unit_vector* connectCoords(Coordinate*, Coordinate*);
    double interactGenetics(double*);
    mesh_node* costMeshAssign(Cost_mesh* mesh);
};


#endif /* Player_h */
