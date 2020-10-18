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


class Input_handler
{
    Config* User_config;
    struct Coordinate* Destination_Coord;
    
public:
    Input_handler(Coordinate*);
    struct Coordinate* getCoordinate(class Player*);  //Like an update position. Mostly a placeholder
    struct Coordinate* getDestination();
    struct vector* getVector(Coordinate* coord);
};

#endif /* Input_Handler_hpp */
