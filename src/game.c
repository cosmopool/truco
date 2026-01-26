#include "game.h"
#include "logger.c"

#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "raylib.h"

#include <assert.h>

void Game_main(Arena *arena, GameState *prev_state) {
  _logInfo("Reloading main");
  assert(arena);
  GameState *state = {0};
  if (!state) {
    state = arena_alloc(arena, 1024 * 1024);
  }
  state = prev_state;
}

void Game_init(Arena *arena, GameState *state) {
  _logInfo("Initializing game module");
  assert(arena);

  state->msg = "first msg";
  state->fps = arena_alloc(arena, sizeof(char) * 10);

  _logInfo("Ending game module");
}

void Game_update(Arena *arena, GameState *state) {
  assert(arena);
  sprintf(state->fps, "%d", GetFPS());
  state->msg = "second msg";
}

void Game_draw(GameState state) {
  DrawText(state.fps, 0, 0, 20, BLACK);
  DrawText(state.msg, 0, 50, 20, BLACK);
}
