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
    int new_size = 0;
    
    Player_node* temp = this->post_breeding_players->next_node;
    Player_node* trail = this->post_breeding_players->next_node;
    for(int l = 0; l < this->post_breeding_players->length; l++)
    {
        trail = temp;
        temp = temp->next_node;
        free(trail);
        trail = NULL;
    }//clears the post breeding players
    this->post_breeding_players->length = 0;
    
    
    for(int i = 0; i < this->player_roster->length; i++)
    {
        if((this->player_roster->length - i) > getRandom2RN(0, this->player_roster->length))
        {
            this->addToRoster(traversal_node->ranked_player, this->post_breeding_players);
            new_size++;
            //this will breed a new player on a 2RN of it's position
        }
        traversal_node = traversal_node->next_node;
    }//post breeding players is now partially filled
    
    traversal_node = this->player_roster->next_node;
    for(int k = 0; k < this->player_roster->length - new_size; k++)
    {
        this->addToRoster(new Player(traversal_node->ranked_player->Input_Console, this), this->post_breeding_players);
        //this pads the end of the roster with new players
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
        }//these mutate a player 5% of the time
        traversal_node = traversal_node->next_node->next_node;
    }
    
    /*if(this->player_roster->length > this->User_config->generation_size || this->post_breeding_players->length > this->User_config->generation_size)
    {
        printf("ERROR: roster size increased mid loop\n");
    }*/
}//this function generates the post_breeding_players list

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
                temp = gene_A.time_weight;
                gene_A.time_weight = gene_B.time_weight;
                gene_B.time_weight = temp;
                break;
                
            case 1:
                temp = gene_A.travel_weight;
                gene_A.travel_weight = gene_B.travel_weight;
                gene_B.travel_weight = temp;
                break;
                
            case 2:
                temp = gene_A.distance_weight;
                gene_A.distance_weight = gene_B.distance_weight;
                gene_B.distance_weight = temp;
                break;
                
            case 3:
                temp = gene_A.work_weight;
                gene_A.work_weight = gene_B.work_weight;
                gene_B.work_weight = temp;
                break;
                
            case 4:
                temp = gene_A.turning_rate;
                gene_A.turning_rate = gene_B.turning_rate;
                gene_B.turning_rate = temp;
                break;
                
            case 5:
                temp = gene_A.change_constant;
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
    double* new_genes = getRandomDoubleArray(-100, 100, genes_to_switch);

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
