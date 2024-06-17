#include <stdlib.h>
#include <math.h>

#include "scaffold.h"
#include "mason.h"

#include "layers.h"

#define SPRITE_PATH "assets/asteroid.png"

#define ANGLE_RANGE 1.5f
#define SPEED 60
#define COL_RADIUS 16

static void on_collision(scaffold_node* this, scaffold_node* other) {
	scaffold_queue_destroy(this->parent);
}

scaffold_node* asteroid_create(scaffold_node* drawer, scaffold_node* col_handler) {
	scaffold_node* asteroid = mason_body_create();
	mason_body_data* data = asteroid->data;

	// randomizing velocity vector direction
	float r = mason_randf_range(-ANGLE_RANGE, ANGLE_RANGE)/2 + M_PI_2;
	data->vel.x = cosf(r) * SPEED;
	data->vel.y = sinf(r) * SPEED;

	scaffold_node* sprite = mason_sprite_create(drawer, SPRITE_PATH);
	scaffold_node_add_child(asteroid, sprite);

	scaffold_node* collider = mason_circle_collider_create(col_handler, LAYER_ASTEROID, LAYER_BULLET, COL_RADIUS, on_collision);
	collider->local_pos = (scaffold_vector2){COL_RADIUS, COL_RADIUS};
	scaffold_node_add_child(asteroid, collider);

	return asteroid;
}

