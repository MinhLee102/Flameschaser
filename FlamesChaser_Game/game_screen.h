#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "GameLib.h"

class game_screen
{
public:
    //Init Variables
    game_screen();

    //Deallocate Texture
    ~game_screen();

    //Load image at specified path
    bool loadImg(std::string path, SDL_Renderer* gRenderer);

    //Deallocate texture
    void free();

    //Render Texture at given point
    void render(int x, int y, SDL_Renderer* gRenderer);

    //Get image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture* m_Texture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

////Game screen
//game_screen StageTexture;
//
//game_screen bgTexture;

#endif // GAME_SCREEN_H
