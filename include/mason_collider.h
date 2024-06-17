#pragma once

#include "scaffold.h"

extern int mason_collider_type;

typedef enum {
	CIRCLE_SHAPE = 0,	
} mason_shape_type;

typedef struct {
	float radius;
} mason_circle_shape;

typedef struct {
	unsigned int layer;
	unsigned int mask;

	mason_shape_type type;
	union {
		mason_circle_shape circle;
	} shape;

	void (*on_collision)(scaffold_node*, scaffold_node*);

	scaffold_node* col_handler;
	scaffold_list* elem;
} mason_collider_data;

scaffold_node* mason_circle_collider_create(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, float radius, void (*on_collision)(scaffold_node*, scaffold_node*));

