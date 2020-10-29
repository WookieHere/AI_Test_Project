//
//  Mesh_Construction.cpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 9/22/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#include "Mesh_Construction.hpp"
#include "Player.hpp"
data* create_data()
{
    data* allocated_memory = (data*)malloc(sizeof(data));
    allocated_memory->Coord = (Coordinate*)malloc(sizeof(Coordinate));
    return allocated_memory;
}

unit_vector* createUnitVector()
{
    return (unit_vector*)malloc(sizeof(unit_vector));
}

vector* createVector()
{
    return (vector*)malloc(sizeof(vector));
}

Coordinate* createCoordinate()
{
    return (Coordinate*)malloc(sizeof(Coordinate));
}

data* set_data(int x, int y)
{
    data* result_data = create_data();
    //result_data->x = (int*)malloc(sizeof(int));
    //result_data->y = (int*)malloc(sizeof(int));
    result_data->Coord->X = x;
    result_data->Coord->Y = y;
    return result_data;
}

mesh_node* create_mesh_node()
{
    mesh_node* allocated_node = (mesh_node*)malloc(sizeof(mesh_node));
    allocated_node->data = create_data();
    allocated_node->north_coord = NULL;
    allocated_node->east_coord = NULL;
    allocated_node->west_coord = NULL;
    allocated_node->south_coord = NULL;
    return allocated_node;
}

Cost_mesh* create_cost_mesh(int x_size, int y_size)
{
    mesh_node* node_pointer = NULL;
    mesh_node* trailing_pointer = NULL;
    Cost_mesh* Allocated_mesh = (Cost_mesh*)malloc(sizeof(Cost_mesh));
    Allocated_mesh->x_width = x_size;
    Allocated_mesh->y_width = y_size;
    for(int i = 0; i < y_size; i++)
    {
        for(int j = 0; j < x_size; j++)
        {
            //trailing_pointer = node_pointer;
            node_pointer = create_mesh_node();
            node_pointer->data = set_data(j, i);
            if(i == 0 && j == 0)
            {
                Allocated_mesh->origin = node_pointer;
                trailing_pointer = node_pointer;
                //this just sets the origin at 0,0 (top-left)
            }else if(j == 0)
            {
                //left-most column
                trailing_pointer = Allocated_mesh->origin;
                for(int k = 0; k < i-1; k++)
                {
                    trailing_pointer = trailing_pointer->south_coord;
                    //trailing pointer is now node above node_pointer
                }
                node_pointer->north_coord = trailing_pointer;
                trailing_pointer->south_coord = node_pointer;
                trailing_pointer = node_pointer;
            }else if(i == 0)
            {
                //top row
                node_pointer->west_coord = trailing_pointer;
                trailing_pointer->east_coord = node_pointer;
                trailing_pointer = node_pointer;
            }else
            {
                node_pointer->west_coord = trailing_pointer;
                node_pointer->north_coord = trailing_pointer->north_coord->east_coord;
                trailing_pointer->east_coord = node_pointer;
                node_pointer->north_coord->south_coord = node_pointer;
                trailing_pointer = node_pointer;
            }
            
        }
    }
    //this returns a mesh on unallocated values.
    return Allocated_mesh;
}

mesh_node* get_node(Cost_mesh* used_mesh, int x, int y)
{
    if(x >= used_mesh->x_width || y >= used_mesh->y_width || x < 0 || y < 0)
    {
        printf("Invalid arguments: x:%d, y:%d\n mesh size: %d, %d\n", x, y, used_mesh->x_width, used_mesh->y_width);
        //This just checks to make sure the arguements are valid
        return NULL;
    }
    mesh_node* node_pointer = create_mesh_node();
    node_pointer = used_mesh->origin;
    for(int i = 0; i < y; i++)
    {
        node_pointer = node_pointer->south_coord;
    }
    for(int j = 0; j < x; j++)
    {
        node_pointer = node_pointer->east_coord;
    }
    return node_pointer;
}

void doMesh(void(*func)(mesh_node*), Cost_mesh* mesh)
{
    mesh_node* column_holder = mesh->origin;
    mesh_node* traversal_node = mesh->origin;
    for(int i = 0; i < mesh->y_width; i++)
    {
        for(int j = 0; j < mesh->x_width; j++)
        {
            func(traversal_node);
            traversal_node = traversal_node->west_coord;
        }//goes through a row left to right
        column_holder = column_holder->south_coord;
        traversal_node = column_holder;
    }
}//This does whatever function is sent to it to the whole mesh
 //Player will have a mesh around it's reference frame, and the
 //cost evaluation function will run for each node in the mesh,
 //then the minimum will be found
