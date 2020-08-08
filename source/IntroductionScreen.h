/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: IntroductionScreen.h
 **Contains IntroductionScreen Class - Holds information to display introduction screen
 */

#ifndef INTRODUCTIONSCREEN_H
#define INTRODUCTIONSCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.h"
#include "fstream"
#include "sstream"

using std::ifstream;
using std::stringstream;

//IntroductionScreen Class Definition
class IntroductionScreen{

public:

    IntroductionScreen(int w, int h, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* gFont);//Constructor
    ~IntroductionScreen();//Destructor

    void setColor(Uint8 r, Uint8 g, Uint8 b);//set color of font
    void setTextPath(string path);//set the source of the introduction text
    string readFromFile();//read the text in file to a string
    void renderText();

protected:

private:

    SDL_Window* window = NULL;//the window
    SDL_Renderer* renderer = NULL;//the renderer
    TTF_Font* font = NULL;//font

    int SCREEN_WIDTH;//screen dimensions
    int SCREEN_HEIGHT;

    Texture textTexture;
    SDL_Color textColor;//Text Color
    string textSource = "NULL";
};
//End IntroductionScreen Definition

#endif // INTRODUCTIONSCREEN_H

/**End of IntroductionScreen.h*/
