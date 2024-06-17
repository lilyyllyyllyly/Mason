#pragma once

#include "scaffold.h"

typedef struct {
	scaffold_node* drawer;
	scaffold_node* col_handler;
} shooter_data;

scaffold_node* ship_create(scaffold_node* drawer, scaffold_node* col_handler, scaffold_node* mouse);

