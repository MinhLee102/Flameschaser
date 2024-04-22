#include "game_screen.h"

game_screen::game_screen(){
    //Initialize
    m_Texture = NULL;
    mWidth = 0;
    mHeight = 0;
}

game_screen::~game_screen(){
    //Deallocate
    free();
}

bool game_screen::loadImg(std::string path, SDL_Renderer* gRenderer){
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
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255 ,255));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            std::cout << "Unable to create texture from " << path.c_str() << std::endl;
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Clear old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    m_Texture = newTexture;
    return m_Texture != NULL;
}

void game_screen::free(){
    //Free texture if it exists
    if (m_Texture != NULL)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int game_screen::getWidth(){
    return mWidth;
}

int game_screen::getHeight(){
    return mHeight;
}

void game_screen::render(int x, int y, SDL_Renderer* gRenderer){
    //Set rendering space and render to screen
    SDL_Rect renderStage = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, m_Texture, NULL, &renderStage);
}

