//
//  Unit_Testing.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/16/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Unit_Testing_hpp
#define Unit_Testing_hpp

#include <stdio.h>
#include "Mesh_Construction.hpp"
#include "Player.hpp"

void print_mesh(Cost_mesh* used_mesh);
void print_data(data*);
void printGenetics(Player* A, const char* name);
void crossTest(Player* A, Player* B);

#endif /* Unit_Testing_hpp */
