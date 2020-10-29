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

int main(int argc, const char * argv[])
{
    Cost_mesh* test_mesh = create_cost_mesh(10, 10);
    print_mesh(test_mesh);
    
    Coordinate* Origin = (Coordinate*)malloc(sizeof(Coordinate));
    Coordinate* Destination = (Coordinate*)malloc(sizeof(Coordinate));
    Origin->X = 0;
    Origin->Y = 0;
    Destination->X = 100;
    Destination->Y = 100;
    Input_handler Input_Console = Input_handler(Origin, Destination, 400);
    Output_handler Output = Output_handler();
    
    Player test_player = Player(&Input_Console, &Output);
    test_player.updateData();
    test_player.travel();
    return 0;
}
