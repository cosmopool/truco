#!/bin/sh

PROJECT_DIR="$(realpath "$( cd "$( dirname "$0" )" && pwd )"/..)"
OS=$(uname -s)
INCLUDE_DIR="$PROJECT_DIR/include"
LIB_DIR="$PROJECT_DIR/lib"
DEPS_CACHE_DIR="$PROJECT_DIR/.deps_cache"

setup_raylib() {
  echo "-- Installing raylib dependency"
  
  if [ "$OS" = "Linux" ]; then
    URL=https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz
  elif [ "$OS" = "Darwin" ]; then
    URL=https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_macos.tar.gz
  else
    echo "==>> OS ($OS) not suported yet"
    exit 1
  fi

  if [ -d "$INCLUDE_DIR"/raylib ] && [ -f "$LIB_DIR"/*raylib*.a ]; then 
    echo "-- Already installed, skipping..."
    return
  fi

  echo "-- Removing old raylib include and library files"
  rm -rf "$INCLUDE_DIR"/raylib
  rm "$LIB_DIR"/*raylib*

  if [ ! -d "$DEPS_CACHE_DIR"/raylib ]; then
    echo "-- Fetching from: $URL"
    git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git "$DEPS_CACHE_DIR"/raylib
  fi

  echo "-- Building raylib"
  cd "$DEPS_CACHE_DIR"/raylib/src || exit
  make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED -j3

  # setup dynamic libraries
  if [ "$OS" = "Linux" ]; then
    cp libraylib.so.5.5.0 "$LIB_DIR"
    ln -s "$LIB_DIR"/libraylib.so.5.5.0 "$LIB_DIR"/libraylib.so
    ln -s "$LIB_DIR"/libraylib.so.5.5.0 "$LIB_DIR"/libraylib.so.550
  elif [ "$OS" = "Darwin" ]; then
    cp libraylib.5.5.0.dylib "$LIB_DIR"
    ln -s "$LIB_DIR"/libraylib.5.5.0.dylib "$LIB_DIR"/libraylib.so.dylib
    ln -s "$LIB_DIR"/libraylib.5.5.0.dylib "$LIB_DIR"/libraylib.so.550.dylib
  fi

  # setup header files
  mkdir -p "$INCLUDE_DIR"/raylib
  cp raylib.h  "$INCLUDE_DIR"/raylib/
  cp raymath.h "$INCLUDE_DIR"/raylib/
  cp rlgl.h    "$INCLUDE_DIR"/raylib/
}

# -------------------------------------------------------------------
# MAIN
# -------------------------------------------------------------------

mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$DEPS_CACHE_DIR"

setup_raylib
