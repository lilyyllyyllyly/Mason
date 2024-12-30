#pragma once

#include <stdbool.h>

#include "scaffold.h"
#include "mason_drawer.h"

extern int mason_sprite_type;

typedef struct {
	scaffold_node* node;
	mason_drawer_data* drawer;
	scaffold_list* elem; // list element in list of sprites

	int draw_order;
	bool visible;

	void (*draw)(scaffold_node*);
} mason_sprite_data;

void mason_sprite_data_destroy(mason_sprite_data* data);
mason_sprite_data* mason_sprite_data_create(scaffold_node* node, scaffold_node* drawer, int draw_order, void (*draw)(scaffold_node*));

