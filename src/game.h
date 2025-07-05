#ifndef GAME_MAIN_
#define GAME_MAIN_

typedef struct {
  const char *msg;
  char *fps;
} GameState;

typedef void (*module_init_function)(GameState *state);
typedef void (*module_update_function)(GameState *state);
typedef void (*module_draw_function)(GameState *state);

void Game_init(GameState *state);
void Game_update(GameState *state);
void Game_draw(GameState *state);

#endif // GAME_MAIN_
