#include <stdlib.h>

#include "scaffold.h"
#include "mason_drawer_internal.h"

int mason_rectangle_type = NODE_TYPE_UNASSIGNED;

#include "mason_rectangle.h"

static void destroy(scaffold_node* rect) {
	mason_rectangle_data* data = (mason_rectangle_data*)(rect->data);

	drawer_delete_sprite(data->drawer, data->elem);
	free(rect->data);
	scaffold_node_destroy(rect);
}

scaffold_node* mason_rectangle_create(scaffold_node* drawer, scaffold_vector2 size) {
	mason_rectangle_data* data = malloc(sizeof(mason_rectangle_data));
	data->drawer = (mason_drawer_data*)(drawer->data);
	data->size = size;

	scaffold_node* rect = scaffold_node_create(
		&mason_rectangle_type,
		data,
		NULL,
		destroy
	);

	data->elem = drawer_add_rectangle(drawer, rect, size);

	return rect;
}

