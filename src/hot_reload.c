#include "game_state.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#define MODULE_NAME "truco.so"
#define MAIN_FUNCTION_NAME "module_main"

/// Game main function used for hot reloading
typedef GameState *module_main_func(GameState *game_state);

/// Rebuild the dynamic library containing the game state
int HotReload_RebuildLibrary() {
  printf("-->> Rebuilding source code\n");
  return system("make truco.so");
}

/// Load the dynamic library containing the game state
void *HotReload_LoadModule() {
  printf("-->> Loading game module\n");
  return dlopen(MODULE_NAME, RTLD_NOW);
}

void *HotReload_LoadLibrary(void *module) {
  printf("-->> Searching for game function in module\n");
  return dlsym(module, MAIN_FUNCTION_NAME);
}

/// Close the dynamic library containing the game state
int HotReload_CloseLibrary(void *module) {
  printf("-->> Unloading game module\n");
  return dlclose(module);
}
