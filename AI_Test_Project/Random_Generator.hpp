//
//  Random_Generator.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/29/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Random_Generator_hpp
#define Random_Generator_hpp

#include <stdio.h>

typedef enum randomDatatype { int_r, double_r, char_r,}randomDatatype;

double getRandomDouble(int min, int max);
double* getRandomArray(double min, double max, int size);
int getRandomInt(int min, int max);
int getRandomIntArray(int min, int max, int size);
void swapInts(int* array, int A, int B);
int* getRandomMatchup(int min, int max);
int getRandom2RN(int min, int max);

#endif /* Random_Generator_hpp */
