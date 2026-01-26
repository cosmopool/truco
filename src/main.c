#include "game.h"
#include "hot_reload.c"
#include "logger.c"

#define ARENA_IMPLEMENTATION
#include "arena.h"
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

static Arena state_arena = {0};
static Arena default_arena = {0};

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  // pre-allocate 5mb
  arena_alloc(&default_arena, 5 * 1024 * 1024);
  arena_reset(&default_arena);

  InitWindow(screenWidth, screenHeight, "truco game");
  SetTargetFPS(60);

  GameState *state = arena_alloc(&state_arena, 1 * 1024 * 1024);
  arena_reset(&state_arena);
  GameHotReloadModule_t game = {0};
  HotReload_LoadGameModule(&game);
  game.init(&default_arena, state);
  //--------------------------------------------------------------------------------------

  while (!WindowShouldClose()) {
    // Update
    //------------------------------------------------------------------------------------
    if (IsKeyPressed(KEY_R)) {
      HotReload_RebuildLibrary();
      HotReload_LoadGameModule(&game);
    }

    game.update(&default_arena, state);
    //------------------------------------------------------------------------------------

    // Draw
    //------------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    game.draw(*state);

    EndDrawing();
    //------------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  arena_free(&default_arena);
  HotReload_CloseLibrary(game.module);
  CloseWindow();
  //--------------------------------------------------------------------------------------

  return 0;
}
