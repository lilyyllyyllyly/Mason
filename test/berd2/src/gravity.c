#include <stdlib.h>

#include "scaffold.h"
#include "mason.h"

#define GRAVITY 1000

int gravity_type = NODE_TYPE_UNASSIGNED;

void process(scaffold_node* grav, double delta) {
	if (grav->data == NULL) return;

	scaffold_node* body = (scaffold_node*)(grav->data);
	mason_body_data* body_data = (mason_body_data*)(body->data);
	body_data->vel.y = body_data->vel.y + GRAVITY * delta;
}

scaffold_node* gravity_create() {
	return scaffold_node_create(
		&gravity_type,
		NULL,
		process,
		NULL
	);
}

