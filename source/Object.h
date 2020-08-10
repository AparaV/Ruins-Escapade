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
class Object{

public:

    Object() {};
    Object(string path, int x, int y, SDL_Renderer* renderer);//Constructor
    virtual ~Object();//Destructor

    virtual int getPosX();//Position Getters
    virtual int getPosY();
    virtual void setLevelDimensions(int x, int y);//Level Dimensions Setter
    virtual void setClipSize(int x, int y, int w, int h);//Sprite Size Setter

    virtual void setRenderer(SDL_Renderer* renderer);
    virtual void render(int camX, int camY);//Render Object onto Window

protected:
    string spriteSourcePath;//Sprite Path
    SDL_Rect spritePos;//Sprite Offset
    SDL_Rect spriteClip;//Information to Clip Image from Source

    int LEVEL_WIDTH;//Level Dimensions
    int LEVEL_HEIGHT;
    const int SCREEN_WIDTH = 640;//Screen Dimensions
    const int SCREEN_HEIGHT = 320;

    Texture objectTexture;//Texture Containing Object

private:

};
//End GameObject Definition

#endif // GAMEOBJECT_H

/**End of GameObject.h*/
