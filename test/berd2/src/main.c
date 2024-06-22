#include <stdio.h>
#include <signal.h>

#include "scaffold.h"
#include "mason.h"

#include "bird.h"

#define WIN_W 800
#define WIN_H 600
#define FPS 0

int end = 0;

void handle_interrupt(int signal) {
	puts("\nQuitting.");
	end = 1;
}

int main() {
	signal(SIGINT, handle_interrupt);

	scaffold_node* root = scaffold_initialize();

	scaffold_node* drawer = mason_drawer_create(WIN_W, WIN_H, "berd 2: electric boogaloo", FPS);
	scaffold_node_add_child(root, drawer);

	scaffold_node* bird = bird_create(drawer);
	scaffold_node_add_child(root, bird);

	while(!end) {
		scaffold_process_cleanup(root, mason_drawer_frame_time());
	}

	root->destroy(root);
}

