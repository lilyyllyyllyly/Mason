#include <stdlib.h>

#include "scaffold.h"

#include "body.h"
#include "rectangle.h"

#define SPEED -300
#define WIDTH  5
#define HEIGHT 5

scaffold_node* create_bullet(scaffold_node* drawer) {
	scaffold_node* bullet = create_body();
	((body_data*)(bullet->data))->vel.y = SPEED;

	scaffold_node* sprite = create_rectangle(drawer, (scaffold_vector2){WIDTH, HEIGHT});
	scaffold_node_add_child(bullet, sprite);

	return bullet;
}

