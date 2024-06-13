#pragma once

#include "scaffold.h"

typedef enum {
	CIRCLE_SHAPE = 0,	
} shape_type;

typedef struct {
	float radius;
} circle_shape;

typedef struct {
	unsigned int layer;
	unsigned int mask;

	shape_type type;
	union {
		circle_shape circle;
	} shape;

	void (*on_collision)(scaffold_node*, scaffold_node*);

	scaffold_node* col_handler;
	scaffold_list* elem;
} collider_data;

scaffold_node* create_circle_collider(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, float radius, void (*on_collision)(scaffold_node*, scaffold_node*));

