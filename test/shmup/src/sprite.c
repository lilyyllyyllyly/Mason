#include <stdlib.h>

#include "scaffold.h"
#include "drawer.h"

int sprite_type = NODE_TYPE_UNASSIGNED;

scaffold_node* create_sprite(scaffold_node* drawer, const char* filename) {
	scaffold_node* sprite = scaffold_node_create(
		&sprite_type,
		NULL,
		NULL,
		NULL
	);

	drawer_add_sprite(drawer, sprite, filename);

	return sprite;
}

