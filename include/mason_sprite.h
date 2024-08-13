#pragma once

#include "scaffold.h"

extern int mason_sprite_type;

typedef struct {
	mason_drawer_data* drawer;
	Texture2D tex;
	scaffold_vector2 size;
	scaffold_list* elem;
} mason_sprite_data;

scaffold_node* mason_sprite_create(scaffold_node* drawer, const char* filename);

