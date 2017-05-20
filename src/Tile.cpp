/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Tile.cpp
 **Contains Tile Class Implementation
 */

#include "../include/Tile.h"

//Constructor
Tile::Tile(int x, int y, int type){
    box.x = x;
    box.y = y;
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    tileType = type;
}

//Destructor
Tile::~Tile(){}

//Get Type
int Tile::getType(){
    return tileType;
}

//Get Box
SDL_Rect Tile::getBox(){
    return box;
}

//Set Type
void Tile::setType(int t){
    tileType = t;
}

/**End of Tile.cpp*/
