/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: IntroductionScreen.cpp
 **Contains IntroductionScreen Class Implementation
 */

#include "../include/IntroductionScreen.h"

//Constructor
IntroductionScreen::IntroductionScreen(int w, int h, SDL_Window* gWindow, SDL_Renderer* gRenderer, TTF_Font* gFont){
    SCREEN_HEIGHT = h;
    SCREEN_WIDTH = w;
    window = gWindow;
    renderer = gRenderer;
    font = gFont;
    textTexture.setFont(font);
    textTexture.setRenderer(renderer);
}

//Destructor
IntroductionScreen::~IntroductionScreen(){
    window = NULL;
    renderer = NULL;
    font = NULL;
}

//Set Color of Font
void IntroductionScreen::setColor(Uint8 red, Uint8 green, Uint8 blue){
    textColor = {red, green, blue};
}

//Set text source
void IntroductionScreen::setTextPath(string path){
    textSource = path;
}

//Read Text from File into String
string IntroductionScreen::readFromFile(){

    ifstream filePtr;
    filePtr.open(textSource);

    if(filePtr.fail()){
        return "ERROR: File Not Found";
    }

    //read file
    stringstream buffer;
    buffer << filePtr.rdbuf();

    return buffer.str();
}

//Render Text
void IntroductionScreen::renderText(){

    //clear renderer
    SDL_RenderClear(renderer);

    string text = readFromFile();

    textTexture.loadFromRenderedText(text, textColor);

    textTexture.render((SCREEN_WIDTH - textTexture.getWidth()) / 2, (SCREEN_HEIGHT - textTexture.getHeight()) / 2);

    //update renderer
    SDL_RenderPresent(renderer);

    SDL_Event e;

    //run infinitely
    while(true){

        //poll for events
        while(SDL_PollEvent(&e) != 0){

            //if user presses ENTER
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
                //stop function
                return;
            }
        }

    }
}
