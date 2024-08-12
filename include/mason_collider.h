#pragma once

#include "scaffold.h"
#include "mason_shape.h"

extern int mason_collider_type;

typedef enum {
	MASON_COL_CIRCLE = 0,
	MASON_COL_RECTANGLE
} mason_collision_shape;

typedef struct {
	unsigned int layer;
	unsigned int mask;

	struct {
		mason_collision_shape type;
		union {
			float radius;
			scaffold_vector2 size;
		};
	} shape;

	void (*on_collision)(scaffold_node*, scaffold_node*);

	scaffold_node* col_handler;
	scaffold_list* elem;
} mason_collider_data;

scaffold_node* mason_circle_collider_create(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, float radius, void (*on_collision)(scaffold_node*, scaffold_node*));

scaffold_node* mason_rect_collider_create(scaffold_node* collision_handler, unsigned int layer, unsigned int mask, scaffold_vector2 size, void (*on_collision)(scaffold_node*, scaffold_node*));

