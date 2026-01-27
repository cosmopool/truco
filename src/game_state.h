#ifndef GAME_STATE_
#define GAME_STATE_

#include "base_types.h"

typedef struct {
  f32 x, y;
} Card;

typedef struct {
  const char *msg;
  char *fps;
  Card cards[3];
  i32 card_grabbed;
} GameState;

#endif // GAME_STATE_
