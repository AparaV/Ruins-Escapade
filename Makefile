IDIR = ./source
CC = g++
CFLAGS = -std=c++11 -I$(IDIR)

ODIR = obj
SDIR = ./source

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

_DEPS = GameLevel.h Object.h IntroductionScreen.h Menu.h Tile.h GameMap.h Player.h Key.h Texture.h DynamicObject.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_SRCS = GameLevel.cpp Object.cpp IntroductionScreen.cpp Menu.cpp Tile.cpp GameMap.cpp Player.cpp Key.cpp Texture.cpp DynamicObject.cpp
SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))

ruinsescapade: $(SRCS)
	$(CC) -o $@ main.cpp $^ $(LIBS) $(CFLAGS)

clean:
	rm ruinsescapade
