#include <stdlib.h>
#include <stdint.h>

#include "scaffold.h"

#include "mason.h"

int mason_collision_handler_type = NODE_TYPE_UNASSIGNED;

void collision_handler_delete_collider(scaffold_node* handler, scaffold_list* elem) {
	handler->data = scaffold_list_delete_element((scaffold_list*)(handler->data), elem);
}

scaffold_list* collision_handler_add_collider(scaffold_node* handler, scaffold_node* col) {
	handler->data = scaffold_list_insert((scaffold_list*)(handler->data), col);
	return (scaffold_list*)(handler->data);
}

static int circle_circle_collision(scaffold_node* col, scaffold_node* other) {
	float col_r   = ((mason_collider_data*)(col->data))->shape.radius;
	float other_r = ((mason_collider_data*)(other->data))->shape.radius;

	return scaffold_vector2_distance(col->global_pos, other->global_pos) <= col_r + other_r;
}

static int rect_rect_collision(scaffold_node* col, scaffold_node* other) {
	scaffold_vector2 col_size   = ((mason_collider_data*)(col->data))->shape.size;
	scaffold_vector2 other_size = ((mason_collider_data*)(other->data))->shape.size;

	return col->global_pos.x < other->global_pos.x + other_size.x &&
	       col->global_pos.x + col_size.x >   other->global_pos.x &&
	       col->global_pos.y < other->global_pos.y + other_size.y &&
	       col->global_pos.y + col_size.y >   other->global_pos.y;
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

			if (col_data->shape.type == MASON_COL_CIRCLE && other_data->shape.type == MASON_COL_CIRCLE) {
				if (circle_circle_collision(col, other)) {
					if (col_collides && col_data->on_collision != NULL) {
						col_data->on_collision(col, other);
					}

					if (other_collides && other_data->on_collision != NULL) {
						other_data->on_collision(other, col);
					}
				}
				goto next;
			}

			if (col_data->shape.type == MASON_COL_RECTANGLE && col_data->shape.type == MASON_COL_RECTANGLE) {
				if (rect_rect_collision(col, other)) {
					if (col_collides && col_data->on_collision != NULL) {
						col_data->on_collision(col, other);
					}

					if (other_collides && other_data->on_collision != NULL) {
						other_data->on_collision(other, col);
					}
				}
				goto next;
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
		&mason_collision_handler_type,
		NULL,
		process,
		destroy
	);
}

