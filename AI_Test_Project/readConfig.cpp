//
//  readConfig.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/28/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include "Input_Handler.hpp"
#include "Player.hpp"
#include <string.h>
#define     MAX_LINE_SIZE   1000

void Input_handler::setConfig(const char* filename)
{
    FILE* config_file = fopen(filename, "r");
    char delims[] = " :{}=;\n/";
    char* token;
    char* temp;
    char file_buffer[1000];
    
    if(config_file == NULL)
    {
        printf("Error: config file could not be opened");
        exit(77);
    }
    
    while (fgets(file_buffer, MAX_LINE_SIZE, config_file))
    {
        token = strtok(file_buffer, delims);
        //do stuff
        while(token != NULL)
        {
                if( strcmp(token,"Input_file") == 0)
                {
                    token = strtok(NULL, delims);
                    this->heightmap_img = token;
                    //printf("%s\n", config->heightmap_img);
                }
                if( strcmp(token,"Output_file") == 0)
                {
                    token = strtok(NULL, delims);
                    this->turbulence_map = token;
                    //printf("%s\n", config->turbulence_map);
                }
                 if( strcmp(token,"x_size") == 0)
                {
                    token = strtok(NULL, delims);
                    this->x_size = atoi(token);
                    //printf("%d\n", config->x_size);
                }
                if( strcmp(token,"y_size") == 0)
                {
                    token = strtok(NULL, delims);
                    this->y_size = atoi(token);
                    //printf("%d\n", config->y_size);
                }
                 if( strcmp(token,"roughness") == 0)
                {
                    token = strtok(NULL, delims);
                    this->roughness = atof(token);
                    //printf("%f\n", config->roughness);
                }
                 if( strcmp(token,"Avg_Thrust") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Avg_Thrust = atof(token);
                    //printf("%f\n", config->Avg_Thrust);
                }
                 if( strcmp(token,"Minimum_Velocity") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Minimum_Velocity = atof(token);
                    //printf("%f\n", config->Minimum_Velocity);
                }
                if( strcmp(token,"Wind_Unit") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Wind_Unit = atof(token);
                    //printf("%f\n", config->Wind_Unit);
                }
                 if( strcmp(token,"Wing_Area") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Wing_Area = atof(token);
                    //printf("%f\n", config->Wing_Area);
                }
                 if( strcmp(token,"Pressure_Const") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Pressure_Const = atof(token);
                    //printf("%f\n", config->Pressure_Const);
                }
                 if( strcmp(token,"Drag_Coefficient") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Drag_Coefficient = atof(token);
                    //printf("%f\n", config->Drag_Coefficient);
                }
                 if( strcmp(token,"Max_Turn_Rate") == 0)
                {
                    token = strtok(NULL, delims);
                    this->Max_Turn_Rate = atof(token);
                    //printf("%f\n", config->Max_Turn_Rate);
                } 
                //printf("%s\n", token);                                                      

            token = strtok(NULL, delims);
        }
        //token is now the whole line
    }
    fclose(config_file);
}