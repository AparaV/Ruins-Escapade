/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: GameLevel.cpp
 **Contains GameLevel Class Implementation
 */

#include "../include/GameLevel.h"

//Constructor
GameLevel::GameLevel(int width, int height, SDL_Window* gWindow, SDL_Renderer* gRenderer, Hero* player){
    SCREEN_HEIGHT = height;
    SCREEN_WIDTH = width;
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    imgFlags = IMG_INIT_PNG;//Enable loading PNG images
    window = gWindow;
    globalRenderer = gRenderer;
    hero = player;
}

//Destructor
GameLevel::~GameLevel(){
    hero = NULL;
    window = NULL;
    globalRenderer = NULL;
    level = NULL;
}

//Set Level Dimensions
void GameLevel::setLevelDimensions(int x, int y){
    LEVEL_WIDTH = x * TILE_WIDTH;
    LEVEL_HEIGHT = y * TILE_HEIGHT;
}

//Load Texture
SDL_Texture* GameLevel::loadTexture(string path){

    SDL_Texture* newTexture = NULL;

    //Load Image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Error Check
    if(loadedSurface == NULL){
        cout << "Error while loading surface" << endl;
    }

    else{
        //Create Texture from Surface
        newTexture = SDL_CreateTextureFromSurface(globalRenderer, loadedSurface);

        //Error Check
        if(newTexture == NULL){
            cout << "Error while creating texture from surface" << endl;
        }

        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }

    return newTexture;
}

//Load Level
void GameLevel::loadLevel(GameMap* levelMap){

    level = levelMap;
    level->loadTiles();
    hero->setLevel(level);
}

//Start Playing the Game
int GameLevel::playLevel(){

    //Set Level Dimensions
    hero->setLevelDimensions(LEVEL_WIDTH, LEVEL_HEIGHT);

    //Setup Keys
    Key key1("Assets/Sprites/Key.png", 192, 768, 0, 0, globalRenderer);
    Key key2("Assets/Sprites/Key.png", 576, 768, 0, 0, globalRenderer);
    Key key3("Assets/Sprites/Key.png", 1152, 768, 0, 0, globalRenderer);

    //Event Handling
    SDL_Event e;
    bool running = true;

    //While Application is Still Running
    while(running){

        //Poll for Events on Queue
        while(SDL_PollEvent(&e) != 0){

            //User Requests to Quit
            if(e.type == SDL_QUIT){
                running = false;
                return 3;
            }

            //Player uses keyboard to quit or ask for help
            if(e.type == SDL_KEYDOWN ){

                if(e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q){
                    running = false;
                    return 3;
                }

                if(e.key.keysym.sym == SDLK_h || e.key.keysym.sym == SDLK_F1){
                    cout << printHelp(helpDocSrc) << endl;
                }
            }

            //Otherwise let Hero handle the event
            hero->handleEvent(e, key1, key2, key3);

            //If player attempts to open door
            if(hero->openDoor(e) == true){
                return 4;
            }
        }

        //Clear Screen
        SDL_RenderClear(globalRenderer);

        //Move Object and Camera
        if(hero->moveObject() == 99){
            return 99;//If hero falls in Hole
        }
        hero->setCamera(camera, LEVEL_WIDTH, LEVEL_HEIGHT);

        //Render items onto the texture
        level->renderMap(camera);
        key1.render(camera);
        key2.render(camera);
        key3.render(camera);
        hero->render(camera.x, camera.y);

        SDL_RenderPresent(globalRenderer);//Update renderer with the updated texture
    }

    return 1;//Default Return Value
}

/**End of GameLevel.cpp*/
