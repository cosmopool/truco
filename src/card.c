#ifndef CARDS_
#define CARDS_

#include <stdio.h>
#include "raylib.h"

#include "base_types.h"
#include "game_state.h"

void Card_drawCardAtIndex(u32 idx, GameState state) {
  Card card = state.cards[idx];
  u32 r = 80 - (int)(20 * idx);
  u32 g = 120 - (int)(20 * idx);
  u32 b = 180 - (int)(20 * idx);
  DrawRectangle(card.x, card.y, 50, 100, CLITERAL(Color){r, g, b, 255});

  // card number
  char buff[16];
  sprintf(buff, "%d", idx);
  DrawText(buff, card.x, card.y, 20, WHITE);
}

#endif // CARDS_
