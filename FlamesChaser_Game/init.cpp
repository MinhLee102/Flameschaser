#include "init.h"

bool game::init(SDL_Window* gWindow, SDL_Renderer* gRenderer){
    bool success = true;

    //Initialize SDL
    if ( SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        //set texture filtering to linear
        if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
            cout << "Warning: Linear texture filtering not enabled!";

        //Create Window
        gWindow = SDL_CreateWindow("FlamesChaser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL)
        {
            cout << "Window could not be created! " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            //Create Renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL)
            {
                cout << "Renderer could not be created! " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                //init renderer color
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                int imgFlags = IMG_INIT_PNG;
                if ( !(IMG_Init(imgFlags) & imgFlags))
                    {
                        cout << "SDL image could not be rendered: " << SDL_GetError();
                        success = false;
                    }
            }
        }
    }
    return success;
}
