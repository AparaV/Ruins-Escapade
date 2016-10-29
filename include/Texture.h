/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Texture.h
 **Contains Texture class - Holds methods for loading and rendering textures
 */

#ifndef Texture_H
#define Texture_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

//Texture Definition
class Texture{

public:
    Texture();//Constructor
    ~Texture();//Destructor

    int getWidth();//Get Dimensions
    int getHeight();
    void setRenderer(SDL_Renderer* renderer);//Set Renderer
    void setFont(TTF_Font* gFont);//Set Font

    bool loadFromFile(string path);//Load Texture
    void loadFromRenderedText(string text, SDL_Color textColor);//Load Text
    void render(int x, int y, SDL_Rect* clip = NULL);//Render Texture
    void free();//Deallocate Memory

protected:

private:
    SDL_Texture* mTexture = NULL;
    SDL_Renderer* gRenderer = NULL;
    TTF_Font* font = NULL;
    int mWidth;
    int mHeight;

};
//End Texture Definition

#endif // Texture_H

/**End of Texture.h*/
