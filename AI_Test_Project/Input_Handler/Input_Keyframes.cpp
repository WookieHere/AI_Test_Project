//
//  Input_Keyframes.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 11/24/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include "Input_Handler.hpp"
#include "Player.hpp"
#include <math.h>
#define MAX_KEYS        16
#define COORD_NUM   4

int Input_handler::isInKeyframe(Coordinate* frame, Coordinate* loc)
{
    if(loc->X <= frame[1].X && loc->X >= frame[0].X)
    {
        if(loc->Y <= frame[2].Y && loc->Y >= frame[0].Y)
        {
            return 1;
        }
    }
    return 0;
}

void Input_handler::readKeyFrames()
{
    Coordinate temp = {0,0};
    this->Keyframe_array[0][0] = temp;
    temp = {550, 0};
    this->Keyframe_array[0][1] = temp;
    temp = {0, 550};
    this->Keyframe_array[0][2] = temp;
    temp = {550, 550};
    this->Keyframe_array[0][3] = temp;
    
    temp = {0, 551};
    this->Keyframe_array[1][0] = temp;
    temp = {551, 551};
    this->Keyframe_array[1][1] = temp;
    temp = {0, 1048};
    this->Keyframe_array[1][2] = temp;
    temp = {1048, 1048};
    this->Keyframe_array[1][3] = temp;
    
    for(int i = 2; i < MAX_KEYS; i++)
    {
        free(Keyframe_array[i]);
        Keyframe_array[i] = NULL;
    }//frees all unused indexes
}

double Input_handler::getDistKeyFrame(Coordinate* loc, Coordinate* origin)
{
    double temp_min = 500000;
    double temp = temp_min;
    for(int i = 0; i < MAX_KEYS; i++)
    {
        
        for(int j = 0; j < COORD_NUM; j++)
        {
            if(this->Keyframe_array[i] != NULL)
            {
                if(isInKeyframe(this->Keyframe_array[i], loc) == 0)
                {
                    if(loc->X > Keyframe_array[i][0].X && loc->X < Keyframe_array[i][1].X)
                    {
                        //is directly above or below frame
                        if(loc->Y > Keyframe_array[i][2].Y)
                        {
                            //below
                            temp = abs(loc->Y - Keyframe_array[i][2].Y);
                        }else
                        {
                            //above
                            temp = abs(loc->Y - Keyframe_array[i][0].Y);
                        }
                        
                    }else if(loc->Y > Keyframe_array[i][0].Y && loc->Y < Keyframe_array[i][2].Y)
                    {
                        //is directly to the left/right of frame
                        if(loc->X > Keyframe_array[i][1].X)
                        {
                            //to the right
                            temp = abs(loc->X - Keyframe_array[i][1].X);
                        }else
                        {
                            //to the left
                            temp = abs(loc->X - Keyframe_array[i][0].X);
                        }
                    }else
                    {
                        //is diagonally away froma  corner
                        temp = getDistance(loc, &this->Keyframe_array[i][j]);
                    }
                }
                if(isInKeyframe(this->Keyframe_array[i], loc) != isInKeyframe(this->Keyframe_array[i], origin))
                {
                    temp *= -1;
                    //this means the origin and result are not in the same frame
                }
                if(abs(temp_min) > abs(temp))
                {
                    temp_min = temp;
                }
                
            }
            
            
        }
    }
    return temp_min;
}
