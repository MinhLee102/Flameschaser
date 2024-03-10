#include "Game.h"

int main(int argc, char* args[]){
    if ( !init() ){
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        if(!loadMedia())
            cout << "Failed to load media!" << endl;
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
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);

                //Render Background Texture to screen
                bgTexture.render(0,0);

                //Render GameStage to Screen
                StageTexture.render(333, 150);

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

stage::stage(){
    //Initialize
    m_Texture = NULL;
    mWidth = 0;
    mHeight = 0;
}

stage::~stage(){
    //Deallocate
    free();
}

bool stage::loadImg(string path){
    //Get rid of pre-existing texture
    free();
    //the final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "Unable to load image " << SDL_GetError() << endl;
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255 , 255));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
            cout << "Unable to create texture from " << path.c_str() << endl;
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

void stage::free(){
    //Free texture if it exists
    if (m_Texture != NULL)
    {
        SDL_DestroyTexture(m_Texture);
        m_Texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

int stage::getWidth(){
    return mWidth;
}

int stage::getHeight(){
    return mHeight;
}

void stage::render(int x, int y){
    //Set rendering space and render to screen
    SDL_Rect renderStage = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, m_Texture, NULL, &renderStage);
}

//SDL_Texture* loadTexture(string path){
//    //the final texture
//    SDL_Texture* newTexture = NULL;
//
//    //Load image at specified path
//    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//    if (loadedSurface == NULL)
//        cout << "Unable to load image " << SDL_GetError() << endl;
//    else
//    {
//        //Create texture from surface pixels
//        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//
//        if(newTexture == NULL)
//            cout << "Unable to create texture from " << path.c_str() << endl;
//
//        //Clear old texture
//        SDL_FreeSurface(loadedSurface);
//    }
//    return newTexture;
//}

bool loadMedia(){
    //Initialize flag
    bool success = true;

    //Load the Game Stage
    if ( !StageTexture.loadImg("img/Gamesv3.png"))
    {
        cout << "Failed to load Game Stage! " << endl;
        success = false;
    }

    if (!bgTexture.loadImg("F:/UET - VNU/LapTrinhNangCao/FlamesChaser/FlameChaser/img/Hall_29.png"))
    {
        cout << "Failed to load Background! " << endl;
        success = false;
    }
    return success;
}

void close(){
    //Free loaded image
    StageTexture.free();
    bgTexture.free();

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL Subsystems
    IMG_Quit();
    SDL_Quit();
}

