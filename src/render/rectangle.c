#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "render/mason_sprite.h"

int mason_rectangle_type = NODE_TYPE_UNASSIGNED;

#include "render/mason_rectangle.h"

static void destroy(scaffold_node* rectangle) {
	mason_rectangle_data* data = (mason_rectangle_data*)(rectangle->data);

	mason_sprite_data_destroy(data->sprite);
	free(data);

	scaffold_node_destroy(rectangle);
}

static void draw(scaffold_node* rect) {
	scaffold_vector2 size = ((mason_rectangle_data*)rect->data)->size;
	DrawRectangle(rect->global_pos.x, rect->global_pos.y, size.x, size.y, BLACK);
}

scaffold_node* mason_rectangle_create(scaffold_node* drawer, int draw_order, scaffold_vector2 size) {
	mason_rectangle_data* data = malloc(sizeof(mason_rectangle_data));

	scaffold_node* rectangle = scaffold_node_create(
		&mason_rectangle_type,
		data,
		NULL,
		destroy
	);

	data->size = size;
	data->sprite = mason_sprite_data_create(rectangle, drawer, draw_order, draw);

	return rectangle;
}

