#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "mason.h"

int mouse_follower_type = NODE_TYPE_UNASSIGNED;

static void process(scaffold_node* follower, double delta) {
	scaffold_vector2 screen_mouse_pos = (scaffold_vector2){GetMouseX(), GetMouseY()};
	follower->local_pos = mason_drawer_screen_to_game_pos((scaffold_node*)(follower->data), screen_mouse_pos);
}

scaffold_node* mouse_follower_create(scaffold_node* drawer) {
	return scaffold_node_create(
		&mouse_follower_type,
		(void*)drawer,
		process,
		NULL
	);
}

