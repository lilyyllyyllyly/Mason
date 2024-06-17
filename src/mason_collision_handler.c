#include <stdlib.h>
#include <stdint.h>

#include "scaffold.h"

#include "mason_collider.h"

int collision_handler_type = NODE_TYPE_UNASSIGNED;

void collision_handler_delete_collider(scaffold_node* handler, scaffold_list* elem) {
	handler->data = scaffold_list_delete_element((scaffold_list*)(handler->data), elem);
}

scaffold_list* collision_handler_add_collider(scaffold_node* handler, scaffold_node* col) {
	handler->data = scaffold_list_insert((scaffold_list*)(handler->data), col);
	return (scaffold_list*)(handler->data);
}

static int circle_circle_collision(scaffold_node* col, scaffold_node* other) {
	float col_r   = ((mason_collider_data*)(col->data))->shape.circle.radius;
	float other_r = ((mason_collider_data*)(other->data))->shape.circle.radius;

	return scaffold_vector2_distance(col->global_pos, other->global_pos) <= col_r + other_r;
}

static void process(scaffold_node* handler, double delta) {
	scaffold_list* elem = (scaffold_list*)(handler->data);

	while (elem != NULL) {
		scaffold_list* other_elem = elem->next;

		while (other_elem != NULL) {
			scaffold_node* col   = (scaffold_node*)(elem->data);
			scaffold_node* other = (scaffold_node*)(other_elem->data);

			mason_collider_data* col_data   = (mason_collider_data*)(col->data);
			mason_collider_data* other_data = (mason_collider_data*)(other->data);

			int col_collides   = col_data->mask & other_data->layer;
			int other_collides = other_data->mask & col_data->layer;

			if (!col_collides && !other_collides) goto next;

			if (col_data->type == other_data->type && col_data->type == CIRCLE_SHAPE) {
				if (circle_circle_collision(col, other)) {
					if (col_collides && col_data->on_collision != NULL) {
						col_data->on_collision(col, other);
					}

					if (other_collides && other_data->on_collision != NULL) {
						other_data->on_collision(other, col);
					}
				}
			}

next:
			other_elem = other_elem->next;
		}

		elem = elem->next;
	}
}

static void destroy(scaffold_node* handler) {
	scaffold_list_destroy((scaffold_list*)(handler->data));
	scaffold_node_destroy(handler);
}

scaffold_node* mason_collision_handler_create() {
	return scaffold_node_create(
		&collision_handler_type,
		NULL,
		process,
		destroy
	);
}

