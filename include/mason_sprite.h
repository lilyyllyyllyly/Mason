#pragma once

#include "scaffold.h"
#include "mason_drawer.h"

extern int mason_sprite_type;

typedef enum {
	MASON_SPR_TEXTURE = 0,
	MASON_SPR_RECTANGLE
} mason_sprite_shape;

typedef struct {
	mason_drawer_data* drawer;
	scaffold_list* elem; // list element in list of sprites
	
	int draw_order;

	struct {
		mason_sprite_shape type;
		union {
			struct {
				Texture2D tex;
				scaffold_vector2 tex_size;
			}; // texture

			scaffold_vector2 rect_size; // rectangle
		};
	} shape;

	Texture2D tex;
	scaffold_vector2 size;
} mason_sprite_data;

scaffold_node* mason_texture_create(scaffold_node* drawer, int draw_order, const char* filename);
scaffold_node* mason_rectangle_create(scaffold_node* drawer, int draw_order, scaffold_vector2 size);

