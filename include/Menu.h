/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Menu.h
 **Contains Menu Class - Holds information for displaying Start Menu
 */

#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.h"

using std::string;

//Button Structure Definition
struct Button{

public:

    string buttonText;
    bool hover = false;
    SDL_Texture* buttonTexture;
    SDL_Rect buttonPosition;

};
//End Button Definition

//Menu Class Definition
class Menu{

public:

    Menu(int, int, SDL_Window*, SDL_Renderer*, TTF_Font*);//Constructor
    ~Menu();//Destructor

    SDL_Texture* setTexture(TTF_Font* font, string text, SDL_Color textColor);//Set Texture with Text
    void setupMenu();//Setup Menu
    int showMenu();//Render Menu

protected:

private:

    int SCREEN_WIDTH;//Screen Dimensions
    int SCREEN_HEIGHT;

    TTF_Font* menuFont;//Font
    SDL_Window* window;//Window
    SDL_Renderer* renderer;//Renderer

    //Buttons
    const int TOTAL_BUTTONS = 3;
    Button* menuButtons;
    SDL_Color buttonColor[2] = {{255, 255, 255}, {105, 105, 105}};
    const int BUTTON_WIDTH = 155;
    const int BUTTON_HEIGHT = 100;

    //Game Title
    SDL_Texture* gameTitle;
    SDL_Rect titlePosition;
};
//End Menu Definition

#endif // MENU_H

/**End of Menu.h*/
