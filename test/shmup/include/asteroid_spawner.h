#pragma once

#include "scaffold.h"

typedef struct {
	scaffold_node* drawer;
	scaffold_node* col_handler;
	double spawn_timer;
} asteroid_spawner_data;

scaffold_node* create_asteroid_spawner(scaffold_node* drawer, scaffold_node* col_handler);

