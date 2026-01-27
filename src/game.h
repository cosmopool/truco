#ifndef GAME_MAIN_
#define GAME_MAIN_

#include "arena.h"

typedef void (*module_init_function)(Arena *arena, void **game_state);
typedef void (*module_update_function)(Arena *arena, void *game_state);
typedef void (*module_draw_function)(Arena *arena, void *game_state);

void Game_init(Arena *arena, void **game_state);
void Game_update(Arena *arena, void *game_state);
void Game_draw(Arena *arena, void *game_state);

#endif // GAME_MAIN_
