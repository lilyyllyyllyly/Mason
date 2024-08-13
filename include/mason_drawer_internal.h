#pragma once

#include "scaffold.h"
#include "mason_drawer.h"

scaffold_list* drawer_add_sprite(mason_drawer_data* drawer, scaffold_node* sprite);
void drawer_delete_sprite(mason_drawer_data* drawer, scaffold_list* elem);

