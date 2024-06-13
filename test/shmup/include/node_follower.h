#pragma once

#include "scaffold.h"

extern int node_follower_type;

typedef struct {
	scaffold_node* target;
	int speed;
} node_follower_data;

scaffold_node* create_node_follower(scaffold_node* target, float speed);

