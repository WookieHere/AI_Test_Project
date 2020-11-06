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
    Destination->X = 10000;
    Destination->Y = 10000;
    Input_handler Input_Console = Input_handler(Origin, Destination, 400, "USA_TM.ppm");
    Output_handler Output = Output_handler();
    
    double* rand_array = getRandomDoubleArray(-10000, 10000, 6);
    Player test_player = Player(&Input_Console, &Output);
    
    Player_head* Player_list = (Player_head*)malloc(sizeof(Player_head));
    Player_list->length = 0;
    
    Player_node* temp = createNodePlayer();
    Player_list->next_node = temp;
    Player* temp_player;
    for(int i = 0; i < 500; i++)
    {
        temp_player = (Player*)malloc(sizeof(Player));
        rand_array = getRandomDoubleArray(-10000, 10000, 6);
        *temp_player = Player(&Input_Console, &Output);
        temp_player->manGenetics(rand_array);
        Player_list->length++;
        temp->ranked_player = temp_player;
        temp_player->updateData();
        temp_player->travel();
        temp->next_node = createNodePlayer();
        temp = temp->next_node;
        temp_player = NULL;
    }
    
    rand_array[0] = 0;
    rand_array[1] = 1;
    rand_array[2] = 1;
    rand_array[3] = 0;
    rand_array[4] = 0;
    rand_array[5] = 0;
    
    test_player.manGenetics(rand_array);
    test_player.updateData();
    test_player.travel();
    return 0;
}
