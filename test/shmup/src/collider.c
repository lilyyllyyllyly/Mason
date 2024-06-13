#include <stdio.h>
#include <stdlib.h>

#include "scaffold.h"

#include "collision_handler.h"

int collider_type = NODE_TYPE_UNASSIGNED;

#include "collider.h"

static void destroy(scaffold_node* col) {
	collider_data* data = (collider_data*)(col->data);
	collision_handler_delete_collider(data->col_handler, data->elem);
	free(data);
	scaffold_node_destroy(col);
}

scaffold_node* create_collider(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, void (*on_collision)(scaffold_node*, scaffold_node*)) {
	collider_data* data = calloc(1, sizeof(collider_data));
	data->layer = layer;
	data->mask  = mask;
	data->on_collision = on_collision;
	data->col_handler = collision_handler;

	scaffold_node* col = scaffold_node_create(
		&collider_type,
		data,
		NULL,
		destroy
	);

	data->elem = collision_handler_add_collider(collision_handler, col);

	return col;
}

scaffold_node* create_circle_collider(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, float radius, void (*on_collision)(scaffold_node*, scaffold_node*)) {
	scaffold_node* circle = create_collider(collision_handler, layer, mask, on_collision);

	collider_data* data = (collider_data*)(circle->data);
	data->type = CIRCLE_SHAPE;
	data->shape.circle.radius = radius;

	return circle;
}

