#include <stdlib.h>

#include "scaffold.h"

int mason_body_type = NODE_TYPE_UNASSIGNED;

#include "mason_body.h"

static void destroy(scaffold_node* body) {
	free(body->data);
	scaffold_node_destroy(body);
}

static void process(scaffold_node* body, double delta) {
	mason_body_data* data = (mason_body_data*)(body->data);
	body->local_pos = scaffold_vector2_add(body->local_pos, scaffold_vector2_scale(data->vel, delta));
}

scaffold_node* mason_body_create() {
	mason_body_data* data = malloc(sizeof(mason_body_data));
	data->vel = (scaffold_vector2){0, 0};

	return scaffold_node_create(
		&mason_body_type,
		data,
		process,
		destroy
	);
}

