#pragma once

#include <raylib.h>

#include "scaffold.h"

extern int mason_drawer_type;

double mason_drawer_frame_time();

scaffold_vector2 mason_drawer_game_size(scaffold_node* drawer);
scaffold_vector2 mason_drawer_screen_size();

scaffold_vector2 mason_drawer_screen_to_game_pos(scaffold_node* drawer, scaffold_vector2 pos);

typedef struct {
	scaffold_list* sprites;
	RenderTexture2D target;
} mason_drawer_data;

scaffold_node* mason_drawer_create(int win_w, int win_h, const char* title, int fps);

