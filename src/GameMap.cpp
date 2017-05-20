/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameMap.cpp
 **Contains GameMap Implementation
 */

#include "../include/GameMap.h"

//Constructor
GameMap::GameMap(int numberTiles, string srcPath, string imagePath, SDL_Renderer* renderer){

    mapSource = srcPath;
    tileTexture.setRenderer(renderer);
    tileTexture.loadFromFile(imagePath);

    TOTAL_TILES = numberTiles;

    tiles = new Tile*[TOTAL_TILES];
    tileClips = new SDL_Rect[TOTAL_TILE_SPRITES];
}

//Destructor
GameMap::~GameMap(){
    delete []tiles;
    delete []tileClips;
}

//Set Level Dimensions
void GameMap::setLevelDimensions(int tilesX, int tilesY){
    LEVEL_WIDTH = tilesX * TILE_WIDTH;
    LEVEL_HEIGHT = tilesY * TILE_HEIGHT;
    TOTAL_TILES = tilesX * tilesY;
}

//Set Map Source
void GameMap::setMapSrc(string src){
    mapSource = src;
}

//Load Tile Set
void GameMap::loadTiles(){

    int x = 0;//initial offsets
    int y = 0;

    //Open File
    ifstream source;
    source.open(mapSource);

    if(source.fail()){
        std::cout << "No file" << std::endl;
        return;
    }
    else{
        //Start Initializing Tiles
        for(int i = 0; i < TOTAL_TILES; ++i){

            int type = -1;//tile type
            source >> type;

            if(source.fail()){
                std::cout << "Could not read file" << std::endl;
                return;
            }

            //Initialize Next Tile
            if(type >= 0 && type < TOTAL_TILE_SPRITES){
                tiles[i] = new Tile(x, y, type);
            }
            else{
                std::cout << "Invalid Tile" << std::endl;
                return;
            }

            x+= TILE_WIDTH;

            if(x >= LEVEL_WIDTH){
                x = 0;
                y += TILE_HEIGHT;
            }
        }

        //Initiate Clip Sizes
        for(int i = 0; i < TOTAL_TILE_SPRITES; ++i){
            tileClips[i].x = i * TILE_WIDTH;
            tileClips[i].y = 0;
            tileClips[i].w = TILE_WIDTH;
            tileClips[i].h = TILE_HEIGHT;
        }
    }

    source.close();
}


//Check Collision
bool GameMap::checkCollision( SDL_Rect a, SDL_Rect b ){

    //Sides of Rectangle A and B
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate Sides of Rectangle A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate Sides of Rectangle B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If A and B don't intersect
    if( bottomA <= topB ){
        return false;
    }

    if( topA >= bottomB ){
        return false;
    }

    if( rightA <= leftB ){
        return false;
    }

    if( leftA >= rightB ){
        return false;
    }

    return true;
}


//Render Map
void GameMap::renderMap(SDL_Rect &camera){

    for(int i = 0; i < TOTAL_TILES; ++i){

        //If Tile Collides with Camera
        if(checkCollision(camera, tiles[i]->getBox())){
            tileTexture.render(tiles[i]->box.x - camera.x, tiles[i]->box.y - camera.y, &tileClips[tiles[i]->getType()]);
        }
    }
}

/**End of GameMap.cpp*/
