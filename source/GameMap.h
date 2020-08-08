/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameMap.h
 **Contains GameMap Class - Holds Information about Map of Each Level
 */

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include "Tile.h"
#include <fstream>

using std::string;
using std::ifstream;

//GameMap Definition
class GameMap{

public:

    const int TILE_WIDTH = 96;//Tile Dimensions
    const int TILE_HEIGHT = 96;
    const int TILE_EMPTY = 0;//Tile Types
    const int TILE_FLOOR = 1;
    const int TILE_RIGHT_WALL = 2;
    const int TILE_LEFT_WALL = 3;
    const int TILE_DOOR = 4;
    const int TILE_HOLE = 5;
    const int TOTAL_TILE_SPRITES = 6;//Total Tile Types
    int TOTAL_TILES;//Total Tiles
    Tile** tiles;//Array to Store Map Information

    GameMap(int tiles, string srcPath, string imagePath, SDL_Renderer* renderer);//Constructor
    ~GameMap();//Destructor

    void setLevelDimensions(int tilesX, int tilesY);//Set Level Dimensions
    void setMapSrc(string src);//Set Map Source

    void loadTiles();//Load Tiles From File
    bool checkCollision(SDL_Rect a, SDL_Rect b);//Check Collision
    void renderMap(SDL_Rect &camera);//Render Map

protected:

private:

    string mapSource;//Map File Path
    Texture tileTexture;//Texture for Rendering
    SDL_Rect* tileClips;//Information for Clipping Sprites
    int LEVEL_WIDTH;//Level Dimensions
    int LEVEL_HEIGHT;

};
//End GameMap Definition

#endif // GAMEMAP_H

/**End of GameMap.h*/
