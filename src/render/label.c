#include <stdlib.h>
#include <string.h>

#include "scaffold.h"
#include "render/mason_sprite.h"

int mason_label_type = NODE_TYPE_UNASSIGNED;

#include "render/mason_label.h"

static void destroy(scaffold_node* label) {
	mason_label_data* data = (mason_label_data*)(label->data);

	mason_sprite_data_destroy(data->sprite);

	if (data->format) free(data->text);

	free(data);
	scaffold_node_destroy(label);
}

static void draw(scaffold_node* label) {
	mason_label_data* data = (mason_label_data*)(label->data);
	DrawText(data->text, label->global_pos.x, label->global_pos.y, data->font_size, BLACK);
}

scaffold_node* mason_label_create(scaffold_node* drawer, int draw_order, char* text, int font_size, int format) {
	mason_label_data* data = malloc(sizeof(mason_label_data));

	scaffold_node* label = scaffold_node_create(
		&mason_label_type,
		data,
		NULL,
		destroy
	);

	data->font_size = font_size;
	data->format = format;

	if (format) {
		size_t text_len = strlen(text) + 1;
		data->text = malloc(text_len);
		memcpy(data->text, text, text_len);
	} else {
		data->text = text;
	}

	data->sprite = mason_sprite_data_create(label, drawer, draw_order, draw);

	return label;
}

