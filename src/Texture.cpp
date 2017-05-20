/**Ruins Escapade
 **Author: Aparajithan Venkateswaran
 **Filename: Texture.cpp
 **Contains Texture Implementation
 */

#include "../include/Texture.h"

//Constructor
Texture::Texture(){
    mWidth = 0;
    mHeight = 0;
}

//Destructor
Texture::~Texture(){
    free();
}

//Dimension Accessors
int Texture::getHeight(){
    return mHeight;
}

int Texture::getWidth(){
    return mWidth;
}

//Set Renderer
void Texture::setRenderer(SDL_Renderer* renderer){
    gRenderer = renderer;
}

//Set Font
void Texture::setFont(TTF_Font* gFont){
    font = gFont;
}

//Loading Texture from File
bool Texture::loadFromFile(string path){

    free();//Remove preexisting textures

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());//Load Image

    //Create Texture and Set Dimensions
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight= loadedSurface->h;

    mTexture = newTexture;

    //Deallocate Memory
    SDL_FreeSurface(loadedSurface);
    newTexture = NULL;

    return (mTexture != NULL);
}

//Load Text
void Texture::loadFromRenderedText(string text, SDL_Color textColor){

    free();//Remove preexisting textures

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, 600);

    //Error Check
    if(textSurface == NULL){
        cout << "Error while rendering surface" << endl;
        return;
    }

    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    //Error Check
    if(mTexture == NULL){
        cout << "Error while creating texture" << endl;
        return;
    }

    //Set Dimensions
    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);//Free Memory
}

//Render Texture
void Texture::render(int x, int y, SDL_Rect* clip){

    //Set Rendering Space
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Set Custom Rendering Dimensions
    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

//Deallocator
void Texture::free(){

    //Free Memory
    if(mTexture != NULL){
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

/**End of Texture.cpp*/
