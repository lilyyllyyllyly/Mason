#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "scaffold.h"
#include "mason_rng.h"

#include "body.h"
#include "sprite.h"

#include "collider.h"
#include "layers.h"

#define SPRITE_PATH "assets/asteroid.png"

#define ANGLE_RANGE 1.5f
#define SPEED 60
#define COL_RADIUS 16

scaffold_node* create_asteroid(scaffold_node* drawer, scaffold_node* col_handler) {
	scaffold_node* asteroid = create_body();
	body_data* data = asteroid->data;

	// randomizing velocity vector direction
	float r = mason_randf_range(-ANGLE_RANGE, ANGLE_RANGE)/2 + M_PI_2;
	data->vel.x = cosf(r) * SPEED;
	data->vel.y = sinf(r) * SPEED;

	scaffold_node* sprite = create_sprite(drawer, SPRITE_PATH);
	scaffold_node_add_child(asteroid, sprite);

	scaffold_node* collider = create_circle_collider(col_handler, LAYER_ASTEROID, 0, COL_RADIUS, NULL);
	collider->local_pos = (scaffold_vector2){COL_RADIUS, COL_RADIUS};
	scaffold_node_add_child(asteroid, collider);

	return asteroid;
}

