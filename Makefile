
TARGET   := $(notdir $(CURDIR))
BUILD    := build
SOURCES  := src
INCLUDES := raylib
LIBS     := raylib m

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
# include all libraries
CFLAGS += -L$(CURDIR)/lib
# include all dependencies folder
CFLAGS += $(foreach dir,$(INCLUDES),-I$(CURDIR)/include/$(dir))
CFLAGS += $(foreach library,$(LIBS),-l$(library))

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

dependencies:
	chmod +x ./scripts/install-dependencies.sh
	./scripts/install-dependencies.sh

debug:
	$(CC) src/main.c -o $(OUTPUT) $(CFLAGS) 
	chmod +x $(OUTPUT)
