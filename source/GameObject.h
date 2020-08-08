/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameObject.h
 **Contains GameObject class - A generic outline for all of the game objects
 **Parent of Hero.h and Key.h
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"

using std::string;

//GameObject Definition
class GameObject{

public:
    Texture objectTexture;//Texture Containing Object

    GameObject(string path, int x, int y, int constVelX, int constVelY, SDL_Renderer* renderer);//Constructor
    ~GameObject();//Destructor

    int getPosX();//Position Getters
    int getPosY();
    void setLevelDimensions(int x, int y);//Level Dimensions Setter
    void setClipSize(int x, int y, int w, int h);//Sprite Size Setter

    void handleEvent(SDL_Event &e);//Object Event Handler
    void moveObject();//Move Object
    void render(int camX, int camY);//Render Object onto Window

protected:
    string spriteSourcePath;//Sprite Path
    SDL_Rect spritePos;//Sprite Offset
    int velX, velY;//Object Velocity
    int constVelX, constVelY;//Maximum Velocity
    SDL_Rect spriteClip;//Information to Clip Image from Source

    int LEVEL_WIDTH;//Level Dimensions
    int LEVEL_HEIGHT;
    const int SCREEN_WIDTH = 640;//Screen Dimensions
    const int SCREEN_HEIGHT = 320;

private:

};
//End GameObject Definition

#endif // GAMEOBJECT_H

/**End of GameObject.h*/
