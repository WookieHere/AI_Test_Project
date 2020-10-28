//
//  Input_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//
#include <stdlib.h>
#include "Input_Handler.hpp"

Input_handler::Input_handler(Coordinate* Destination)
{
    this->User_config = (Config*)malloc(sizeof(Config));
    this->Destination_Coord = Destination;
    this->User_config->heightmap_img = NULL;
    this->User_config->x_size = 9;     //reference frame dimensions (try to make it an odd number)
    this->User_config->y_size = 9;
    this->User_config->roughness = 2;       //2 meters per node
    this->User_config->Avg_Thrust = 252000;     //DEFINITELY a placeholder. avg thrust for a 747 Boeing (newtons)
    this->User_config->Minimum_Velocity = 294.98;    //minimum velocity in m/s
    this->User_config->Wind_Unit = 37/(127) * (1000/60);    //m/s per 1 unit of wind vector
    this->User_config->Wing_Area = 541.2;   //meters^2 for Boeing 747
    this->User_config->Pressure_Const = .613;   //P = .613V^2 where V is wind velocity
    this->User_config->Drag_Coefficient = .031; //no unit, C_o in equations of Boeing 747
    this->User_config->Max_Turn_Rate = 5/72;    //radians
}

Coordinate* Input_handler::getDestination()
{
    return Destination_Coord;
}

vector* Input_handler::getVector(Coordinate* coord)
{
    //This will scan an image found in the config for teh RGB value at that pixel...

    ImageRGB image;
    load_ppm(image, "USA_TM.ppm", coord->X, coord->Y);
    printf("\nTarget Pixel: [%u, %u, %u]\n", image.pixel.r, image.pixel.g, image.pixel.b); //for testing purposes
    return NULL;
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
}

void eat_comment(pbyte& ptr, const pbyte end)
{
    while (ptr != end)
    {
        eat_white(ptr, end);
        if (*ptr != '#')
            break;
        eat_line(ptr, end);
    }
}

void eat_white(pbyte& ptr, const pbyte end)
{
    for (; ptr != end; ++ptr)
    {
        if (*ptr != '\n' && *ptr != '\r' && *ptr != '\t' && *ptr != ' ')
            break;
    }
}

int load_file(std::vector<byte>& buf, const std::string& name)
{
    // open
    FILE* f = fopen(name.c_str(), "rb");
    if (!f)
    {
        std::cout << "Could not open file: " << name << std::endl;
        return 1;
    }

    // get size
    fseek(f, 0, SEEK_END);
    int s = ftell(f);
    fseek(f, 0, SEEK_SET);

    // read (put space at end for atoi)
    buf.resize(s + 1);
    fread((char*)&buf[0], 1, s, f);
    buf[s] = ' ';

    // close
    fclose(f);
    return 0;
}

void load_ppm(ImageRGB& img, const std::string& name, int rows, int cols)
{
    std::vector<byte> file;
    if (load_file(file, name))
    {
        std::cout << "Could not open file: " << name << std::endl;
        return;
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
        exit(0);
    }

    // get h
    eat_comment(ptr, end);
    img.h = get_int(ptr, end);
    if (img.h < rows)
    {
        std::cout << "ERROR: target is out of bounds" << std::endl;
        exit(0);
    }

    // get bits
    eat_comment(ptr, end);
    int bits = get_int(ptr, end);

    // load image data
    int target_location = rows * cols;  //this will be the start of the pixel we want
    int target_end = target_location + 3; //end of the pixel data we want

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
            if (i = target_location)
            {
                img.pixel.r = get_int(ptr, end);
                img.pixel.g = get_int(ptr, end);
                img.pixel.b = get_int(ptr, end);
            }
        }
    }
}
