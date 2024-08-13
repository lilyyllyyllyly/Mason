#pragma once

#include "scaffold.h"
#include "mason_drawer.h"

void drawer_delete_sprite(mason_drawer_data* drawer, scaffold_list* elem);

scaffold_list* drawer_add_rectangle(scaffold_node* drawer, scaffold_node* rect, scaffold_vector2 size);
void drawer_add_sprite(scaffold_node* drawer, scaffold_node* sprite, const char* filename);

