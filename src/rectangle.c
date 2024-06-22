#include <stdlib.h>

#include "scaffold.h"
#include "mason_drawer_internal.h"

int mason_rectangle_type = NODE_TYPE_UNASSIGNED;

scaffold_node* mason_rectangle_create(scaffold_node* drawer, scaffold_vector2 size) {
	scaffold_node* rect = scaffold_node_create(
		&mason_rectangle_type,
		NULL,
		NULL,
		NULL
	);

	drawer_add_rectangle(drawer, rect, size);

	return rect;
}

