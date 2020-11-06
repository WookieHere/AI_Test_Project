//
//  Input_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//
#include <stdlib.h>
#include "Input_Handler.hpp"
#include "Player.hpp"

Input_handler::Input_handler(Coordinate* Origin, Coordinate* Destination, double scale, const char* filename)
{
    this->User_config = (Config*)malloc(sizeof(Config));
    this->Player_Origin = Origin;
    this->Destination_Coord = Destination;
    this->User_config->heightmap_img = NULL;
    this->User_config->turbulence_map = filename;
    this->User_config->x_size = 9;     //reference frame dimensions (try to make it an odd number)
    this->User_config->y_size = 9;
    this->User_config->roughness = 2;       //2 meters per node
    this->User_config->Avg_Thrust = 252000;     //DEFINITELY a placeholder. avg thrust for a 747 Boeing (newtons)
    this->User_config->Minimum_Velocity = 294.98;    //minimum velocity in m/s
    this->User_config->Wind_Unit = .7874;    //m/s per 1 unit of wind vector (37/(127) * (1000/60))
    this->User_config->Wing_Area = 541.2;   //meters^2 for Boeing 747
    this->User_config->Pressure_Const = .613;   //P = .613V^2 where V is wind velocity
    this->User_config->Drag_Coefficient = .031; //no unit, C_o in equations of Boeing 747
    this->User_config->Max_Turn_Rate = .07;    //radians
}



Coordinate Input_handler::getDestination()
{
    return *Destination_Coord;
}

Config Input_handler::getConfig()
{
    return *this->User_config;
}

Coordinate Input_handler::getOrigin()
{
    return *this->Player_Origin;
}
