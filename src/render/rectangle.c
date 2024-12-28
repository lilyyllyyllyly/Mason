#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "render/mason_sprite.h"

int mason_rectangle_type = NODE_TYPE_UNASSIGNED;

#include "render/mason_rectangle.h"

void mason_rectangle_set_color(scaffold_node* rect, Color color) {
	((mason_rectangle_data*)(rect->data))->color = color;
}

static void destroy(scaffold_node* rectangle) {
	mason_rectangle_data* data = (mason_rectangle_data*)(rectangle->data);

	mason_sprite_data_destroy(data->sprite);
	free(data);

	scaffold_node_destroy(rectangle);
}

static void draw(scaffold_node* rect) {
	mason_rectangle_data* rect_d = rect->data;
	scaffold_vector2 size = rect_d->size;
	DrawRectangle(rect->global_pos.x, rect->global_pos.y, size.x, size.y, rect_d->color);
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
	data->color = BLACK;
	data->sprite = mason_sprite_data_create(rectangle, drawer, draw_order, draw);

	return rectangle;
}

