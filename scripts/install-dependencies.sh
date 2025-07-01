#!/bin/sh

mkdir -p includes
mkdir -p libs

if [ ! -d includes/raylib ]; then
  # git clone --depth 1 --branch 5.5 https://github.com/raysan5/raylib.git includes/raylib
  if [ ! -f includes/raylib.tar.gz ]; then
    curl -L https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz --output includes/raylib.tar.gz
  fi
  tar -xf includes/raylib.tar.gz || exit
  mv raylib-5.5_linux_amd64/include includes/raylib
  mv raylib-5.5_linux_amd64/lib/*.a libs/
  # cleanup
  rm includes/raylib.tar.gz
  rm -rf raylib-5.5_linux_amd64
fi

# cd includes/raylib/src
# make PLATFORM=PLATFORM_DESKTOP
# mv libraylib.a ../../../libs/
