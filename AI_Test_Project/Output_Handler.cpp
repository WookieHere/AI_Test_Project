//
//  Output_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/18/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Output_Handler.hpp"
#define	 SIZE 1
#define  SIZE_ITEMS	3

void Output_handler::drawVector(FILE* output_file, Coordinate* A, Coordinate* B) //draw a line between two points in a file
{

}

FILE* Output_handler::initPPM_file(const char* output_filename, int width, int height)
{
	static unsigned char color[3] = {0,0,0};
	 //name is subject to change
	FILE* out_file = fopen(output_filename, "wb"); //write to file in binary mode
	if (!out_file)
	{
		std::cout << "ERROR: output file did not load" << std::endl;
		exit(90);
	}

	fprintf(out_file, "P6\n%d %d\n255\n", width, height); //this code is important for the type of ppm file and the header
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fwrite(color, SIZE, SIZE_ITEMS, out_file); //binary output
		}
	}
	fclose(out_file);
	return out_file;
}
