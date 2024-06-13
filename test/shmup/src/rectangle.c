#include <stdlib.h>

#include "scaffold.h"
#include "drawer.h"

int rectangle_type = NODE_TYPE_UNASSIGNED;

#include "rectangle.h"

scaffold_node* create_rectangle(scaffold_node* drawer, scaffold_vector2 size) {
	scaffold_node* rect = scaffold_node_create(
		&rectangle_type,
		NULL,
		NULL,
		NULL
	);

	drawer_add_rectangle(drawer, rect, size);

	return rect;
}

