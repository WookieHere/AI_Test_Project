//
//  Unit_Testing.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/16/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Unit_Testing.hpp"

void print_mesh(Cost_mesh* used_mesh)
{
    
    for(int i = 0; i < used_mesh->y_width; i++)
    {
        printf("|");
        for(int j = 0; j < used_mesh->x_width; j++)
        {
            print_data(get_node(used_mesh, j, i)->data);
            printf("|");
        }
        printf("\n");
    }
}

void print_data(data* used_data)
{
    printf("%d,%d", used_data->x, used_data->y);
}
