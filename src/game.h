#ifndef GAME_MAIN_
#define GAME_MAIN_

#include "arena.h"

typedef struct {
  const char *msg;
  char *fps;
} GameState;

typedef void (*module_main_function)(Arena *arena, GameState *state);
typedef void (*module_init_function)(Arena *arena, GameState *state);
typedef void (*module_update_function)(Arena *arena, GameState *state);
typedef void (*module_draw_function)(GameState);

void Game_main(Arena *arena, GameState *state);
void Game_init(Arena *arena, GameState *state);
void Game_update(Arena *arena, GameState *state);
void Game_draw(GameState state);

#endif // GAME_MAIN_
