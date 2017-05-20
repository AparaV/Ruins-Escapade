/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameObject.cpp
 **Contains GameObject implementation
 */

#include "../include/GameObject.h"

//Constructor
GameObject::GameObject(string path, int x, int y, int constVelX, int constVelY, SDL_Renderer* renderer){

    spriteSourcePath = path;
    spritePos.x = x;
    spritePos.y = y;
    velX = 0;//Initially body at rest
    velY = 0;
    this->constVelX = constVelX;
    this->constVelY = constVelY;

    //Setup texture
    objectTexture.setRenderer(renderer);
    objectTexture.loadFromFile(spriteSourcePath);
}

//Destructor
GameObject::~GameObject(){
    objectTexture.free();//Deallocate Texture
}

//Position Accessors
int GameObject::getPosX(){
    return spritePos.x;
}

int GameObject::getPosY(){
    return spritePos.x;
}

//Set Level Dimensions
void GameObject::setLevelDimensions(int x, int y){
    LEVEL_WIDTH = x;
    LEVEL_HEIGHT = y;
}

//Set Clip Size
void GameObject::setClipSize(int x, int y, int w, int h){
    spriteClip.x = x;
    spriteClip.y = y;
    spriteClip.w = w;
    spriteClip.h = h;

    spritePos.h = h;
    spritePos.w = w;
}

//Event Handler
void GameObject::handleEvent(SDL_Event &e){

    //If a key is pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){

        //Change the velocity
        switch(e.key.keysym.sym){

            case SDLK_UP:
                velY -= constVelY;//Decrease Y-velocity
                break;

            case SDLK_DOWN:
                velY += constVelY;//Increase Y-velocity
                break;

            case SDLK_RIGHT:
                velX += constVelX;//Increase X-velocity
                break;

            case SDLK_LEFT:
                velX -= constVelX;//Decrease X-velocity
                break;

            default:
                break;
        }
    }

    //If key was released
    else if(e.type == SDL_KEYUP && e.key.repeat == 0){

        //Change velocity
        switch(e.key.keysym.sym){

            case SDLK_UP:
                velY += constVelY;//Increase Y-velocity
                break;

            case SDLK_DOWN:
                velY -= constVelY;//Decrease Y-velocity
                break;

            case SDLK_RIGHT:
                velX -= constVelX;//Decrease X-velocity
                break;

            case SDLK_LEFT:
                velX += constVelX;//Increase X-velocity
                break;

            default:
                break;
        }
    }
}

//Motion of Object
void GameObject::moveObject(){

    //Move object left or right
    spritePos.x += velX;

    //If object goes off screen
    if((spritePos.x < 0) || (spritePos.x + spritePos.w > LEVEL_WIDTH)){
        spritePos.x -= velX;
    }

    //Move object up or down
    spritePos.y += velY;

    //If object goes off screen
    if((spritePos.y < 0) || (spritePos.y + spritePos.h > LEVEL_HEIGHT)){
        spritePos.y -= velY;
    }

}

//Render Object - Relative to Camera Position
void GameObject::render(int camX, int camY){
    objectTexture.render(spritePos.x - camX, spritePos.y - camY, &spriteClip);
}

/**End of GameObject.cpp*/
