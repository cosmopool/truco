#ifndef CARDS_
#define CARDS_

#include "raylib.h"
#include <assert.h>
#include <stdio.h>

#include "base_types.h"
#include "game_state.h"

Rectangle Card_ToRectangle(Card card) {
  Rectangle r = {.x = card.x, .y = card.y, .height = 100, .width = 50};
  return r;
}

void Card_DrawOutline(Rectangle r, Color color) {
  DrawLine(r.x, r.y, r.x + r.width, r.y, color);
  DrawLine(r.x, r.y + r.height, r.x + r.width, r.y + r.height, color);
  DrawLine(r.x, r.y + r.height, r.x, r.y, color);
  DrawLine(r.x + r.width, r.y, r.x + r.width, r.y + r.height, color);
}

/// Move card at `idx` to position 0, shifting all other elements to the right
///
/// `idx`: index of the card to move to the top of the `card_order` stack
void Card_MoveToTheTop(u8 idx, GameState *state) {
  assert(idx < CARD_COUNT);
  assert(idx * sizeof(u8) <= sizeof(state->cards_order));

  u8 card_to_move_to_the_top = state->cards_order[idx];
  for (u8 i = idx; i > 0; i--) {
    state->cards_order[i] = state->cards_order[i - 1];
  }
  state->cards_order[0] = card_to_move_to_the_top;
}

#endif // CARDS_
