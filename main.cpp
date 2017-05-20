/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **FileName: main.cpp
 **The game starts running from here
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "include/Menu.h"
#include "include/IntroductionScreen.h"
#include "include/GameLevel.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;

//Screen Dimensions Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Game Assets Source File
const string level1MapSrc = "Assets/Maps/level_1_map.map";
const string tileSpriteSrc = "Assets/Sprites/tile_sprite_sheet.png";
const string heroSpriteSrc = "Assets/Sprites/link_sprite_sheet.png";
const string helpDocSrc = "Assets/Documents/Help.txt";
const string introDocSrc = "Assets/Documents/Introduction_Text.txt";
const string fontSrc = "Assets/Fonts/Times_New_Roman.ttf";

string printHelp(string srcPath);//function to print the help document

//Main Begins
int main(int argc, char* argv[]){

    //Initialize SDL Subsystems
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window* gWindow = NULL;//The Game Window
    SDL_Renderer* gRenderer = NULL;//The Renderer
    TTF_Font* gFont = NULL;//The Font

    //Setup Window, Renderer and Font
    gWindow = SDL_CreateWindow("Ruins Escapade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    gFont = TTF_OpenFont(fontSrc.c_str(), 24);

    //Setup Game Menu
    Menu startMenu(640, 480, gWindow, gRenderer, gFont);
    startMenu.setupMenu();

    //Setup Introduction Screen
    IntroductionScreen screen(SCREEN_WIDTH, SCREEN_HEIGHT, gWindow, gRenderer, gFont);
    screen.setColor(0, 0, 0);//set text color to black
    screen.setTextPath(introDocSrc);//load the introduction text

    //Setup Hero
    Hero hero(heroSpriteSrc, 0, 0, 1, 1, gRenderer);
    hero.objectTexture.setRenderer(gRenderer);
    hero.setClipSize(0, 96, 64, 96);

    //Setup Level 1 Map
    GameMap Level1Map(286, level1MapSrc, tileSpriteSrc, gRenderer);
    Level1Map.setLevelDimensions(22, 13);

    //Setup Game Level Screen and Load Hero
    GameLevel Level1(SCREEN_WIDTH, SCREEN_HEIGHT, gWindow, gRenderer, &hero);
    Level1.setLevelDimensions(22, 13);
    Level1.loadLevel(&Level1Map);//Load the level map
    hero.setSpritePos(96, 960);

    bool playing = true;
    int currentScreen = 0;

    //Begin Playing Game

    while(playing){

        //Choose the Screen to Load
        switch(currentScreen){

            //Start Menu
            case 0:
                currentScreen = startMenu.showMenu();
                break;

            //Level 1
            case 1:
                SDL_Delay(500);
                screen.renderText();
                currentScreen = Level1.playLevel();
                break;

            //Help Document
            case 2:
                cout << printHelp(helpDocSrc) << endl;
                currentScreen = 0;
                break;

            //Quit Game
            case 3:
                cout << "You Quit Game! :(" << endl;
                playing = false;
                break;

            //Game Won
            case 4:
                cout << "You Won! :)" << endl;
                playing = false;
                break;

            //Game Lost
            case 99:
                cout << "You lost the game :(" << endl;
                playing = false;
                break;

            default:
                break;
        }

    }

    //End of Game
    cout << "\nEnd of Game" << endl;

    //Free Memory
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL Subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
//Main Ends

//Printing Help
string printHelp(string srcPath){

    ifstream fPtr(srcPath);

    if(fPtr.fail()){
        return "ERROR: Cannot load Help Document. Report Bug.";
    }

    stringstream buffer;
    buffer << fPtr.rdbuf();

    return buffer.str();
}

/**End of main.cpp*/
