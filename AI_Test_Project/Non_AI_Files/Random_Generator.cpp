//
//  Random_Generator.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/29/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Random_Generator.hpp"
#include <stdlib.h>
#include <time.h>
#include <math.h>

double getRandomDouble(int min, int max)
{
    double returned = (rand() % ((max - min) * 1000));
    returned = returned / 1000;
    returned += min;
    srand((int)returned * 1000);
    while(abs(returned) < 0)
    {
        returned = getRandomDouble(min, max);
    }
    //the double from this can never be 0
    srand(returned * (int)clock());
    return returned;
}

double* getRandomDoubleArray(double min, double max, int size)
{
    double* array = (double*)malloc(sizeof(double) * size);
    for(int i = 0; i < size; i++)
    {
        array[i] = getRandomDouble(min, max);
    }
    return array;
}

int getRandomInt(int min, int max)
{
    int returned = rand() % ((max - min));
    returned += min;
    srand(returned * (int)clock()); //clock() usually returns an unsigned long, but we can loose precision here...
    return returned;
}

int* getRandomIntArray(int min, int max, int size)
{
    int* array = (int*)malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++)
    {
        array[i] = getRandomInt(min, max);
    }
    return array;
}

void swapInts(int* array, int A, int B)
{
    int C = array[A];
    array[A] = array[B];
    array[B] = C;
}

int* getRandomMatchup(int min, int max)
{
    //this will return an array containing every int between min -> max in a random order
    int* array = (int*)malloc(sizeof(int) * (max - min));
    int random_int;
    for (int i = min; i < max; i++)
    {
        array[i] = i;
    }
    for(int j = min; j < max; j++)
    {
        random_int = getRandomInt(j, max);
        swapInts(array, j, random_int);
    }
    return array;
}

int getRandom2RN(int min, int max)
{
    int A = getRandomInt(min, max);
    int B = getRandomInt(min, max);
    
    double C = (A + B) / 2;
    return (int)ceil(C);
    //returns the average of 2 random numbers within a range (so close to a bell curve)
}
