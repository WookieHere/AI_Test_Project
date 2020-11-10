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
    allocated_memory->wind_vector = (vector*)malloc(sizeof(vector));
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
    result_data->Coord = (Coordinate*)malloc(sizeof(Coordinate));
    result_data->wind_vector = (vector*)malloc(sizeof(vector));
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
    //pretty sure the malloc's are a waste of space, but only 1 of these ever exists at a time
    return allocated_node;
}

Cost_mesh* create_cost_mesh(int x_size, int y_size)
{
    mesh_node* node_pointer = (mesh_node*)malloc(sizeof(mesh_node));
    mesh_node* trailing_pointer = (mesh_node*)malloc(sizeof(mesh_node));
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
                //top-left
                Allocated_mesh->origin = node_pointer;
                trailing_pointer = node_pointer;
                free(node_pointer->north_coord);
                node_pointer->north_coord = NULL;
                free((node_pointer->west_coord));
                node_pointer->west_coord = NULL;
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
                free(node_pointer->west_coord);
                node_pointer->west_coord = NULL;
                trailing_pointer->south_coord = node_pointer;
                trailing_pointer = node_pointer;
            }else if(j == 0 && i == y_size-1)
            {
                //bottom-left
                node_pointer->west_coord = trailing_pointer;
                node_pointer->north_coord = trailing_pointer->north_coord->east_coord;
                trailing_pointer->east_coord = node_pointer;
                node_pointer->north_coord->south_coord = node_pointer;
                trailing_pointer = node_pointer;
                free(node_pointer->west_coord);
                node_pointer->west_coord = NULL;
                free(node_pointer->south_coord);
                node_pointer->south_coord = NULL;
            }else if(i == 0)
            {
                //top row
                node_pointer->west_coord = trailing_pointer;
                free(node_pointer->north_coord);
                node_pointer->north_coord = NULL;
                trailing_pointer->east_coord = node_pointer;
                trailing_pointer = node_pointer;
                if(j == x_size - 1)
                {
                    free(node_pointer->east_coord);
                    node_pointer->east_coord = NULL;
                }
            }else if(i == y_size - 1 && j == x_size - 1)
            {
                //bottom right corner
                node_pointer->west_coord = trailing_pointer;
                node_pointer->north_coord = trailing_pointer->north_coord->east_coord;
                trailing_pointer->east_coord = node_pointer;
                node_pointer->north_coord->south_coord = node_pointer;
                trailing_pointer = node_pointer;
                free(node_pointer->south_coord);
                node_pointer->south_coord = NULL;
                free(node_pointer->east_coord);
                node_pointer->east_coord = NULL;
            }else if(j == x_size - 1)
            {
                //right wall
                node_pointer->west_coord = trailing_pointer;
                node_pointer->north_coord = trailing_pointer->north_coord->east_coord;
                trailing_pointer->east_coord = node_pointer;
                node_pointer->north_coord->south_coord = node_pointer;
                trailing_pointer = node_pointer;
                free(node_pointer->east_coord);
                node_pointer->east_coord = NULL;
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

void freeCostMesh(Cost_mesh* mesh)
{
    //freeNode(mesh->origin); //that is a recursive call
    if(mesh->origin == NULL)
    {
        return;
    }
    mesh_node* temp = mesh->origin;
    mesh_node* trail = mesh->origin;
    mesh_node* col_holder = mesh->origin->south_coord;
    for(int i = 1; i < mesh->y_width; i++)
    {
        for (int j = 0; j < mesh->x_width; j++)
        {
            temp = temp->east_coord;
            freeNode(trail); //frees a row
            trail = temp;
        }
        //freeNode(temp); //right edge
        temp = col_holder;
        trail = col_holder;
        col_holder = col_holder->south_coord;
    }
    free(mesh);
    mesh->x_width = 0;
    mesh->y_width = 0;
    mesh = NULL;
}

void freeNode(mesh_node* node)
{
    free(node->data->Coord);
    node->data->Coord = NULL;
    free(node->data->wind_vector);
    node->data->wind_vector = NULL;
    free(node->data);
    node->data = NULL;
    //free(node->east_coord);
    //node->east_coord = NULL;
    //free(node->west_coord);
    //node->west_coord = NULL;
    //free(node->south_coord);
    //node->south_coord = NULL;
    //free(node->north_coord);
    //node->north_coord = NULL;
    free(node);
    node = NULL;
} //would've been cool but doesn't look like it works well



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
