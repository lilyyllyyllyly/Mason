#pragma once

#include "scaffold.h"
#include "mason_collision_handler.h"

void collision_handler_delete_collider(scaffold_node* handler, scaffold_list* elem);
scaffold_list* collision_handler_add_collider(scaffold_node* handler, scaffold_node* col);

