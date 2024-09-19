#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "mason_drawer_internal.h"

int mason_sprite_type = NODE_TYPE_UNASSIGNED;

#include "mason_sprite.h"

static void destroy(scaffold_node* sprite) {
	mason_sprite_data* data = (mason_sprite_data*)(sprite->data);

	if (data->shape.type == MASON_SPR_TEXTURE) UnloadTexture(data->shape.texture);

	drawer_delete_sprite(data->drawer, data->elem);

	free(sprite->data);
	scaffold_node_destroy(sprite);
}

static scaffold_node* create_sprite(scaffold_node* drawer, int draw_order) {
	mason_sprite_data* data = malloc(sizeof(mason_sprite_data));
	data->drawer = (mason_drawer_data*)(drawer->data);
	data->draw_order = draw_order;

	scaffold_node* sprite = scaffold_node_create(
		&mason_sprite_type,
		data,
		NULL,
		destroy
	);

	data->elem = drawer_add_sprite(data->drawer, sprite);

	return sprite;
}

scaffold_node* mason_texture_create(scaffold_node* drawer, int draw_order, const char* filename) {
	scaffold_node* sprite = create_sprite(drawer, draw_order);
	mason_sprite_data* data = (mason_sprite_data*)(sprite->data);

	data->shape.type = MASON_SPR_TEXTURE;
	data->shape.texture = LoadTexture(filename);
	data->shape.texture_size = (scaffold_vector2){data->shape.texture.width, data->shape.texture.height};

	return sprite;
}

scaffold_node* mason_rectangle_create(scaffold_node* drawer, int draw_order, scaffold_vector2 size) {
	scaffold_node* sprite = create_sprite(drawer, draw_order);
	mason_sprite_data* data = (mason_sprite_data*)(sprite->data);

	data->shape.type = MASON_SPR_RECTANGLE;
	data->shape.rect_size = size;

	return sprite;
}

scaffold_node* mason_label_create(scaffold_node* drawer, int draw_order, const char* text, int font_size) {
	scaffold_node* sprite = create_sprite(drawer, draw_order);
	mason_sprite_data* data = (mason_sprite_data*)(sprite->data);

	data->shape.type = MASON_SPR_LABEL;
	data->shape.text = text;
	data->shape.font_size = font_size;

	return sprite;
}

