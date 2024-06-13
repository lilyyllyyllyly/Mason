#include <stdio.h>
#include <signal.h>

#include "scaffold.h"

#include "drawer.h"
#include "collision_handler.h"
#include "mouse_follower.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid_spawner.h"

#define WIN_W 320
#define WIN_H 240
#define WIN_TITLE "graphics test"
#define FPS 60

#define SHIP_SPRITE "assets/ship1.png"
#define SHIP_SPEED 60

char end = 0;

void handle_interrupt(int signal) {
	printf("\nQuitting.\n");
	end = 1;
}

int main() {
	signal(SIGINT, handle_interrupt);

	scaffold_node* root = scaffold_initialize();

	scaffold_node* col_handler = create_collision_handler();
	scaffold_node_add_child(root, col_handler);

	scaffold_node* drawer = create_drawer(WIN_W, WIN_H, WIN_TITLE, FPS);
	scaffold_node_add_child(root, drawer);

	scaffold_node* mouse = create_mouse_follower(drawer);
	scaffold_node_add_child(root, mouse);

	scaffold_node* ship = create_ship(drawer, col_handler, mouse);
	scaffold_node_add_child(root, ship);
	ship->local_pos = (scaffold_vector2){WIN_W/2, WIN_H/2};

	scaffold_node* bullet = create_bullet(drawer);
	scaffold_node_add_child(root, bullet);
	bullet->local_pos = ship->local_pos;
	
	scaffold_node* asteroid = create_asteroid_spawner(drawer, col_handler);
	scaffold_node_add_child(root, asteroid);

	while (!end) {
		scaffold_process_cleanup(root, drawer_get_frame_time());
	}

	root->destroy(root);
}

