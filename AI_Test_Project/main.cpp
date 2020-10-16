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
    
    
    return 0;
}
