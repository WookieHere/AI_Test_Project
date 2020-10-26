//
//  Linked_List_Handler.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/17/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Linked_List_Handler.hpp"

Player_node* createNodePlayer()
{
    Player_node* new_node = (Player_node*)malloc(sizeof(Player_node));
    return new_node;
}//probably never called directly in class etc. Use setNode

Player_node* setNodePlayer(Player* new_data)
{
    Player_node* new_node = createNodePlayer();
    new_node->ranked_player = new_data;
    return new_node;
}

void addNodePlayer(Player_head* head, Player* data)
{
    Player_node* temp_pointer = head->next_node;
    Player_node* new_node = setNodePlayer(data);
    for(int i = 0; i < head->length; i++)
    {
        temp_pointer = temp_pointer->next_node;
    }
    temp_pointer->next_node = new_node;
    //new_node->next_node = NULL; //just making sure?
    head->length++;
}//This adds a player to the linked list and updates the head;

Coordinate_node* createNodeCoordinate()
{
    Coordinate_node* new_node = (Coordinate_node*)malloc(sizeof(Coordinate_node));
    return new_node;
}//probably never called directly in class etc. Use setNode

Coordinate_node* setNodeCoordinate(Coordinate* new_data)
{
    Coordinate_node* new_node = createNodeCoordinate();
    new_node->Coordinate = new_data;
    return new_node;
}

void addNodeCoordinate(Coordinate_head* head, Coordinate* data)
{
    Coordinate_node* temp_pointer = head->next_node;
    Coordinate_node* new_node = setNodeCoordinate(data);
    for(int i = 0; i < head->length; i++)
    {
        temp_pointer = temp_pointer->next_node;
    }
    temp_pointer->next_node = new_node;
    //new_node->next_node = NULL; //just making sure?
    head->length++;
}//This adds a Coordinate to the linked list and updates the head;

Range_node* createNodeRange()
{
    Range_node* new_node = (Range_node*)malloc(sizeof(Range_node));
    return new_node;
}//probably never called directly in class etc. Use setNode

Range_node* setNodeRange(Range_tuple* new_data)
{
    Range_node* new_node = createNodeRange();
    new_node->Range_tuple = new_data;
    return new_node;
}

void addNodeRange(Range_head* head, Range_tuple* data)
{
    Range_node* temp_pointer = head->next_node;
    Range_node* new_node = setNodeRange(data);
    for(int i = 0; i < head->length; i++)
    {
        temp_pointer = temp_pointer->next_node;
    }
    temp_pointer->next_node = new_node;
    //new_node->next_node = NULL; //just making sure?
    head->length++;
}//This adds a Coordinate to the linked list and updates the head;
