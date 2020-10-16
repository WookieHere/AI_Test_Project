//
//  Mesh_Construction.hpp
//  AI_Test_Project
//
//  Created by Luke Nasby on 9/22/20.
//  Copyright © 2020 Luke Nasby. All rights reserved.
//

#ifndef Mesh_Construction_h
#define Mesh_Construction_h
#include <stdlib.h>
#include <stdio.h>

struct data
{
    int x;
    int y;
};

struct mesh_node
{
    struct data* data;
    struct mesh_node* north_coord;
    struct mesh_node* east_coord;
    struct mesh_node* west_coord;
    struct mesh_node* south_coord;
};

struct Cost_mesh
{
    int x_width;    //this will be a rotated selection based on the plane's current trajectory from the image.
    int y_width;    //rectangular stretched based on current velocity
    struct mesh_node* origin;   //the 0,0 of the grid
};

Cost_mesh*  create_cost_mesh(int x_size, int y_size);
mesh_node*  create_mesh_node();
data*       create_data();
data*       set_data(int x, int y);
mesh_node* get_node(Cost_mesh*, int x, int y);



#endif /* Mesh_Construction_h */
