//
//  Input_Handler.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Input_Handler_hpp
#define Input_Handler_hpp
#include <stdio.h>

struct Config
{
    FILE* heightmap_img;
    //some other stuff to be filled in later
};

struct Range_tuple
{
    struct Coordinate* A;
    struct Coordinate* B;   //This means from point A to point B (in a row/col) the derivitive avg is the data
    int orientation;        //row/col selector
    double derivitive;
};

struct Range_node
{
    Range_tuple* Range;
    Range_node* next_node;
};

struct Range_head
{
    int length;
    Range_node* next_node;
};

class Input_handler
{
    Config* User_config;
    struct Coordinate* Destination_Coord;
    struct Coordinate* Player_Origin;
    struct Coordinate* resolution;  //pixels in image as X/Y
    double scale;   //This is the pixels/meter type scale
    Range_head* Range_list; //this defines ranges of derivitives
    
public:
    Input_handler(Coordinate*);
    struct Coordinate* getCoordinate(class Player*);  //Like an update position. Mostly a placeholder
    struct Coordinate* getDestination();
    struct Coordinate* getOrigin();
    struct vector* getVector(Coordinate* coord);
};

#endif /* Input_Handler_hpp */
