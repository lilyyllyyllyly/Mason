#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "render/mason_drawer_internal.h"
#include "render/mason_sprite.h"

void mason_sprite_data_destroy(mason_sprite_data* data) {
	drawer_delete_sprite(data->drawer, data->elem);
	free(data);
}

mason_sprite_data* mason_sprite_data_create(scaffold_node* node, scaffold_node* drawer, int draw_order, void (*draw)(scaffold_node*)) {
	mason_sprite_data* data = malloc(sizeof(mason_sprite_data));
	
	data->node = node;
	data->drawer = (mason_drawer_data*)(drawer->data);
	data->draw_order = draw_order;
	data->elem = drawer_add_sprite(data->drawer, data);
	data->draw = draw;

	return data;
}

