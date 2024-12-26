#pragma once

#include "scaffold.h"
#include "render/mason_drawer.h"
#include "render/mason_sprite.h"

scaffold_list* drawer_add_sprite(mason_drawer_data* drawer, mason_sprite_data* sprite);
void drawer_delete_sprite(mason_drawer_data* drawer, scaffold_list* elem);

