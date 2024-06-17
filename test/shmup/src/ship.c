#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "mason.h"

#include "node_follower.h"
#include "bullet.h"

#include "layers.h"

#define SPRITE_PATH "assets/ship1.png"

#define SPEED 100
#define COL_RADIUS 8

int shooter_type = NODE_TYPE_UNASSIGNED;

#include "ship.h"

static void on_collision(scaffold_node* this, scaffold_node* other) {
	scaffold_queue_destroy(this->parent);
}

static void process(scaffold_node* shooter, double delta) {
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;

	shooter_data* data = (shooter_data*)(shooter->data);

	scaffold_node* ship = shooter->parent;
	if (ship == NULL) return;

	scaffold_node* root = ship->parent;
	if (root == NULL) return;

	scaffold_node* bullet = bullet_create(data->drawer, data->col_handler);
	scaffold_node_add_child(root, bullet);
	bullet->local_pos = ship->local_pos;
}

static void destroy(scaffold_node* shooter) {
	free(shooter->data);
	scaffold_node_destroy(shooter);
}

scaffold_node* ship_create(scaffold_node* drawer, scaffold_node* col_handler, scaffold_node* mouse) {
	scaffold_node* ship = node_follower_create(mouse, SPEED);

	shooter_data* data = malloc(sizeof(shooter_data));
	data->drawer = drawer;
	data->col_handler = col_handler;
	scaffold_node* shooter = scaffold_node_create(
		&shooter_type,
		data,
		process,
		destroy
	);
	scaffold_node_add_child(ship, shooter);

	scaffold_node* sprite = mason_sprite_create(drawer, SPRITE_PATH);
	scaffold_node_add_child(ship, sprite);

	scaffold_node* collider = mason_circle_collider_create(col_handler, LAYER_SHIP, LAYER_ASTEROID, COL_RADIUS, on_collision);
	collider->local_pos = (scaffold_vector2){COL_RADIUS, COL_RADIUS};
	scaffold_node_add_child(ship, collider);

	return ship;
}

