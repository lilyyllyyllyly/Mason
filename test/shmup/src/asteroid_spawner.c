#include <stdlib.h>

#include "scaffold.h"
#include "mason.h"

#include "asteroid.h"
#include "asteroid_spawner.h"

#define SPAWN_TIME 1.5
#define POS_Y -50

int asteroid_spawner_type = NODE_TYPE_UNASSIGNED;

static void destroy(scaffold_node* spawner) {
	free(spawner->data);
	scaffold_node_destroy(spawner);
}

static void process(scaffold_node* spawner, double delta) {
	asteroid_spawner_data* data = (asteroid_spawner_data*)(spawner->data);

	data->spawn_timer += delta;
	if (data->spawn_timer < SPAWN_TIME) return;

	data->spawn_timer = 0.0;

	scaffold_node* asteroid = asteroid_create(data->drawer, data->col_handler);
	scaffold_node_add_child(spawner, asteroid);

	float game_w = mason_drawer_game_size(data->drawer).x;
	asteroid->local_pos.x = mason_randf_range(0.0f, game_w);
	asteroid->local_pos.y = POS_Y;
}

scaffold_node* asteroid_spawner_create(scaffold_node* drawer, scaffold_node* col_handler) {
	asteroid_spawner_data* data = malloc(sizeof(asteroid_spawner_data));
	data->drawer = drawer;
	data->col_handler = col_handler;
	data->spawn_timer = 0.0;

	return scaffold_node_create(
		&asteroid_spawner_type,
		data,
		process,
		destroy
	);
}

