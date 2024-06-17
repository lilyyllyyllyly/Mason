#include <stdio.h>
#include <signal.h>

#include "scaffold.h"
#include "mason.h"

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

	scaffold_node* col_handler = mason_collision_handler_create();
	scaffold_node_add_child(root, col_handler);

	scaffold_node* drawer = mason_drawer_create(WIN_W, WIN_H, WIN_TITLE, FPS);
	scaffold_node_add_child(root, drawer);

	scaffold_node* mouse = mouse_follower_create(drawer);
	scaffold_node_add_child(root, mouse);

	scaffold_node* ship = ship_create(drawer, col_handler, mouse);
	scaffold_node_add_child(root, ship);
	ship->local_pos = (scaffold_vector2){WIN_W/2, WIN_H/2};
	
	scaffold_node* asteroid = asteroid_spawner_create(drawer, col_handler);
	scaffold_node_add_child(root, asteroid);

	while (!end) {
		scaffold_process_cleanup(root, mason_drawer_frame_time());
	}

	root->destroy(root);
}

