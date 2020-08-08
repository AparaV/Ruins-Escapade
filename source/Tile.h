/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Tile.h
 **Contains Tile Class- Hold Information About Each Tile in Game Map
 */

#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

//Tile Definition
class Tile{

public:

    const int TILE_WIDTH = 96;//Dimensions
    const int TILE_HEIGHT = 96;
    SDL_Rect box;//Each Box

    Tile(){};//Default Constructor
    Tile(int x,int y, int type);//Constructor
    ~Tile();//Destructor

    int getType();//Get Type
    SDL_Rect getBox();//Get Box
    void setType(int t);//Set Type

protected:

private:

    int tileType;

};
//End Tile Definition

#endif // TILE_H

/**End of Tile.h*/
