#include "GameObject.h"

gBalls::gBalls(){
    Balls = NULL;
    b_width = 0;
    b_height = 0;
}

gBalls::~gBalls(){
    free();
}

bool gBalls::loadImage(string path, SDL_Renderer* gRenderer){
    //Get rid of pre-existing texture
    free();
    //the final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        std::cout << "Unable to load image " << SDL_GetError() << std::endl;
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255 , 255));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            std::cout << "Unable to create texture from " << path.c_str() << std::endl;
        else
        {
            //Get image dimensions
            b_width = loadedSurface->w;
            b_height = loadedSurface->h;
        }

        //Clear old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    Balls = newTexture;
    return Balls != NULL;
}

void gBalls::free(){
    //Free texture if exists
    if (Balls != NULL){
        SDL_DestroyTexture(Balls);
        b_width = 0;
        b_height = 0;
        Balls = NULL;
    }
}

int gBalls::getWidth(){
    return b_width;
}

int gBalls::getHeight(){
    return b_height;
}

void gBalls::render(int x, int y, SDL_Renderer* gRenderer){
    SDL_Rect GameBalls = {x, y, b_width, b_height};
    SDL_RenderCopy(gRenderer, Balls, NULL, &GameBalls );
}

