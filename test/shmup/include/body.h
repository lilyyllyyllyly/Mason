#pragma once

#include "scaffold.h"

typedef struct {
	scaffold_vector2 vel;
} body_data;

scaffold_node* create_body();

