//
//  Linked_List_Handler.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 10/17/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Linked_List_Handler_hpp
#define Linked_List_Handler_hpp

#include <stdio.h>
#include "Mesh_Construction.hpp"
#include "Route_Constructor.hpp"
#include "Player.hpp"



Player_node* createNodePlayer();
Player_node* setNodePlayer(Player* new_data);
void addNodePlayer(Player_head* head, Player_node* new_node);

Coordinate_node* createNodeCoordinate();
Coordinate_node* setNodeCoordinate(Coordinate* new_data);
void addNodeCoordinate(Coordinate_head* head, Coordinate_node* data);   //This one is a stack

Range_node* createNodeRange();
Range_node* setNodeRange(Range_tuple* new_data);
void addNodeRange(Range_head* head, Range_node* data);  //This one is a Queue
//Technically these functions could be universal with just variations in the
 //void* version of a data*, but these functions could be placed into a class for
 //easier to understand code I think, so I will keep this format for now



#endif /* Linked_List_Handler_hpp */
