/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Key.h
 **Contains Key class - Holds information for Keys
 **Derived from GameObject
 */

#ifndef KEY_H
#define KEY_H

#include "Object.h"
#include "Player.h"
#include <iostream>

using std::string;

//Key:GameObject Definition
class Key : protected Object{

public:
    Key(string path, int x, int y, SDL_Renderer* renderer);//Constructor
    ~Key();//Destructor

    SDL_Rect getPos();//Get Key Position
    bool getIsTaken();//Get <isTaken>

    void keyPicked();//Pick Up Key
    bool checkCollision(SDL_Rect a, SDL_Rect b);//Check Collision
    void render(SDL_Rect &camera);//Render Key

protected:

private:

    bool isTaken;
    const int KEY_HEIGHT = 96;//Key Dimensions
    const int KEY_WIDTH = 96;

};
//End Key Definition

#endif // KEY_H

/**End of Key.h*/
