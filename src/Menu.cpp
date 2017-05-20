/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Menu.cpp
 **Contains Menu Class Implementation
 */

#include "../include/Menu.h"

//Constructor
Menu::Menu(int w, int h, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* font){
    SCREEN_WIDTH = w;
    SCREEN_HEIGHT = h;
    window = gWindow;
    renderer = gRenderer;
    menuFont = font;

    menuButtons = new Button[TOTAL_BUTTONS];
}

//Destructor
Menu::~Menu(){
    delete []menuButtons;
    menuFont = NULL;
    window = NULL;
    renderer = NULL;
    gameTitle = NULL;
}

//Set Button Texture
SDL_Texture* Menu::setTexture(TTF_Font* font, string text, SDL_Color textColor){

    SDL_Surface* buttonSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);

    SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);

    SDL_FreeSurface(buttonSurface);

    return buttonTexture;
}


//Setup Menu
void Menu::setupMenu(){
    //Setup buttons and title

    //Button 1
    menuButtons[0].buttonText = "Start";
    menuButtons[0].hover = false;
    menuButtons[0].buttonPosition.x = 110;
    menuButtons[0].buttonPosition.y = 200;
    menuButtons[0].buttonPosition.w = BUTTON_WIDTH;
    menuButtons[0].buttonPosition.h = BUTTON_HEIGHT;
    menuButtons[0].buttonTexture = setTexture(menuFont, menuButtons[0].buttonText, buttonColor[0]);

    //Button 2
    menuButtons[1].buttonText = "Help";
    menuButtons[1].hover = false;
    menuButtons[1].buttonPosition.x = 242;
    menuButtons[1].buttonPosition.y = 300;
    menuButtons[1].buttonPosition.w = BUTTON_WIDTH;
    menuButtons[1].buttonPosition.h = BUTTON_HEIGHT;
    menuButtons[1].buttonTexture = setTexture(menuFont, menuButtons[1].buttonText, buttonColor[0]);

    //Button 3
    menuButtons[2].buttonText = "Exit";
    menuButtons[2].hover = false;
    menuButtons[2].buttonPosition.x = 370;
    menuButtons[2].buttonPosition.y = 200;
    menuButtons[2].buttonPosition.w = BUTTON_WIDTH;
    menuButtons[2].buttonPosition.h = BUTTON_HEIGHT;
    menuButtons[2].buttonTexture = setTexture(menuFont, menuButtons[2].buttonText, buttonColor[0]);

    //Game Title
    gameTitle = setTexture(menuFont, "Ruins Escapade", buttonColor[0]);
    titlePosition.x = 100;
    titlePosition.y = 50;
    titlePosition.w = 440;
    titlePosition.h = 150;
}

//Show Menu
int Menu::showMenu(){

    SDL_Event e;
    bool running = true;
    int x, y;

    while(running){

        //Poll for event
        while(SDL_PollEvent(&e) != 0){

            switch(e.type){

                //Mouse Hovering
                case SDL_MOUSEMOTION:
                    x = e.motion.x;
                    y = e.motion.y;

                    //check for all buttons
                    for(int i = 0; i < TOTAL_BUTTONS; ++i){

                        //if mouse is hovering over any of the buttons
                        if(x >= menuButtons[i].buttonPosition.x && x <= menuButtons[i].buttonPosition.x + menuButtons[i].buttonPosition.w){
                            if(y >= menuButtons[i].buttonPosition.y && y <= menuButtons[i].buttonPosition.y + menuButtons[i].buttonPosition.h){

                                //change button text color
                                if(!menuButtons[i].hover){
                                    menuButtons[i].hover = true;
                                    menuButtons[i].buttonTexture = setTexture(menuFont, menuButtons[i].buttonText, buttonColor[1]);
                                }
                            }
                        }

                        //if mouse is not hovering over button, but mouse was hovering over button previously
                        else if(menuButtons[i].hover){
                            menuButtons[i].hover = false;
                            menuButtons[i].buttonTexture = setTexture(menuFont, menuButtons[i].buttonText, buttonColor[0]);
                        }
                    }
                    break;

                //Mouse button pressed
                case SDL_MOUSEBUTTONDOWN:
                    x = e.motion.x;
                    y = e.motion.y;

                    //check for all buttons
                    for(int i = 0; i < TOTAL_BUTTONS; ++i){

                        //if mouse button was pressed when hovering over a button
                        if(x >= menuButtons[i].buttonPosition.x && x <= menuButtons[i].buttonPosition.x + menuButtons[i].buttonPosition.w){
                            if(y >= menuButtons[i].buttonPosition.y && y <= menuButtons[i].buttonPosition.y + menuButtons[i].buttonPosition.h){
                                return i + 1;
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_RenderCopy(renderer, gameTitle, NULL, &titlePosition);

        for(int i = 0; i < TOTAL_BUTTONS; ++i){
            SDL_RenderCopy(renderer, menuButtons[i].buttonTexture, NULL, &menuButtons[i].buttonPosition);
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}

/**End of Menu.cpp*/
