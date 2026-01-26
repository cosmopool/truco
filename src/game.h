#ifndef GAME_MAIN_
#define GAME_MAIN_

typedef struct {
  const char *msg;
  char *fps;
} GameState;

typedef void (*module_main_function)(GameState *state);

void Game_main(GameState *state);

#endif // GAME_MAIN_
