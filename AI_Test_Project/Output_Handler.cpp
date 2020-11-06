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

Output_handler::Output_handler(Player_head* head, )
{

}
void Output_handler::drawPlayer(const char* filename, Player_head* list)
{
	FILE* fp;
	fopen_s(fp, filename, "w+b"); //open the file for read and write in binary mode
	if (!fp)
	{
		std::cout << "ERROR: cannot open file" << std::endl;
		exit(90);
	}
	fseek(fp, 26 * SIZE_ITEMS, 0); //i believe the header of a ppm file is 26 * 3 bytes long, will probably have to correct that later
	for (int i = 0; i < list->length; i++)
	{
		Player* player = list->next_node->ranked_player;
		for (int j = 0; j < player->Route->length; j++)
		{
			Coordinate* A = player->Route->next_node->Coordinate;
			Coordinate* B = player->Route->next_node->next_node->Coordinate;
			this->drawVector(fp, A, B);
			player->Route->next_node = player->Route->next_node->next_node; //iterate through the coordinates
		}
		player = list->next_node->next_node->ranked_player; //iterate through the players
	}
	fclose(fp);
}
bool Output_handler::drawVector(FILE* fp, Coordinate* A, Coordinate* B) //draw a line between two points in a file
{
	RGB color;		//at the moment these are all printed out black, we can implement a color based on rank later
	color.r = 0;
	color.g = 0;
	color.b = 0;
	//figure out the slope from point A to B
	int slope = (B->Y - A->Y) / (B->X - A->Y);
	//find whether A or B comes first in the file
	int firstInFile;
	int secondInFile;
	//by adding the coords parts together we can determine their placement in the file
	int totalA = A->X + A->Y;
	int totalB = B->X + B->Y;
	if (totalA > totalB)
	{
		firstInFile = totalB;
		secondInFile = totalA;
	}
	else					//if Coord A and B are the same it does not matter which we choose to be first in the file.
	{
		firstInFile = totalA;
		secondInFile = totalB;
	}
	/*Open the file and increment past the header*/
	//add an offset to the file to get to the RGBs
	
	fseek(fp, firstInFile, 0); //iterate the file pointer to the first of our coordinates in the file
	while (firstInFile != secondInFile || !EOF)
	{
		//fprintf to the RGB values at current point
		//iterate a line + slope
		fprintf(fp, "%d", color->r, color->g, color->b);
		fseek(fp, file_width + slope, SEEK_CUR);

	}
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

Player_head* Output_handler::rankPlayers(Player_head* head)
{
	//ranks the players in terms of best time


}