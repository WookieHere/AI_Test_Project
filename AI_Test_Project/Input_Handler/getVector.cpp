//
//  getVector.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/28/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include <stdio.h>
#include "Input_Handler.hpp"
#include "Player.hpp"
#include <math.h>

vector* Input_handler::getVector(Coordinate* coord)
{
    //This will scan an image found in the config for the RGB value at that pixel...

    ImageRGB image;
    //vector* test_vector = createVector();
    //test_vector->X = 127;
    //test_vector->Y = 0;
    //test_vector->Z = 50;
    //return test_vector;
    vector* test_vector = (vector*)malloc(sizeof(vector));
    if(coord->Y > 550)
    {
        test_vector->X = 255;
        test_vector->Y = 91;
        test_vector->Z = 2;
        return test_vector;
    }else if(coord->X < 0 || coord->Y < 0)
    {
        test_vector->X = -200;
        test_vector->Y = -200;
        test_vector->Z = 200;
        return test_vector;
    }else
    {
        test_vector->X = 10;
        test_vector->Y = 10;
        test_vector->Z = 10;
        return test_vector;
    }
    
    
    int error = load_ppm(image, this->User_config->turbulence_map, coord->X, coord->Y);
    //printf("\nTarget Pixel: [%u, %u, %u]\n", image.pixel.r, image.pixel.g, image.pixel.b); //for testing purposes
    
    if(error == 100)
    {
        
        //vector* test_vector = createVector();
        test_vector->X = 127;
        test_vector->Y = 0;
        test_vector->Z = 50;
         
        printf("File not loaded\n");
        
    }//error is 100 if file was NULL
    
    
    test_vector->X = image.pixel.r >> 24;
    test_vector->Y = image.pixel.g >> 24;
    test_vector->Z = image.pixel.b >> 24;
    
    return test_vector;
}

void eat_token(pbyte& ptr, const pbyte end)
{
    for (; ptr != end; ++ptr)
    {
        if (*ptr == '\n' || *ptr == '\r' || *ptr == '\t' || *ptr == ' ')
            break;
    }
}

int get_int(pbyte& ptr, const pbyte end)
{
    eat_white(ptr, end);
    int v = atoi((char*)ptr);
    eat_token(ptr, end);
    return v;
}

void eat_line(pbyte& ptr, const pbyte end)
{
    for (; ptr != end; ++ptr)
    {
        if (*ptr == '\n')
            break;
    }
    ptr++;
}//move on from new_line

void eat_comment(pbyte& ptr, const pbyte end)
{
    while (ptr != end)
    {
        eat_white(ptr, end);
        if (*ptr != '#')
            break;
        eat_line(ptr, end);
    }
}//move on from comments

void eat_white(pbyte& ptr, const pbyte end)
{
    for (; ptr != end; ++ptr)
    {
        if (*ptr != '\n' && *ptr != '\r' && *ptr != '\t' && *ptr != ' ')
            break;
    }
}//move ahead to nearest non-white space character

int load_file(std::vector<byte>& buf, const char* name)
{
    // open
    FILE* f = fopen(name, "rb");
    if (!f)
    {
        //std::cout << "Could not open file: " << name << std::endl;
        return 1;
    }

    // get size
    fseek(f, 0, SEEK_END);
    int s = (int)ftell(f);
    fseek(f, 0, SEEK_SET);

    // read (put space at end for atoi)
    buf.resize(s + 1);
    fread((char*)&buf[0], 1, s, f);
    buf[s] = ' ';

    // close
    fclose(f);
    return 0;
}

int load_ppm(ImageRGB& img, const char* name, int rows, int cols)
{
    std::vector<byte> file;
    if (load_file(file, name))
    {
        std::cout << "Could not open file: " << name << std::endl;
        return 100;
    }

    pbyte ptr = &file[0];   //starts at the start of the file
    const pbyte end = ptr + file.size(); // declares the end point

    // get type of file
    eat_comment(ptr, end);
    eat_white(ptr, end);
    int mode = 0;
    if (ptr + 2 < end && ptr[0] == 'P')
    {
        mode = ptr[1] - '0';
        ptr += 2;
    }

    // get w
    eat_comment(ptr, end);
    img.w = get_int(ptr, end);
    
    if (img.w < cols)
    {
        std::cout << "ERROR: target is out of bounds" << std::endl;
        return 0;
    }

    // get h
    eat_comment(ptr, end);
    img.h = get_int(ptr, end);
    if (img.h < rows)
    {
        std::cout << "ERROR: target is out of bounds" << std::endl;
        return 0;
    }

    // get bits
    eat_comment(ptr, end);
    get_int(ptr, end);

    // load image data
    int target_location = rows * cols;  //this will be the start of the pixel we want
    //(unused)int target_end = target_location + 3; //end of the pixel data we want

    if (mode == 6)
    {
        ptr++;
        /*add the offset traget location to find the pixel we want*/
        memcpy(&img.pixel, ptr + target_location, 9);
    }
    else if (mode == 3)
    {
        for (int i = 0; i < img.h * img.w; i++)
        {
            if (i == target_location)
            {
                img.pixel.r = get_int(ptr, end);
                img.pixel.g = get_int(ptr, end);
                img.pixel.b = get_int(ptr, end);
            }
        }
    }
    return 0;
}

