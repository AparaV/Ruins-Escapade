IDIR = ./include
CC = g++
CFLAGS = -std=c++11 -I$(IDIR)

ODIR = obj
SDIR = ./src

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

_DEPS = GameLevel.h GameObject.h IntroductionScreen.h Menu.h Tile.h GameMap.h Hero.h Key.h Texture.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_SRCS = GameLevel.cpp GameObject.cpp IntroductionScreen.cpp Menu.cpp Tile.cpp GameMap.cpp Hero.cpp Key.cpp Texture.cpp
SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))

ruinsescapade: $(SRCS)
	$(CC) -o $@ main.cpp $^ $(LIBS) $(CFLAGS)

clean:
	rm ruinsescapade
