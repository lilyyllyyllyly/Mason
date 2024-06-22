#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"
#include "mason.h"

#include "gravity.h"

#include "layers.h"

#define WIDTH  64
#define HEIGHT 64

#define X_POS 200

#define JUMP_FORCE -350;

int bird_type = NODE_TYPE_UNASSIGNED;
int jump_type = NODE_TYPE_UNASSIGNED;

static void on_collision(scaffold_node* this, scaffold_node* other) {
	scaffold_queue_destroy(this->parent);
}

static void jump_process(scaffold_node* jump, double delta) {
	if (!IsKeyPressed(KEY_SPACE)) return;

	mason_body_data* body_data = (mason_body_data*)(jump->parent->data);
	body_data->vel.y = JUMP_FORCE;
}

scaffold_node* bird_create(scaffold_node* col_handler, scaffold_node* drawer) {
	scaffold_node* bird = mason_body_create();

	scaffold_node* jump = scaffold_node_create(
		&jump_type,
		NULL,
		jump_process,
		NULL
	);
	scaffold_node_add_child(bird, jump);

	scaffold_node* collider = create_rect_collider(col_handler, LAYER_BIRD, LAYER_OBSTACLE, (scaffold_vector2){WIDTH, HEIGHT}, on_collision);
	scaffold_node_add_child(bird, collider);

	scaffold_vector2 game_size = mason_drawer_game_size(drawer);
	bird->local_pos = (scaffold_vector2){X_POS, (game_size.y - HEIGHT)/2};

	scaffold_node* gravity = gravity_create();
	gravity->data = bird;
	scaffold_node_add_child(bird, gravity);

	scaffold_node* sprite = mason_rectangle_create(drawer, (scaffold_vector2){WIDTH, HEIGHT});
	scaffold_node_add_child(bird, sprite);

	return bird;
}

