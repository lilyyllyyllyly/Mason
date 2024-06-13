#pragma once

#include <raylib.h>

#include "scaffold.h"

extern int drawer_type;

double drawer_get_frame_time();

scaffold_vector2 drawer_get_game_size(scaffold_node* drawer);
scaffold_vector2 drawer_get_screen_size();

scaffold_vector2 drawer_screen_to_game_pos(scaffold_node* drawer, scaffold_vector2 pos);

typedef struct {
	scaffold_list* sprites;
	RenderTexture2D target;
} drawer_data;

scaffold_node* create_drawer(int win_w, int win_h, const char* title, int fps);

void drawer_add_rectangle(scaffold_node* drawer, scaffold_node* rect, scaffold_vector2 size);
void drawer_add_sprite(scaffold_node* drawer, scaffold_node* sprite, const char* filename);

