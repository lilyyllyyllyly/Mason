#include <stdlib.h>

#include <raylib.h>

#include "scaffold.h"

#include "mason_rectangle.h"
#include "mason_sprite.h"

int mason_drawer_type = NODE_TYPE_UNASSIGNED;

#include "mason_drawer.h"

double mason_drawer_frame_time() {
	return GetFrameTime();
}

scaffold_vector2 mason_drawer_game_size(scaffold_node* drawer) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);
	return (scaffold_vector2){data->target.texture.width, data->target.texture.height};
}

scaffold_vector2 mason_drawer_screen_size() {
	return (scaffold_vector2){(float)GetScreenWidth(), (float)GetScreenHeight()};
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

static void destroy(scaffold_node* drawer) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);

	UnloadRenderTexture(data->target);
	CloseWindow();

	scaffold_list_destroy(data->sprites);

	if (drawer->data) free(drawer->data);

	scaffold_node_destroy(drawer);
}

typedef struct rectangle_data {
	scaffold_vector2 size;
	mason_drawer_data* drawer;
	scaffold_list* elem;
} rectangle_data;

typedef struct sprite_data {
	Texture2D tex;
	mason_drawer_data* drawer;
	scaffold_list* elem;
} sprite_data;

static void rectangle_destroy(scaffold_node* rectangle) {
	rectangle_data* rect_data = (rectangle_data*)(rectangle->data);

	rect_data->drawer->sprites = (void*)scaffold_list_delete_element(rect_data->drawer->sprites, rect_data->elem);

	free(rectangle->data);
	scaffold_node_destroy(rectangle);
}

static void sprite_destroy(scaffold_node* sprite) {
	sprite_data* spr_data = (sprite_data*)(sprite->data);

	spr_data->drawer->sprites = scaffold_list_delete_element(spr_data->drawer->sprites, spr_data->elem);

	UnloadTexture(spr_data->tex);

	free(sprite->data);
	scaffold_node_destroy(sprite);
}

void drawer_add_rectangle(scaffold_node* drawer, scaffold_node* rect, scaffold_vector2 size) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);
	data->sprites = scaffold_list_insert(data->sprites, (void*)rect);

	rectangle_data* rect_data = malloc(sizeof(rectangle_data));
	rect_data->size = size;
	rect_data->drawer = data;
	rect_data->elem = data->sprites;

	rect->data = rect_data;
	rect->destroy = rectangle_destroy;
}

void drawer_add_sprite(scaffold_node* drawer, scaffold_node* sprite, const char* filename) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);
	data->sprites = scaffold_list_insert(data->sprites, (void*)sprite);

	sprite_data* spr_data = malloc(sizeof(sprite_data));
	spr_data->tex = LoadTexture(filename);
	spr_data->drawer = data;
	spr_data->elem = data->sprites;

	sprite->data = spr_data;
	sprite->destroy = sprite_destroy;
}

static void draw_rectangle(scaffold_node* rect) {
	scaffold_vector2 size = ((rectangle_data*)(rect->data))->size;
	DrawRectangle(rect->global_pos.x, rect->global_pos.y, size.x, size.y, BLACK);
}

static void draw_sprite(scaffold_node* sprite) {
	Texture2D tex = ((sprite_data*)(sprite->data))->tex;
	DrawTexture(tex, sprite->global_pos.x, sprite->global_pos.y, WHITE);
}

static void process(scaffold_node* drawer, double delta) {
	mason_drawer_data* data = (mason_drawer_data*)(drawer->data);

	// Drawing sprites to target texture
	BeginTextureMode(data->target);
	ClearBackground(WHITE);

	scaffold_list* elem = data->sprites;
	while (elem != NULL) {
		scaffold_node* node = (scaffold_node*)(elem->data);

		if (node->type == mason_rectangle_type) {
			draw_rectangle(node);
		} else if (node->type == mason_sprite_type) {
			draw_sprite(node);
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

