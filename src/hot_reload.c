#include "game.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

/// Game main function used for hot reloading

typedef struct {
  void *module;
  module_main_function main;
  module_init_function init;
  module_update_function update;
  module_draw_function draw;
} GameHotReloadModule_t;

/// Rebuild the dynamic library containing the game state
int HotReload_RebuildLibrary() {
  printf("-->> Rebuilding source code\n");
  system("make clean");
  return system("make truco.so");
}

/// Load the dynamic library containing the game state
void *HotReload_LoadLibrary(char *libray_name) {
  printf("-->> Loading game module: %s\n", libray_name);
  return dlopen(libray_name, RTLD_NOW);
}

void *HotReload_LoadSymbol(void *loaded_library, char *symbol_name) {
  printf("-->> Searching for symbol in module: %s\n", symbol_name);
  return dlsym(loaded_library, symbol_name);
}

/// Close the dynamic library containing the game state
int HotReload_CloseLibrary(void *loaded_library) {
  printf("-->> Unloading game module\n");
  return dlclose(loaded_library);
}

void HotReload_LoadGameModule(GameHotReloadModule_t *game_module) {
  printf("-->> Loading game module\n");
  if (game_module->module) {
    HotReload_CloseLibrary(game_module->module);
  }

  game_module->module = HotReload_LoadLibrary("./truco.so");
  if (!game_module->module) {
    fprintf(stderr, "ERROR: could not load truco.so library: %s", dlerror());
    exit(1);
  }

  game_module->main = HotReload_LoadSymbol(game_module->module, "Game_main");
  if (!game_module->main) {
    fprintf(stderr, "ERROR: could not find symbol 'Game_main': %s", dlerror());
    exit(1);
  }

  game_module->init = HotReload_LoadSymbol(game_module->module, "Game_init");
  if (!game_module->init) {
    fprintf(stderr, "ERROR: could not find symbol 'Game_init': %s", dlerror());
    exit(1);
  }

  game_module->update = HotReload_LoadSymbol(game_module->module, "Game_update");
  if (!game_module->update) {
    fprintf(stderr, "ERROR: could not find symbol 'Game_update': %s", dlerror());
    exit(1);
  }

  game_module->draw = HotReload_LoadSymbol(game_module->module, "Game_draw");
  if (!game_module->draw) {
    fprintf(stderr, "ERROR: could not find symbol 'Game_draw': %s", dlerror());
    exit(1);
  }
}
