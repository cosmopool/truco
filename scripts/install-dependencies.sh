#!/bin/sh

PROJECT_DIR="$(realpath "$( cd "$( dirname "$0" )" && pwd )"/..)"
OS=$(uname -s)
INCLUDE_DIR="$PROJECT_DIR/include"
LIB_DIR="$PROJECT_DIR/lib"
DEPS_CACHE_DIR="$PROJECT_DIR/.deps_cache"

setup_raylib() {
  printf "\n==---- Installing raylib\n"
  
  if [ "$OS" = "Linux" ]; then
    URL=https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz
  elif [ "$OS" = "Darwin" ]; then
    URL=https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_macos.tar.gz
  else
    echo "==>> OS ($OS) not suported yet"
    exit 1
  fi

  if [ ! -d "$DEPS_CACHE_DIR"/raylib ]; then
    echo "-- Fetching from: $URL"
    git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git "$DEPS_CACHE_DIR"/raylib
  else
    echo "-- Skipping download, cache found!"
  fi

  echo "-- Removing old raylib include and library files"
  rm -rf "$INCLUDE_DIR"/raylib
  rm "$LIB_DIR"/*raylib*

  echo "-- Building raylib"
  cd "$DEPS_CACHE_DIR"/raylib/src || exit
  make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED -j3

  echo "-- Copying dynamic libraries files to 'lib/'"
  if [ "$OS" = "Linux" ]; then
    cp libraylib.so.5.5.0 "$LIB_DIR"
    ln -s "$LIB_DIR"/libraylib.so.5.5.0 "$LIB_DIR"/libraylib.so
    ln -s "$LIB_DIR"/libraylib.so.5.5.0 "$LIB_DIR"/libraylib.so.550
  elif [ "$OS" = "Darwin" ]; then
    cp libraylib.5.5.0.dylib "$LIB_DIR"
    ln -s "$LIB_DIR"/libraylib.5.5.0.dylib "$LIB_DIR"/libraylib.dylib
    ln -s "$LIB_DIR"/libraylib.5.5.0.dylib "$LIB_DIR"/libraylib.550.dylib
  fi

  echo "-- Copying header files to 'include/'"
  mkdir -p "$INCLUDE_DIR"/raylib
  cp raylib.h  "$INCLUDE_DIR"/raylib/
  cp raymath.h "$INCLUDE_DIR"/raylib/
  cp rlgl.h    "$INCLUDE_DIR"/raylib/

  echo "==---- Success"
}

setup_arena() {
  printf "\n==---- Installing tsoding/arena\n"
  DEPENDENCY_DIR="$DEPS_CACHE_DIR/arena"

  if [ ! -d "$DEPENDENCY_DIR" ]; then
    echo "-- Fetching from: $URL"
    git clone --depth 1 https://github.com/tsoding/arena.git "$DEPENDENCY_DIR"
  else
    echo "-- Skipping download, cache found!"
  fi

  echo "-- Copying header files to 'include/'"
  mkdir -p "$INCLUDE_DIR"/arena
  cp "$DEPENDENCY_DIR"/arena.h "$INCLUDE_DIR"/arena/arena.h

  echo "==---- Success"
}

# -------------------------------------------------------------------
# MAIN
# -------------------------------------------------------------------

mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$DEPS_CACHE_DIR"

setup_raylib
setup_arena
