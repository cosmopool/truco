#include "game.h"
#include "game_state.h"
#include "logger.c"

#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "raylib.h"

#include <assert.h>

void Game_init(Arena *arena, void **game_state) {
  const char *header = "INIT";
  _log(header, "Initializing game module");
  assert(arena);

  if (*game_state == NULL) {
    _logDebug("First initialization");
  } else {
    arena_reset(arena);
  }
  // allocate and initialize GameState structure current size
  GameState *new_state = arena_alloc(arena, 4096);
  new_state->msg = "first msg";
  new_state->fps = arena_alloc(arena, sizeof(char) * 10);
  *game_state = new_state;

  // print GameState current size for debug porpouse
  char size_msg[256];
  sprintf(size_msg, "GameState structure size: %lu", sizeof(GameState));
  _logDebug(size_msg);

  _log(header, "Finished initialization");
}

void Game_update(Arena *arena, void *game_state) {
  assert(arena);
  GameState *state = game_state;
  sprintf(state->fps, "%d", GetFPS());
}

void Game_draw(Arena *arena, void *game_state) {
  ClearBackground(RAYWHITE);
  (void)arena;
  GameState *state = game_state;
  DrawText(state->fps, 0, 0, 20, BLACK);
  DrawText(state->msg, 0, 50, 20, BLACK);
}
