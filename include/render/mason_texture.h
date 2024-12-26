#pragma once

#include <raylib.h>

#include "scaffold.h"
#include "render/mason_sprite.h"

extern int mason_texture_type;

typedef struct {
	mason_sprite_data* sprite;
	Texture2D texture;
	scaffold_vector2 size;
} mason_texture_data;

scaffold_node* mason_texture_create(scaffold_node* drawer, int draw_order, const char* filename);

