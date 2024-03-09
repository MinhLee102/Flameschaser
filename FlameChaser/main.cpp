#include "Game.h"

int main(int argc, char** argv){
    if ( !init() ){
        printf( "Failed to initialize!\n" );
    }
    else
    {
        if(!loadMedia())
            printf( "Failed to load media!\n" );
        else
        {
            bool quit = false;
            SDL_Event e;
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    //User request quit
                    if (e.type == SDL_QUIT)
                        quit = true;
                }

                // Clear Screen
                SDL_RenderClear(gRenderer);

                //Render Texture to Screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}

bool init(){
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
        gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

SDL_Texture* loadTexture(string path){
    //the final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "Unable to load image " << SDL_GetError() << endl;
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture == NULL)
            cout << "Unable to create texture from " << path.c_str() << endl;

        //Clear old texture
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia(){
    //Initialize flag
    bool success = true;

    //Load PNG texture
    gTexture = loadTexture("img/Hall_29.png");
    if (gTexture == NULL)
    {
        std::cout << "Failed to load image " << endl;
        success = false;
    }
    return success;
}

void close(){
    //Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL Subsystems
    IMG_Quit();
    SDL_Quit();
}

