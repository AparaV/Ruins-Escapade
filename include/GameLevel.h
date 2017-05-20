/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameLevel.h
 **Contains GameLevel Class- Holds information for each level and enables playing
 */

#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Texture.h"
#include "GameObject.h"
#include "Hero.h"
#include "Key.h"
#include "GameMap.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

extern const string helpDocSrc;//Declared in "main.cpp"
extern string printHelp(string);//Declared in "main.cpp"

//GameLevel Class Definition
class GameLevel{

public:

    GameLevel(int, int, SDL_Window* gWin, SDL_Renderer* gRenderer, Hero* player);//constructor
    ~GameLevel();//Destructor

    void setLevelDimensions(int x, int w);//Set Level Dimensions
    SDL_Texture* loadTexture(string path);//Load Texture
    void loadLevel(GameMap* levelMap);//Load Game Screen
    int playLevel();//Play Game

protected:

private:

    int SCREEN_WIDTH;//Screen Dimensions
    int SCREEN_HEIGHT;
    int LEVEL_WIDTH;//Level Dimensions
    int LEVEL_HEIGHT;
    const int TILE_HEIGHT = 96;//Each Tile Dimensions
    const int TILE_WIDTH = 96;

    SDL_Window* window = NULL;//Window that we will render to
    SDL_Renderer* globalRenderer = NULL;//Renderer
    GameMap* level = NULL;//Map of Level
    Hero* hero = NULL;//Hero
    SDL_Rect camera;//Camera to focus on Hero
    int imgFlags;//Enable Loading .png Files

};
//End GameLevel Definition

#endif // GAMELEVEL_H

/**End of GameLevel.h*/
