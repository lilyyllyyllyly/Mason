#pragma once

#include "scaffold.h"

extern int mason_body_type;

typedef struct {
	scaffold_vector2 vel;
} mason_body_data;

scaffold_node* mason_body_create();

