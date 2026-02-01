#ifndef CARDS_
#define CARDS_

#include "raylib.h"
#include <assert.h>
#include <stdio.h>

#include "base_types.h"
#include "game_state.h"

Rectangle Card_cardToRectangle(Card card) {
  Rectangle r = {.x = card.x, .y = card.y, .height = 100, .width = 50};
  return r;
}

void Card_drawCardAtIndex(u32 idx, GameState state) {
  Card card = state.cards[idx];
  u32 r = 80 - (int)(20 * idx);
  u32 g = 120 - (int)(20 * idx);
  u32 b = 180 - (int)(20 * idx);
  Rectangle rec = Card_cardToRectangle(card);
  DrawRectangle(rec.x, rec.y, rec.width, rec.height,
                CLITERAL(Color){r, g, b, 255});

  // card number
  char buff[16];
  sprintf(buff, "%d", idx);
  DrawText(buff, card.x, card.y, 20, WHITE);
}

/// Move card at `idx` to position 0, shifting all other elements to the right
///
/// `idx`: index of the card to move to the top of the `card_order` stack
void Card_MoveCardToTheTop(u8 idx, GameState *state) {
  assert(idx < CARD_COUNT);
  assert(idx * sizeof(u8) <= sizeof(state->cards_order));

  u8 card_to_move_to_the_top = state->cards_order[idx];
  for (u8 i = idx; i > 0; i--) {
    state->cards_order[i] = state->cards_order[i - 1];
  }
  state->cards_order[0] = card_to_move_to_the_top;
}

#endif // CARDS_
