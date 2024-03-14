#include "GameLib.h"
#include "game_screen.h"
#include "init.h"
#include "GameObject.h"
#include "moveBalls.h"

//Create Window to render to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;

//Game screen
game_screen StageTexture;

game_screen bgTexture;

gBalls ball;

//Initialize SDL
bool init();

//Load screen
bool loadMedia();

//Free resources
void close();

int main(int argc, char* args[]){

    //Limit framerate
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if ( !init() ){
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        if(!loadMedia())
            cout << "Failed to load media!" << endl;
        else
        {
            //Init quit flags
            bool quit = false;

            //Handle event
            SDL_Event e;

            //Create Ball's movement
            movement Ball_move;

            //Take ball dimension
//            movement::Ball_Width = gBalls::getWidth();
//            movement::Ball_Height = gBalls::getHeight();

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    //User request quit
                    if (e.type == SDL_QUIT)
                        quit = true;

                    //Handle input for ball
                    Ball_move.handleEvent(e);
                }

                frameStart = SDL_GetTicks();

                // Clear Screen
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);

                //Render Background Texture to screen
                bgTexture.render(0,0, gRenderer);

                //Render GameStage to Screen
                StageTexture.render(333, 150, gRenderer);

                //move the ball
                Ball_move.moving();

//                //Set action based on current key input
//                const Uint8* currentKeystates = SDL_GetKeyboardState(NULL);
//                if (currentKeystates[SDL_SCANCODE_LEFT])
//                {
//                    Ball_move.bVelX -= Ball_move.Ball_Vel;
//                }
//                else if (currentKeystates[SDL_SCANCODE_RIGHT])
//                {
//                    Ball_move.bVelX += Ball_move.Ball_Vel;
//                }
//                else
//                {
//                    Ball_move.bVelX = 0;
//                }

                //Render ball
                ball.render(Ball_move.getBallPosX(), Ball_move.getBallPosY(), gRenderer);


                //Update screen
                SDL_RenderPresent(gRenderer);

                frameTime = SDL_GetTicks() - frameStart;

                if (frameDelay > frameTime)
                {
                    SDL_Delay(frameDelay - frameTime);
                }
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

bool loadMedia(){
    //Initialize flag
    bool success = true;

    //Load the Game Stage
    if ( !StageTexture.loadImg("img/Gamesv5.png", gRenderer))
    {
        cout << "Failed to load Game Stage! " << endl;
        success = false;
    }

    if (!bgTexture.loadImg("F:/UET - VNU/LapTrinhNangCao/FlamesChaser/FlameChaser/img/Hall_29.png", gRenderer))
    {
        cout << "Failed to load Background! " << endl;
        success = false;
    }
    if (! ball.loadImage("img/mobius_ballv4.png", gRenderer))
    {
        cout << "Failed to load Object \n";
        success = false;
    }
    return success;
}

void close(){
    //Free loaded image
    StageTexture.free();
    bgTexture.free();
    ball.free();

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL Subsystems
    IMG_Quit();
    SDL_Quit();
}
