#pragma once

typedef enum {
	MASON_CIRCLE = 0,
	MASON_RECTANGLE
} mason_shape_type;

typedef struct {
	mason_shape_type type;
	union {
		float radius;
		scaffold_vector2 size;
	} u;
} mason_shape;

