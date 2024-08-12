#include <stdlib.h>

#include "scaffold.h"

#include "mason_collision_handler_internal.h"

int mason_collider_type = NODE_TYPE_UNASSIGNED;

#include "mason_collider.h"

static void destroy(scaffold_node* col) {
	mason_collider_data* data = (mason_collider_data*)(col->data);
	collision_handler_delete_collider(data->col_handler, data->elem);
	free(data);
	scaffold_node_destroy(col);
}

static scaffold_node* create_collider(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, void (*on_collision)(scaffold_node*, scaffold_node*)) {
	mason_collider_data* data = calloc(1, sizeof(mason_collider_data));
	data->layer = layer;
	data->mask  = mask;
	data->on_collision = on_collision;
	data->col_handler = collision_handler;

	scaffold_node* col = scaffold_node_create(
		&mason_collider_type,
		data,
		NULL,
		destroy
	);

	data->elem = collision_handler_add_collider(collision_handler, col);

	return col;
}

scaffold_node* mason_circle_collider_create(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, float radius, void (*on_collision)(scaffold_node*, scaffold_node*)) {
	scaffold_node* circle = create_collider(collision_handler, layer, mask, on_collision);

	mason_collider_data* data = (mason_collider_data*)(circle->data);
	data->shape.type = MASON_COL_CIRCLE;
	data->shape.radius = radius;

	return circle;
}

scaffold_node* mason_rect_collider_create(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, scaffold_vector2 size, void (*on_collision)(scaffold_node*, scaffold_node*)) {
	scaffold_node* rect = create_collider(collision_handler, layer, mask, on_collision);

	mason_collider_data* data = (mason_collider_data*)(rect->data);
	data->shape.type = MASON_COL_RECTANGLE;
	data->shape.size = size;

	return rect;
}

