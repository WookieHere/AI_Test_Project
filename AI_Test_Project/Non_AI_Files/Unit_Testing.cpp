//
//  Unit_Testing.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/16/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Unit_Testing.hpp"
#include "Random_Generator.hpp"

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
    printf("%d,%d", (int)used_data->Coord->X, (int)used_data->Coord->Y);
}

void printGenetics(Player* A, const char* name)
{
    Genetics genes = A->getGenetics();
    printf("%s:\n", name);
    printf("time_weight: %f\n", genes.time_weight);
    printf("travel_weight: %f\n", genes.travel_weight);
    printf("distance_weight: %f\n", genes.distance_weight);
    printf("work_weight: %f\n", genes.work_weight);
    printf("turning_rate: %f\n", genes.turning_rate);
    printf("change_constant: %f\n", genes.key_2);
    printf("-------------------------");
}

void crossTest()
{
    Output_handler* Temp = new Output_handler(NULL);
    Coordinate Origin = {0,0};
    Coordinate Dest = {1000, 1000};
    Input_handler* temp_in = new Input_handler(&Origin, &Dest, Temp, "Test.ppm");
    Player* A = new Player(temp_in, Temp);
    Player* B = new Player(temp_in, Temp);
    double* rand_genes = getRandomDoubleArray(-100, 100, 6);
    A->manGenetics(rand_genes);
    printGenetics(A, "Player_A");
    printGenetics(B, "Player_B");
    Temp->crossOver(A, B);
    printGenetics(A, "new_A");
    printGenetics(B, "new_B");
}
