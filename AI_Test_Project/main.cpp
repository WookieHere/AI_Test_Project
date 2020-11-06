//
//  main.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 9/22/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <iostream>
#include "Mesh_Construction.hpp"
#include "Unit_Testing.hpp"
#include "Random_Generator.hpp"
#include "Linked_List_Handler.hpp"

int main(int argc, const char * argv[])
{
    Cost_mesh* test_mesh = create_cost_mesh(10, 10);
    print_mesh(test_mesh);
    
    Coordinate* Origin = (Coordinate*)malloc(sizeof(Coordinate));
    Coordinate* Destination = (Coordinate*)malloc(sizeof(Coordinate));
    Origin->X = 0;
    Origin->Y = 0;
    Destination->X = 1000;
    Destination->Y = 1000;
    Player_head* Player_list = (Player_head*)malloc(sizeof(Player_head));
    Output_handler Output = Output_handler(Player_list);
    Input_handler Input_Console = Input_handler(Origin, Destination, &Output, "USA_TM.ppm");
    
    
    double* rand_array = getRandomDoubleArray(-10000, 10000, 6);
    Player test_player = Player(&Input_Console, &Output);
    
    rand_array[0] = 0;
    rand_array[1] = 1;
    rand_array[2] = 1;
    rand_array[3] = 0;
    rand_array[4] = 0;
    rand_array[5] = 0;
    
    test_player.manGenetics(rand_array);
    test_player.updateData();
    test_player.travel();
    
    Input_Console.loop();
    
    return 0;
}
