/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameObject.cpp
 **Contains GameObject implementation
 */

#include "DynamicObject.h"

//Constructor
DynamicObject::DynamicObject(string path, int x, int y, int unitVelocityX, int unitVelocityY, SDL_Renderer* renderer)
    :Object(path, x, y, renderer) {
    velX = 0;
    velY = 0;
    this->unitVelocityX = unitVelocityY;
    this->unitVelocityY = unitVelocityX;
}

//Destructor
DynamicObject::~DynamicObject(){
    objectTexture.free();//Deallocate Texture
}

/**End of GameObject.cpp*/
