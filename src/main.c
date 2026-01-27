#include "game.h"
#include "hot_reload.c"
#include "logger.c"

#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

static Arena state_arena = {0};

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(screenWidth, screenHeight, "truco game");
  SetTargetFPS(60);

  GameHotReloadModule_t game = {0};
  HotReload_LoadGameModule(&game);

  void *game_state = NULL;
  game.init(&state_arena, &game_state);
  //--------------------------------------------------------------------------------------

  while (!WindowShouldClose()) {
    // Update
    //------------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_R)) {
      HotReload_RebuildLibrary();
      HotReload_LoadGameModule(&game);

      if (IsKeyDown(KEY_LEFT_SHIFT)) {
        _log("Main", "HOT RESTART");
        game.init(&state_arena, &game_state);
      } else {
        _log("Main", "HOT RELOAD");
      }
    }

    game.update(&state_arena, game_state);
    //------------------------------------------------------------------------------------

    // Draw
    //------------------------------------------------------------------------------------
    BeginDrawing();
    game.draw(&state_arena, game_state);
    EndDrawing();
    //------------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  arena_free(&state_arena);
  HotReload_CloseLibrary(game.module);
  CloseWindow();
  //--------------------------------------------------------------------------------------

  return 0;
}
