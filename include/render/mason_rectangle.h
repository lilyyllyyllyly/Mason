#pragma once

#include "scaffold.h"
#include "render/mason_sprite.h"

extern int mason_rectangle_type;

typedef struct {
	mason_sprite_data* sprite;
	scaffold_vector2 size;
} mason_rectangle_data;

scaffold_node* mason_rectangle_create(scaffold_node* drawer, int draw_order, scaffold_vector2 size);

