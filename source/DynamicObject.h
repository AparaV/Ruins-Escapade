/** Ruins Escapade
 ** Author: Aparajithan Venkateswaran
 ** Filename: GameObject.h
 ** Contains GameObject class - A generic outline for all of the game objects
 ** Parent of Hero.h and Key.h
 */

#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.h"
#include "Texture.h"

using std::string;

class DynamicObject : public Object {

public:
    DynamicObject(string path, int x, int y, int maxVelX, int maxVelY, SDL_Renderer* renderer);//Constructor
    virtual ~DynamicObject();//Destructor

    virtual void handleEvent() {};
    virtual int move() { return 0; };
    virtual void animate() {};

protected:

    int velX, velY;//Object Velocity
    int unitVelocityX, unitVelocityY;//Maximum Velocity

private:

};

#endif // DYNAMICOBJECT_H
