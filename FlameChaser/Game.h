#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;

//Texture wrapper class
class stage
{
    public:
        //Init Variables
        stage();

        //Deallocates memory
        ~stage();

        //Load image at specified path
        bool loadImg(string path);

        //Deallocate texture
        void free();

        //Render Texture at given point
        void render(int x, int y);

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

//Load indivisual image as texture
//SDL_Texture* loadTexture(std::string path);

//Create Window to render to
static SDL_Window* gWindow = NULL;
//The window renderer
static SDL_Renderer* gRenderer = NULL;

//Current displayed texture
//static SDL_Texture* gTexture = NULL;

//Scene Textures
stage StageTexture;
stage bgTexture;

bool init();

bool loadMedia();

void close();



#endif // GAME_H
