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
#define     MAX_LINE_SIZE   1000

void Input_handler::setConfig(const char* filename)
{
    FILE* config_file = fopen(filename, "r");
    char* token;
    char max_name_size[64];
    
    if(config_file == NULL)
    {
        printf("Error: file could not be opened");
    }
    
    while (fgets(max_name_size, MAX_LINE_SIZE, config_file))
    {
        <#statements#>
    }
    
}
