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
    bool loadImg(string path, SDL_Renderer* gRenderer);

    bool loadText(string text, SDL_Color TextColor, SDL_Renderer* gRenderer, TTF_Font* font);

    //Deallocate texture
    void free();

    //Render Texture at given point
    void render(int x, int y, SDL_Renderer* gRenderer);

    //adjust Render position
    int updateRenderPosX(const int x);
    int updateRenderPosY(const int y);

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


#endif // GAME_SCREEN_H
