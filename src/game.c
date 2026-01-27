#include "card.c"
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
  GameState *new_state = arena_alloc(arena, 1 * 1024 * 1024);
  new_state->msg = "first msg";
  new_state->fps = arena_alloc(arena, sizeof(char) * 10);
  new_state->card_grabbed = -1;
  for (u32 i = 0; i < 3; i++) {
    const u32 card_width = 50;
    // const u32 card_height = 100;
    const u32 offset = 200;
    const u32 space = 10;
    // const int screen_width = 800;

    Card card;
    card.x = offset + (i * (card_width + space));
    card.y = 100;

    new_state->cards[i] = card;
  }
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
  Vector2 mouse_pos = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Rectangle card;
    for (u32 i = 0; i < 3; i++) {
      card.height = 100;
      card.width = 50;
      card.x = state->cards[i].x;
      card.y = state->cards[i].y;
      if (CheckCollisionPointRec(mouse_pos, card)) {
        char buf[32];
        sprintf(buf, "-- Grabbed card: %d", i);
        _logDebug(buf);
        state->card_grabbed = i;
        break;
      }
    }
  }

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    state->card_grabbed = -1;
  }

  if (state->card_grabbed >= 0) {
    Vector2 mouse_delta = GetMouseDelta();
    state->cards[state->card_grabbed].x += mouse_delta.x;
    state->cards[state->card_grabbed].y += mouse_delta.y;
  }
}

void Game_draw(Arena *arena, void *game_state) {
  ClearBackground(RAYWHITE);
  (void)arena;
  GameState *state = game_state;
  DrawText(state->fps, 0, 0, 20, BLACK);
  DrawText(state->msg, 0, 50, 20, BLACK);

  for (u32 i = 0; i < 3; i++) {
    if ((i32)i == state->card_grabbed) {
      continue;
    }
    Card_drawCardAtIndex(i, *state);
  }

  if (state->card_grabbed >= 0) {
    Card_drawCardAtIndex(state->card_grabbed, *state);
  }
}
