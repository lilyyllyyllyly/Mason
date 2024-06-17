#include <stdlib.h>

#include "scaffold.h"

int node_follower_type = NODE_TYPE_UNASSIGNED;

#include "node_follower.h"

static void destroy(scaffold_node* follower) {
	free(follower->data);
	scaffold_node_destroy(follower);
}

static void process(scaffold_node* follower, double delta) {
	node_follower_data* data = (node_follower_data*)(follower->data);

	scaffold_vector2 diff = scaffold_vector2_sub(data->target->global_pos, follower->global_pos);

	scaffold_vector2 move = scaffold_vector2_clamp_mag(diff, 0.0f, data->speed * delta);

	scaffold_node_set_global_pos(follower, scaffold_vector2_add(follower->global_pos, move));
}

scaffold_node* node_follower_create(scaffold_node* target, float speed) {
	node_follower_data* data = malloc(sizeof(node_follower_data));
	data->target = target;
	data->speed = speed;

	return scaffold_node_create(
		&node_follower_type,
		(void*)data,
		process,
		destroy
	);
}

