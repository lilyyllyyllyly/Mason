#pragma once

#include <raylib.h>

#include "scaffold.h"

extern int mason_drawer_type;

int mason_drawer_window_should_close();

int mason_drawer_get_text_width(const char* text, int font_size);

scaffold_vector2 mason_drawer_get_image_size(const char* filename);

double mason_drawer_get_frame_time();

scaffold_vector2 mason_drawer_get_game_size(scaffold_node* drawer);
void mason_drawer_set_game_size(scaffold_node* drawer, int width, int height);
void mason_drawer_set_game_size_vec(scaffold_node* drawer, scaffold_vector2 size);

scaffold_vector2 mason_drawer_get_window_size();
void mason_drawer_set_window_size(int width, int height);
void mason_drawer_set_window_size_vec(scaffold_vector2 size);

scaffold_vector2 mason_drawer_screen_to_game_pos(scaffold_node* drawer, scaffold_vector2 pos);

typedef struct {
	scaffold_list* sprites;
	RenderTexture2D target;

	scaffold_vector2 scr_size;
	scaffold_vector2 dst_size;
	scaffold_vector2 dst_pos;
	scaffold_vector2 game_size;
} mason_drawer_data;

scaffold_node* mason_drawer_create(int win_w, int win_h, const char* title, int fps);

