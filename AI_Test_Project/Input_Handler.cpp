//
//  Input_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//
#include <stdlib.h>
#include "Input_Handler.hpp"

Input_handler::Input_handler(Coordinate* Destination)
{
    this->User_config = NULL;
    this->Destination_Coord = Destination;
}

Coordinate* Input_handler::getDestination()
{
    return Destination_Coord;
}

vector* Input_handler::getVector(Coordinate* coord)
{
    //This will scan an image found in the config for teh RGB value at that pixel...
    return NULL;
}
