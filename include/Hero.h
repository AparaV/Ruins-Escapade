/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Hero.h
 **Contains Hero Class - Holds information about Hero object
 **Child of GameObject
 */

#ifndef HERO_H
#define HERO_H

#include "GameObject.h"
#include "GameMap.h"
#include "Key.h"

using std::string;

class Key;//Forward Declaration

//Hero:GameObject Definition
class Hero : public GameObject{

public:
    const int spriteWidth = 64;//Sprite Dimensions
    const int spriteHeight = 96;

    Hero(string path, int x, int y, int constVelX, int constVelY, SDL_Renderer* renderer, GameMap* level = NULL);//Constructor
    ~Hero();//Destructor

    void initiateSpriteClips();//Load Sprite Sheet
    void setLevel(GameMap* lvl);//Set GameMap
    void setSpritePos(int x, int y);//Set Initial Position

    void handleEvent(SDL_Event &e, Key &key1, Key &key2, Key &key3);//Event Handler
    bool checkCollision(SDL_Rect a, SDL_Rect b);//Check Collision
    int touchesWall(Tile* tiles[], int totalTiles, int TILE_FLOOR, int TILE_HOLE);//Check Whether Hero Touches Wall
    int moveObject();//Move Hero
    void setCamera(SDL_Rect &camera, int w, int h);//Reposition Camera
    void pickUpKey(Key &key);//Pick Up Key
    bool openDoor(SDL_Event &e);//Open Door
    void render(int camX, int camY);//Render Hero

protected:

private:

    SDL_Rect spriteClipLeft[8];//Frames to Cut for Animation
    SDL_Rect spriteClipRight[8];
    SDL_Rect spriteClipUp[8];
    SDL_Rect spriteClipDown[8];
    int FRAME;//Current Animation Frame

    SDL_Rect currentClip;//Current Position
    int startPosX, startPosY;//Starting Position


    GameMap* level;//Pointer to Level map
    int keysPicked;//Number of Keys Picked
    const int TOTAL_KEYS = 3;//Total Keys to Pick

};
//End Hero Definition

#endif // HERO_H

/**End of Hero.h*/
