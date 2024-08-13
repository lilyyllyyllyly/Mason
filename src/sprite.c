#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "mason_drawer_internal.h"

int mason_sprite_type = NODE_TYPE_UNASSIGNED;

#include "mason_sprite.h"

static void destroy(scaffold_node* sprite) {
	mason_sprite_data* data = (mason_sprite_data*)(sprite->data);

	UnloadTexture(data->tex);
	drawer_delete_sprite(data->drawer, data->elem);

	free(sprite->data);
	scaffold_node_destroy(sprite);
}

scaffold_node* mason_sprite_create(scaffold_node* drawer, const char* filename) {
	mason_sprite_data* data = malloc(sizeof(mason_sprite_data));
	data->drawer = (mason_drawer_data*)(drawer->data);
	data->tex = LoadTexture(filename);
	data->size = (scaffold_vector2){data->tex.width, data->tex.height};

	scaffold_node* sprite = scaffold_node_create(
		&mason_sprite_type,
		data,
		NULL,
		destroy
	);

	data->elem = drawer_add_sprite(data->drawer, sprite);

	return sprite;
}

