#include <stdio.h>
#include <stdlib.h>

#include "scaffold.h"
#include "node_follower.h"
#include "sprite.h"

#include "collider.h"
#include "layers.h"

#define SPRITE_PATH "assets/ship1.png"

#define SPEED 100
#define COL_RADIUS 8

static void on_collision(scaffold_node* this, scaffold_node* other) {
	scaffold_queue_destroy(this->parent);
}

scaffold_node* create_ship(scaffold_node* drawer, scaffold_node* col_handler, scaffold_node* mouse) {
	scaffold_node* ship = create_node_follower(mouse, SPEED);

	scaffold_node* sprite = create_sprite(drawer, SPRITE_PATH);
	scaffold_node_add_child(ship, sprite);

	scaffold_node* collider = create_circle_collider(col_handler, LAYER_SHIP, LAYER_ASTEROID, COL_RADIUS, on_collision);
	collider->local_pos = (scaffold_vector2){COL_RADIUS, COL_RADIUS};
	scaffold_node_add_child(ship, collider);

	return ship;
}

