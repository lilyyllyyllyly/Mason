#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"

#include "mason_sprite.h"

int mason_drawer_type = NODE_TYPE_UNASSIGNED;

#include "mason_drawer.h"

int mason_drawer_get_text_width(const char* text, int font_size) {
	return MeasureText(text, font_size);
}

scaffold_vector2 mason_drawer_get_image_size(const char* filename) {
	Image img = LoadImage(filename);
	scaffold_vector2 size = (scaffold_vector2){img.width, img.height};
	UnloadImage(img);
	return size;
}

double mason_drawer_get_frame_time() {
	return GetFrameTime();
}

scaffold_vector2 mason_drawer_get_game_size(scaffold_node* drawer) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);
	return data->game_size;
}

void mason_drawer_set_game_size(scaffold_node* drawer, int width, int height) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);
	UnloadRenderTexture(data->target);
	data->target = LoadRenderTexture(width, height);
}

void mason_drawer_set_game_size_vec(scaffold_node* drawer, scaffold_vector2 size) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);
	UnloadRenderTexture(data->target);
	data->target = LoadRenderTexture(size.x, size.y);
}

scaffold_vector2 mason_drawer_get_window_size() {
	return (scaffold_vector2){(float)GetScreenWidth(), (float)GetScreenHeight()};
}

void mason_drawer_set_window_size(int width, int height) {
	SetWindowSize(width, height);
}

void mason_drawer_set_window_size_vec(scaffold_vector2 size) {
	SetWindowSize(size.x, size.y);
}

void update_game_dimensions(mason_drawer_data* data) {
	float scr_w = (float)GetScreenWidth();
	float scr_h = (float)GetScreenHeight();

	float game_w = (float)(data->target.texture.width);
	float game_h = (float)(data->target.texture.height);

	float dst_w, dst_h, dst_x, dst_y;

	if ((scr_w/scr_h) > (game_w/game_h)) {
		dst_h = scr_h;
		dst_w = game_w * (scr_h/game_h);
	} else {
		dst_w = scr_w;
		dst_h = game_h * (scr_w/game_w);
	}

	dst_x = (scr_w - dst_w)/2;
	dst_y = (scr_h - dst_h)/2;

	data->scr_size.x = scr_w;
	data->scr_size.y = scr_h;

	data->game_size.x = game_w;
	data->game_size.y = game_h;

	data->dst_pos.x = dst_x;
	data->dst_pos.y = dst_y;
	data->dst_size.x = dst_w;
	data->dst_size.y = dst_h;
}

scaffold_vector2 mason_drawer_screen_to_game_pos(scaffold_node* drawer, scaffold_vector2 pos) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);

	update_game_dimensions(data);
	
	int dst_x = data->dst_pos.x;
	int dst_y = data->dst_pos.y;
	int dst_w = data->dst_size.x;
	int dst_h = data->dst_size.y;
	int game_w = data->game_size.x;
	int game_h = data->game_size.y;

	int ret_x = (pos.x - dst_x) * game_w / dst_w;
	int ret_y = (pos.y - dst_y) * game_h / dst_h;
	return (scaffold_vector2){ret_x, ret_y};
}

scaffold_list* drawer_add_sprite(mason_drawer_data* drawer, scaffold_node* sprite) {
	mason_sprite_data* spr_data = (mason_sprite_data*)(sprite->data);

	// loop through the sprites list until a sprite with the same or higher draw_order is found
	for (scaffold_list* elem = drawer->sprites; elem != NULL; elem = elem->next) {
		mason_sprite_data* elem_data = (mason_sprite_data*)(((scaffold_node*)(elem->data))->data);

		// draw order of current element higher or equal, insert the new sprite before that element
		if (elem_data->draw_order >= spr_data->draw_order) {
			// if this is the first element, the list needs to be updated
			if (elem == drawer->sprites) {
				return drawer->sprites = scaffold_list_insert(elem, (void*)sprite);
			}

			return scaffold_list_insert(elem, (void*)sprite);
		}

		// draw order smaller

		// this is the last element in the list, append the sprite after it no matter what
		if (elem->next == NULL) {
			// list is definitely not null here, no need to check before append
			return scaffold_list_append(elem, (void*)sprite);
		}
	}

	// we only get here if the list is NULL, so just insert the element
	return drawer->sprites = scaffold_list_insert(drawer->sprites, (void*)sprite);
}

void drawer_delete_sprite(mason_drawer_data* drawer, scaffold_list* elem) {
	drawer->sprites = scaffold_list_delete_element(drawer->sprites, elem);
}

static void draw_rectangle(scaffold_node* rect, mason_sprite_data* data) {
	scaffold_vector2 size = data->shape.rect_size;
	DrawRectangle(rect->global_pos.x, rect->global_pos.y, size.x, size.y, BLACK);
}

static void draw_texture(scaffold_node* text, mason_sprite_data* data) {
	DrawTexture(data->shape.texture, text->global_pos.x, text->global_pos.y, WHITE);
}

static void draw_label(scaffold_node* label, mason_sprite_data* data) {
	DrawText(data->shape.text, label->global_pos.x, label->global_pos.y, data->shape.font_size, BLACK);
}

static void process(scaffold_node* drawer, double delta) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);

	// Drawing sprites to target texture
	BeginTextureMode(data->target);
	ClearBackground(WHITE);

	scaffold_list* elem = data->sprites;
	while (elem != NULL) {
		scaffold_node* node = (scaffold_node*)(elem->data);
		mason_sprite_data* spr_data = (mason_sprite_data*)(node->data);

		if (spr_data->shape.type == MASON_SPR_RECTANGLE) {
			draw_rectangle(node, spr_data);
		} else if (spr_data->shape.type == MASON_SPR_TEXTURE) {
			draw_texture(node, spr_data);
		} else if (spr_data->shape.type == MASON_SPR_LABEL) {
			draw_label(node, spr_data);
		}

		elem = elem->next;
	}

	EndTextureMode();

	// Drawing target texture to the screen
	BeginDrawing();
	ClearBackground(BLACK);

	update_game_dimensions(data);
	scaffold_vector2 game_size = data->game_size;
	scaffold_vector2 dst_size = data->dst_size;
	scaffold_vector2 dst_pos = data->dst_pos;

	DrawTexturePro(data->target.texture,
			(Rectangle){0.0f, game_size.y, game_size.x, -game_size.y},
			(Rectangle){dst_pos.x, dst_pos.y, dst_size.x, dst_size.y},
			(Vector2){0.0f, 0.0f}, 0, WHITE);

	EndDrawing();
}

static void destroy(scaffold_node* drawer) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);

	UnloadRenderTexture(data->target);
	CloseWindow();

	scaffold_list_destroy(data->sprites);

	if (drawer->data) free(drawer->data);

	scaffold_node_destroy(drawer);
}

scaffold_node* mason_drawer_create(int win_w, int win_h, const char* title, int fps) {
	SetTraceLogLevel(LOG_WARNING); /* getting rid of annoying init info */
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(win_w, win_h, title);
	SetTargetFPS(fps);

	mason_drawer_data* data = malloc(sizeof(mason_drawer_data));
	data->sprites = NULL;
	data->target = LoadRenderTexture(win_w, win_h);
	
	return scaffold_node_create(
		&mason_drawer_type,
		data,
		process,
		destroy
	);
}

