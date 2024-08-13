#pragma once

#include "scaffold.h"
#include "mason_drawer.h"

extern int mason_rectangle_type;

typedef struct {
	mason_drawer_data* drawer;
	scaffold_vector2 size;
	scaffold_list* elem;
} mason_rectangle_data;

scaffold_node* mason_rectangle_create(scaffold_node* drawer, scaffold_vector2 size);

