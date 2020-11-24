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
    //Cost_mesh* test_mesh = create_cost_mesh(10, 10);
    //print_mesh(test_mesh);
    //freeCostMesh(test_mesh);
    //print_mesh(test_mesh);
    
    Coordinate* Origin = (Coordinate*)malloc(sizeof(Coordinate));
    Coordinate* Destination = (Coordinate*)malloc(sizeof(Coordinate));
    Origin->X = 0;
    Origin->Y = 0;
    Destination->X = 1000;
    Destination->Y = 1000;
    Player_head* Player_list = (Player_head*)malloc(sizeof(Player_head));
    Output_handler Output = Output_handler(Player_list);
    Input_handler Input_Console = Input_handler(Origin, Destination, &Output, "Test.ppm");
    Input_Console.setConfig("Test_Config.txt");
    
    double* rand_array = getRandomDoubleArray(-10, 10, 6);
    Player test_player = Player(&Input_Console, &Output);
    
    rand_array[0] = 0;
    rand_array[1] = -1;
    rand_array[2] = -1;
    rand_array[3] = 0;
    rand_array[4] = 0;
    rand_array[5] = 0;
    
    //crossTest();
    //test_player.manGenetics(rand_array);
    //test_player.updateData();
    //test_player.travel();
    /*
    Player* A = new Player(&Input_Console, &Output);
    Player* B = new Player(&Input_Console, &Output);
    A->manGenetics(getRandomDoubleArray(-10, 10, 6));
    //A->manGenetics(getRandomDoubleArray(-10, 10, 6));
    crossTest(A, B);
    */
    
    int i = 0;
    int finished_flag = Input_Console.loop();
    Player_head* last_gen = Output.player_roster;
    while(finished_flag == 0)
    {
        i++;
        //Output.setRoster(last_gen);
        last_gen = Output.player_roster;
        finished_flag = Input_Console.loop();
    }
    last_gen = Output.player_roster;
    //Player_head* last_gen = Input_Console.loop();
    
    return 0;
}

//add an addToRoute function
//unit test addToRoute, Mutate.
//last gen is coming up with a length of 0. investigate this
//double check roster rotation and deletion working.
