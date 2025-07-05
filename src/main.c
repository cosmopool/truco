#include "hot_reload.c"
#include "logger.c"
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(screenWidth, screenHeight, "truco game");
  SetTargetFPS(60);

  GameState state = {0};
  GameHotReloadModule_t game = {0};
  HotReload_LoadGameModule(&game);
  game.init(&state);
  //--------------------------------------------------------------------------------------

  while (!WindowShouldClose()) {
    // Update
    //------------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_R)) {
      HotReload_RebuildLibrary();
      HotReload_LoadGameModule(&game);
    }

    game.update(&state);
    //------------------------------------------------------------------------------------

    // Draw
    //------------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    game.draw(&state);

    EndDrawing();
    //------------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  HotReload_CloseLibrary(game.module);
  CloseWindow();
  //--------------------------------------------------------------------------------------

  return 0;
}
