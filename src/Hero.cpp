/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Hero.cpp
 **Contains Hero Class Implementation
 */

#include "../include/Hero.h"

//Constructor
Hero::Hero(string path, int x, int y, int constVelX, int constVelY, SDL_Renderer* renderer, GameMap* mapped):
    GameObject(path, x, y, constVelX, constVelY, renderer){
    initiateSpriteClips();//Initiate Sprite Clips
    FRAME = 0;
    currentClip = spriteClipRight[0];//Initiate Current Clip
    level = mapped;
    keysPicked = 0;
    startPosX = x;
    startPosY = y;
}

//Destructor
Hero::~Hero(){
    objectTexture.free();
    level = NULL;
}

//Initiate Sprite Clips
void Hero::initiateSpriteClips(){

    //Left Sprites
    for(int i = 0; i < 8; ++i){
        spriteClipLeft[i].x = i * spriteWidth;
        spriteClipLeft[i].y = 0;
        spriteClipLeft[i].w = spriteWidth;
        spriteClipLeft[i].h = spriteHeight;
    }

    //Right Sprites
    for(int i = 0; i < 8; ++i){
        spriteClipRight[i].x = i * spriteWidth;
        spriteClipRight[i].y = spriteHeight;
        spriteClipRight[i].w = spriteWidth;
        spriteClipRight[i].h = spriteHeight;
    }

    //Up Sprites
    for(int i = 0; i < 8; ++i){
        spriteClipUp[i].x = i * spriteWidth;
        spriteClipUp[i].y = 2 * spriteHeight;
        spriteClipUp[i].w = spriteWidth;
        spriteClipUp[i].h = spriteHeight;
    }

    //Down Sprites
    for(int i = 0; i < 8; ++i){
        spriteClipDown[i].x = i * spriteWidth;
        spriteClipDown[i].y = 3 * spriteHeight;
        spriteClipDown[i].w = spriteWidth;
        spriteClipDown[i].h = spriteHeight;
    }
}

//Set the Game Map
void Hero::setLevel(GameMap* lvl){
    level = lvl;
}

//Set Initial Sprite Position
void Hero::setSpritePos(int x, int y){
    spritePos.x = x;
    spritePos.y = y;
    startPosX = x;
    startPosY = y;
}

//Main Event Handler
void Hero::handleEvent(SDL_Event &e, Key &key1, Key &key2, Key &key3){

    //If Key is Pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){

        //Change Velocity
        switch(e.key.keysym.sym){

            //Move Up
            case SDLK_UP:
                velY -= constVelY;
                currentClip = spriteClipUp[0];
                break;

            //Move Down
            case SDLK_DOWN:
                velY += constVelY;
                currentClip = spriteClipDown[0];
                break;

            //Move Right
            case SDLK_RIGHT:
                velX += constVelX;
                currentClip = spriteClipRight[0];
                break;

            //Move Left
            case SDLK_LEFT:
                velX -= constVelX;
                currentClip = spriteClipLeft[0];
                break;

            //Pick Up Key
            case SDLK_SPACE:
                pickUpKey(key1);
                pickUpKey(key2);
                pickUpKey(key3);
                break;

            default:
                break;
        }
    }

    //If Key was Released
    else if(e.type == SDL_KEYUP && e.key.repeat == 0){

        //Change Velocity
        switch(e.key.keysym.sym){

            //Stop Moving Up
            case SDLK_UP:
                velY += constVelY;
                currentClip = spriteClipUp[0];
                break;

            //Stop Moving Down
            case SDLK_DOWN:
                velY -= constVelY;
                currentClip = spriteClipDown[0];
                break;

            //Stop Moving Right
            case SDLK_RIGHT:
                velX -= constVelX;
                currentClip = spriteClipRight[0];
                break;

            //Stop Moving Left
            case SDLK_LEFT:
                velX += constVelX;
                currentClip = spriteClipLeft[0];
                break;

            //Pick Up Key
            case SDLK_SPACE:
                pickUpKey(key1);
                pickUpKey(key2);
                pickUpKey(key3);
                break;

            default:
                break;
        }
    }
}

//Check Collision
bool Hero::checkCollision(SDL_Rect a, SDL_Rect b){

    //Sides of Rectangles A and B
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

//Check Whether Hero Touches Walls or Holes
int Hero::touchesWall(Tile* tiles[], int totalTiles, int TILE_FLOOR, int TILE_HOLE){

    //Check For All Tiles
    for(int i = 0; i < totalTiles; ++i){

        int tileType = tiles[i]->getType();

        //If Tile is of Type Wall
        if(tileType != TILE_FLOOR && tileType != TILE_HOLE){
            //If Collides
            if(checkCollision(spritePos, tiles[i]->getBox())){
                return 1;
            }
        }

        //If Tile is a Hole
        if(tileType == TILE_HOLE){

            SDL_Rect tile = tiles[i]->getBox();

            //If Bottom Half Intersects Hole
            if(spritePos.x >= tile.x && spritePos.x + spritePos.w <= tile.x + tile.w){
                if(spritePos.y + spritePos.h <= tile.y + tile.h && spritePos.y + spritePos.h/2 >= tile.y){
                    return 2;
                }
            }
        }
    }

    return 0;//Can Walk Freely
}

//Move our Hero
int Hero::moveObject(){

    int pixelsPerFrameChange = 1;//Rate of Changing Frames
    int frameCount = 0;
    int initX = spritePos.x;
    int initY = spritePos.y;
    int positionOnTile;//Is it possible to walk on Tile

    //Moving Right
    if(velX > 0){

        while(spritePos.x <= initX + velX){

            spritePos.x += pixelsPerFrameChange;
            positionOnTile = touchesWall(level->tiles, level->TOTAL_TILES, level->TILE_FLOOR, level->TILE_HOLE);

            //If Going Off Screen or Touching Wall
            if(spritePos.x + spriteWidth > LEVEL_WIDTH || positionOnTile == 1){
                spritePos.x -= pixelsPerFrameChange;
                break;
            }

            //If Falling In Hole
            if(positionOnTile == 2){
                return 99;
            }

            //Animate
            frameCount++;
            if(frameCount >= 8){
                frameCount = 0;
            }
            currentClip = spriteClipRight[frameCount];
        }
    }

    //Moving Left
    if(velX < 0){

        while(spritePos.x >= initX + velX){

            spritePos.x -= pixelsPerFrameChange;
            positionOnTile = touchesWall(level->tiles, level->TOTAL_TILES, level->TILE_FLOOR, level->TILE_HOLE);

            //If Going Off Screen or Touching Wall
            if(spritePos.x< 0 || positionOnTile == 1){
                spritePos.x += pixelsPerFrameChange;
                break;
            }

            //If Falling In Hole
            if(positionOnTile == 2){
                return 99;
            }

            //Animate
            frameCount++;
            if(frameCount >= 8){
                frameCount = 0;
            }
            currentClip = spriteClipLeft[frameCount];
        }
    }

    //Moving Down
    if(velY > 0){

        while(spritePos.y <= initY + velY){

            spritePos.y += pixelsPerFrameChange;
            positionOnTile = touchesWall(level->tiles, level->TOTAL_TILES, level->TILE_FLOOR, level->TILE_HOLE);

            //If Going Off Screen or Touching Wall
            if(spritePos.y + spriteHeight > LEVEL_HEIGHT || positionOnTile == 1){
                spritePos.y -= pixelsPerFrameChange;
                break;
            }

            //If Falling In Hole
            if(positionOnTile == 2){
                return 99;
            }

            //Animate
            frameCount++;
            if(frameCount >= 8){
                frameCount = 0;
            }
            currentClip = spriteClipDown[frameCount];
        }
    }

    //Moving Up
    if(velY < 0){

        while(spritePos.y >= initY + velY){

            spritePos.y -= pixelsPerFrameChange;
            positionOnTile = touchesWall(level->tiles, level->TOTAL_TILES, level->TILE_FLOOR, level->TILE_HOLE);

            //If Going Off Screen or Touching Wall
            if(spritePos.y < 0 || positionOnTile == 1){
                spritePos.y += pixelsPerFrameChange;
                break;
            }

            //If Falling In Hole
            if(positionOnTile == 2){
                return 99;
            }

            //Animate
            frameCount++;
            if(frameCount >= 8){
                frameCount = 0;
            }
            currentClip = spriteClipUp[frameCount];
        }
    }

    return 1;//Default Return Value
}

//Reposition Camera
void Hero::setCamera(SDL_Rect &camera, int w, int h){

    //Center Camera on Hero
    camera.x = (spritePos.x + spriteWidth / 2) - SCREEN_WIDTH / 2;
    camera.y = (spritePos.y + spriteHeight / 2) - SCREEN_HEIGHT / 2;

    //Keep Camera Within Limits
    if(camera.x < 0){
        camera.x = 0;
    }
    if(camera.y < 0){
        camera.y = 0;
    }
    if(camera.x > w - camera.w){
        camera.x = w - camera.w;
    }
    if(camera.y > h - camera.h){
        camera.y = h - camera.h;
    }

}

//Pick Up Key
void Hero::pickUpKey(Key &key){

    //If Key Is Not Already Taken
    if(key.getIsTaken() == false){

        //If Hero and Key Intersect
        if(checkCollision(Hero::spritePos, key.getPos())){
            key.keyPicked();
            keysPicked++;
        }
    }
}

//Open Door
bool Hero::openDoor(SDL_Event &e){

    //If ENTER is Pressed
    if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){

        //If Player Has Picked All Keys
        if(keysPicked == TOTAL_KEYS){

            //If Player is Next to Door
            if(spritePos.x  >= 1920 && spritePos.y <= 384){
                return true;
            }
        }

        //Print Completion Status
        cout << "\nYou have " << keysPicked << " keys with you right now." << endl;
        cout << "You still need to find " << TOTAL_KEYS - keysPicked << " keys.\n" << endl;
    }

    return false;
}

//Render Sprite - Relative to Camera
void Hero::render(int camX, int camY){
    objectTexture.render(spritePos.x - camX, spritePos.y - camY, &currentClip);
}

/**End of Hero.cpp*/
