#!/bin/sh

OS=$(uname -s)
INCLUDE_DIR=include
LIB_DIR=lib

setup_raylib() {
  echo "-- Installing raylib dependency"

  if [ "$OS" = "Linux" ]; then
    URL=https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz
  elif [ "$OS" = "Darwin" ]; then
    URL=https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_macos.tar.gz
  else
    exit "==>> OS ($OS) not suported yet"
  fi

  if [ -d "$INCLUDE_DIR"/raylib ] && [ -f "$LIB_DIR"/*raylib*.a ]; then 
    echo "-- Already installed, skipping..."
    return
  fi

  echo "-- Removing old raylib include and library files"
  rm -rf "$INCLUDE_DIR"/raylib
  rm "$LIB_DIR"/*raylib*.a

  echo "-- Fetching from: $URL"
  # git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git includes/raylib
  # cd includes/raylib/src
  # make PLATFORM=PLATFORM_DESKTOP
  # mv libraylib.a ../../../libs/
  if [ ! -f "$INCLUDE_DIR"/raylib.tar.gz ]; then
    curl -L "$URL" --output "$INCLUDE_DIR"/raylib.tar.gz
  fi

  echo "-- Extracting files"
  tar -xf "$INCLUDE_DIR"/raylib.tar.gz || exit
  mv raylib-5.5*/"$INCLUDE_DIR" "$INCLUDE_DIR"/raylib
  mv raylib-5.5*/"$LIB_DIR"/*.a "$LIB_DIR"/

  echo "-- Cleanup temp files and directories"
  rm "$INCLUDE_DIR"/raylib.tar.gz
  rm -rf raylib-5.5_linux_amd64
}

# -------------------------------------------------------------------
# MAIN
# -------------------------------------------------------------------

mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"

setup_raylib
