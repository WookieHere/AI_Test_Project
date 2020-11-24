//
//  Input_Handler.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Input_Handler_hpp
#define Input_Handler_hpp
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>

struct RGB
{
    unsigned int r, g, b;
};
struct ImageRGB
{
    int w, h;
    RGB pixel;
};

//this block is for reading RGB values (Zach's code)
typedef unsigned char byte;
typedef byte* pbyte;
int load_ppm(ImageRGB& img, const char* name, int rows, int cols);
void eat_line(pbyte& ptr, const pbyte end);
void eat_comment(pbyte& ptr, const pbyte end);
void eat_white(pbyte& ptr, const pbyte end);
int load_file(std::vector<byte>& buf, const char* name);
void eat_token(pbyte& ptr, const pbyte end);
int get_int(pbyte& ptr, const pbyte end);

struct Config
{
    const char* heightmap_img;
    const char* turbulence_map;   //purely for simulation
    int generation_size;
    int generation_end_count;
    //also needs a data structure for a keyframe setup. probably an array of tuples etc
    int x_size;     //reference frame dimensions (try to make it an odd number)
    int y_size;
    double roughness;       //2 meters per node
    double Avg_Thrust;    //DEFINITELY a placeholder. avg thrust for a 747 Boeing
                                //typically need thrust of 1/18 * weight
    double Wind_Unit;
    double Wing_Area;        //meters^2 for Boeing 747
    double Pressure_Const;           //P = .613V^2 where V is wind velocity
    double Drag_Coefficient;      //no unit, C_o in equations of Boeing 747
    double Minimum_Velocity;
    double Max_Turn_Rate;
    double Plane_mass;  //literally mass of the plane in kg's
    //some other stuff to be filled in later
};

struct Range_tuple
{
    struct Coordinate* A;
    struct Coordinate* B;   //This means from point A to point B (in a row/col) the derivitive avg is the data
    int orientation;        //row/col selector
    double derivitive;
};

struct Range_node
{
    Range_tuple* Range;
    Range_node* next_node;
};

struct Range_head
{
    int length;
    Range_node* next_node;
};


class Input_handler
{
    struct Coordinate** Keyframe_array;   //2D array of all keyframe definitions
    Config* User_config;
    struct Coordinate* Destination_Coord;
    struct Coordinate* Player_Origin;
    struct Coordinate* resolution;  //pixels in image as X/Y
    double scale;   //This is the pixels/meter type scale
    Range_head* Range_list; //this defines ranges of derivitives
    class Output_handler* Output;
    int generation_count;   //increments each generation
    
public:
    Input_handler(Coordinate*, Coordinate*, Output_handler*, const char*);
    ~Input_handler();
    void setConfig(const char* filename);   //made this public
    struct Coordinate* getCoordinate(class Player*);  //Like an update position. Mostly a placeholder
    struct Coordinate getDestination();
    struct Coordinate getOrigin();
    struct vector* getVector(Coordinate* coord);
    Config getConfig();
    int loop();
    double getDistKeyFrame(Coordinate*, Coordinate*);     //returns distance to nearest keyframe
    int isInKeyframe(Coordinate*, Coordinate*);
private:
    void readKeyFrames();
    
};
#endif /* Input_Handler_hpp */
