#pragma once

#include "scaffold.h"

void collision_handler_delete_collider(scaffold_node* handler, scaffold_list* elem);
scaffold_list* collision_handler_add_collider(scaffold_node* handler, scaffold_node* col);

scaffold_node* create_collision_handler();

