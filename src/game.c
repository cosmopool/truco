#include "game.h"
#include "logger.c"

#include "raylib.h"

#include <stdlib.h>

void Game_init(GameState *state) {
  _logInfo("Initializing game module");

  state->msg = "first msg";
  state->fps = malloc(sizeof(char) * 10);

  _logInfo("Ending game module");
}

void Game_update(GameState *state) {
  // Update
  sprintf(state->fps, "%d", GetFPS());
  state->msg = "second msg";
}

void Game_draw(GameState *state) {
  // Draw
  DrawText(state->fps, 0, 0, 20, BLACK);
  DrawText(state->msg, 0, 50, 20, BLACK);
}
