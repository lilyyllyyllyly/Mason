#include <stdlib.h>

#include "scaffold.h"
#include "mason.h"

#include "layers.h"

#define SPEED -300
#define SIZE 5

static void on_collision(scaffold_node* this, scaffold_node* other) {
	scaffold_queue_destroy(this->parent);
}

scaffold_node* bullet_create(scaffold_node* drawer, scaffold_node* col_handler) {
	scaffold_node* bullet = mason_body_create();
	((mason_body_data*)(bullet->data))->vel.y = SPEED;

	scaffold_node* sprite = mason_rectangle_create(drawer, (scaffold_vector2){SIZE, SIZE});
	scaffold_node_add_child(bullet, sprite);

	scaffold_node* collider = mason_circle_collider_create(col_handler, LAYER_BULLET, LAYER_ASTEROID, SIZE, on_collision);
	scaffold_node_add_child(bullet, collider);

	return bullet;
}

