/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameObject.cpp
 **Contains GameObject implementation
 */

#include "Object.h"

//Constructor
Object::Object(string path, int x, int y, SDL_Renderer* renderer){

    spriteSourcePath = path;
    spritePos.x = x;
    spritePos.y = y;

    //Setup texture
    objectTexture.setRenderer(renderer);
    objectTexture.loadFromFile(spriteSourcePath);
}

//Destructor
Object::~Object(){
    objectTexture.free();//Deallocate Texture
}

//Position Accessors
int Object::getPosX(){
    return spritePos.x;
}

int Object::getPosY(){
    return spritePos.x;
}

//Set Level Dimensions
void Object::setLevelDimensions(int x, int y){
    LEVEL_WIDTH = x;
    LEVEL_HEIGHT = y;
}

//Set Clip Size
void Object::setClipSize(int x, int y, int w, int h){
    spriteClip.x = x;
    spriteClip.y = y;
    spriteClip.w = w;
    spriteClip.h = h;

    spritePos.h = h;
    spritePos.w = w;
}

void Object::setRenderer(SDL_Renderer* renderer) {
    objectTexture.setRenderer(renderer);
}

//Render Object - Relative to Camera Position
void Object::render(int camX, int camY){
    objectTexture.render(spritePos.x - camX, spritePos.y - camY, &spriteClip);
}

/**End of GameObject.cpp*/
