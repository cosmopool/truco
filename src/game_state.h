#ifndef GAME_STATE_
#define GAME_STATE_

#include "base_types.h"

#define CARD_COUNT 52

typedef struct {
  f32 x, y;
  u32 strength;
} CardSnapPoint;

typedef struct {
  f32 x, y;
} Card;

typedef struct {
  const char *msg;
  char *fps;
  i32 card_grabbed;
  Card cards[CARD_COUNT];
  u8 cards_order[CARD_COUNT];
  CardSnapPoint snap_points[3];
} GameState;

#endif // GAME_STATE_
