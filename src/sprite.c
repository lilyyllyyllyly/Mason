#include <stdlib.h>

#include "scaffold.h"
#include "mason_drawer_internal.h"

int mason_sprite_type = NODE_TYPE_UNASSIGNED;

scaffold_node* mason_sprite_create(scaffold_node* drawer, const char* filename) {
	scaffold_node* sprite = scaffold_node_create(
		&mason_sprite_type,
		NULL,
		NULL,
		NULL
	);

	drawer_add_sprite(drawer, sprite, filename);

	return sprite;
}

