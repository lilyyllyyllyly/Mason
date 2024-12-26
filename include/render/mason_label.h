#pragma once

#include "scaffold.h"
#include "render/mason_sprite.h"

typedef struct {
	mason_sprite_data* sprite;
	char* text;
	int font_size, format;
} mason_label_data;

scaffold_node* mason_label_create(scaffold_node* drawer, int draw_order, char* text, int font_size, int format);

