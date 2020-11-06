//
//  Player_Training.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/31/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//
#include "Player.hpp"
#include "Output_Handler.hpp"
#include "Random_Generator.hpp"
#include "Player_Training.hpp"

void Output_handler::breedPlayers()
{
    Player_node* traversal_node = this->player_roster->next_node;
    for(int i = 0; i < this->player_roster->length; i++)
    {
        if((500 - i) > getRandom2RN(0, this->player_roster->length))
        {
            this->addToRoster(traversal_node->ranked_player, 1);    //the '1' is to place into the breeding roster.
        }
    }
    traversal_node = this->post_breeding_players->next_node;
    for(int j = 0; j < this->post_breeding_players->length; j += 2)
    {
        this->crossOver(traversal_node->ranked_player, traversal_node->next_node->ranked_player);
        if(getRandomInt(0, 100) > 95)
        {
            this->mutate(traversal_node->ranked_player);
        }
        if(getRandomInt(0, 100) > 95)
        {
            this->mutate(traversal_node->next_node->ranked_player);
        }
        traversal_node = traversal_node->next_node->next_node;
    }
}

void Output_handler::crossOver(Player* A, Player* B)
{
    Genetics gene_A = A->getGenetics();
    Genetics gene_B = B->getGenetics();
    
    int* combination_sequence = getRandomMatchup(0, sizeof(gene_A)/ sizeof(double));
    int genes_to_switch = getRandomInt(0, sizeof(gene_A)/ sizeof(double));
    int temp = 0;
    for(int i = 0; i < genes_to_switch; i++)
    {
        switch (combination_sequence[i])
        {
            case 0:
                gene_A.time_weight = temp;
                gene_A.time_weight = gene_B.time_weight;
                gene_B.time_weight = temp;
                break;
                
            case 1:
                gene_A.travel_weight = temp;
                gene_A.travel_weight = gene_B.travel_weight;
                gene_B.travel_weight = temp;
                break;
                
            case 2:
                gene_A.distance_weight = temp;
                gene_A.distance_weight = gene_B.distance_weight;
                gene_B.distance_weight = temp;
                break;
                
            case 3:
                gene_A.work_weight = temp;
                gene_A.work_weight = gene_B.work_weight;
                gene_B.work_weight = temp;
                break;
                
            case 4:
                gene_A.turning_rate = temp;
                gene_A.turning_rate = gene_B.turning_rate;
                gene_B.turning_rate = temp;
                break;
                
            case 5:
                gene_A.change_constant = temp;
                gene_A.change_constant = gene_B.change_constant;
                gene_B.change_constant = temp;
                break;
                
                
            default:
                break;
        }//sadly there is not a better way to do that.
    }
    A->replaceGenes(gene_A);
    B->replaceGenes(gene_B);
    //this gets the sequence of genes that are flipped
    //only a fraction of the top of the array contain the indicies to be flipped
}

void Output_handler::mutate(Player* player)
{
    Genetics gene_A = player->getGenetics();
    
    
    int* combination_sequence = getRandomMatchup(0, sizeof(gene_A)/ sizeof(double));
    int genes_to_switch = getRandomInt(0, sizeof(gene_A)/ sizeof(double));
    double* new_genes = getRandomDoubleArray(-1000, 1000, genes_to_switch);

    for(int i = 0; i < genes_to_switch; i++)
    {
        switch (combination_sequence[i])
        {
            case 0:
                gene_A.time_weight = new_genes[i];
                break;
                
            case 1:
                gene_A.travel_weight = new_genes[i];
                break;
                
            case 2:
                gene_A.distance_weight = new_genes[i];
                break;
                
            case 3:
                gene_A.work_weight = new_genes[i];
                break;
                
            case 4:
                gene_A.turning_rate = new_genes[i];
                break;
                
            case 5:
                gene_A.change_constant = new_genes[i];
                break;
                
                
            default:
                break;
        }//sadly there is not a better way to do that.
    }
    player->replaceGenes(gene_A);
}