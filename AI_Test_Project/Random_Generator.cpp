//
//  Random_Generator.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/29/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Random_Generator.hpp"
#include <stdlib.h>

double getRandomDouble(int min, int max)
{
    double returned = (rand() % ((max - min) * 1000));
    returned = returned / 1000;
    returned += min;
    srand((int)returned * 1000);
    return returned;
}

double* getRandomArray(double min, double max, int size)
{
    double* array = (double*)malloc(sizeof(double) * size);
    for(int i = 0; i < size; i++)
    {
        array[i] = getRandomDouble(min, max);
    }
    return array;
}
