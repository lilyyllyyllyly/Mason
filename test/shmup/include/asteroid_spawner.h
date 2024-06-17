#pragma once

#include "scaffold.h"

typedef struct {
	scaffold_node* drawer;
	scaffold_node* col_handler;
	double spawn_timer;
} asteroid_spawner_data;

scaffold_node* asteroid_spawner_create(scaffold_node* drawer, scaffold_node* col_handler);

