TARGET   := $(notdir $(CURDIR))
BUILD    := build
SOURCES  := src
OS       := $(shell uname -s)

#---------------------------------------------------------------------------------
# exports
#---------------------------------------------------------------------------------

export OUTPUT := $(CURDIR)/$(TARGET)

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS := -g -Wall -O2 -ffunction-sections
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wunreachable-code
CFLAGS += -I$(CURDIR)/include/raylib

# link dynamic libraries for macos and linux
ifeq ($(OS), Darwin)
    LDFLAGS += -Wl,-rpath,@executable_path/lib -Wl,-rpath,@executable_path/
    LDFLAGS += -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
else
		LDFLAGS += -Wl,-rpath,'$(CURDIR)/lib'
endif
LDFLAGS += -L$(CURDIR)/lib
LDFLAGS += -lraylib -lm

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

dependencies:
	chmod +x ./scripts/install-dependencies.sh
	./scripts/install-dependencies.sh

debug: truco.so
	$(CC) src/main.c -o $(OUTPUT) $(CFLAGS) $(LDFLAGS)

truco.so: 
	$(CC) src/game.c -o truco.so -fPIC -shared $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf truco truco.so truco.dSYM
