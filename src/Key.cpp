/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Key.cpp
 **Contains Key Implementation
 */

#include "../include/Key.h"

//Constructor
Key::Key(string path, int x, int y, int constVelX, int constVelY, SDL_Renderer* renderer):
    GameObject(path, x, y, constVelX, constVelY, renderer){
    isTaken = false;
    setClipSize(0, 0, KEY_WIDTH, KEY_HEIGHT);
}

//Destructor
Key::~Key(){
    objectTexture.free();
}

//Accessors
SDL_Rect Key::getPos(){
    return spritePos;
}

bool Key::getIsTaken(){
    return isTaken;
}

//Pick Up Key
void Key::keyPicked(){
    isTaken = true;
}


//Check Collision
bool Key::checkCollision( SDL_Rect a, SDL_Rect b ){

    //Sides of Rectangles A and B
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate Sides of A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate Sides of B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //Check Intersection of Sides
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

//Render Key
void Key::render(SDL_Rect &camera){

    //If Key is not Taken
    if(isTaken == false){

        //If Key is Present on Screen, Render
        if (checkCollision(spritePos, camera)){
            objectTexture.render(spritePos.x - camera.x, spritePos.y - camera.y, &spriteClip);
        }
    }
}

/**End of Key.cpp*/
