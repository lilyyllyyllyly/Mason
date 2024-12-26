#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "render/mason_sprite.h"

int mason_texture_type = NODE_TYPE_UNASSIGNED;

#include "render/mason_texture.h"

static void destroy(scaffold_node* texture) {
	mason_texture_data* data = (mason_texture_data*)(texture->data);

	mason_sprite_data_destroy(data->sprite);
	UnloadTexture(data->texture);
	free(data);

	scaffold_node_destroy(texture);
}

static void draw(scaffold_node* texture) {
	mason_texture_data* data = (mason_texture_data*)(texture->data);
	DrawTexture(data->texture, texture->global_pos.x, texture->global_pos.y, WHITE);
}

scaffold_node* mason_texture_create(scaffold_node* drawer, int draw_order, const char* filename) {
	mason_texture_data* data = malloc(sizeof(mason_texture_data));

	scaffold_node* texture = scaffold_node_create(
		&mason_texture_type,
		data,
		NULL,
		destroy
	);

	data->texture = LoadTexture(filename);
	data->size = (scaffold_vector2){data->texture.width, data->texture.height};
	data->sprite = mason_sprite_data_create(texture, drawer, draw_order, draw);

	return texture;
}

