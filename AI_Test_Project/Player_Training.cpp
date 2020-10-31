//
//  Player_Training.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/31/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//
#include "Player.hpp"
#include "Random_Generator.hpp"
#include "Player_Training.hpp"

void Output_Cross_Over(Player* A, Player* B)
{
    Genetics gene_A = A->getGenetics();
    Genetics gene_B = B->getGenetics();
    
    int* compination_sequence = getRandomMatchup(0, sizeof(gene_A)/ sizeof(double));
    //this gets the sequence of genes that are flipped
    //only a fraction of the top of the array contain the indicies to be flipped
    
}
