#include "GameLib.h"
#include "game_screen.h"
#include "GameObject.h"
#include "moveBalls.h"
#include "Menu.h"

//Create Window to render to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;

//Game screen
game_screen StageTexture;

game_screen bgTexture;

game_screen menu;

gBalls ball;

SDL_Rect ballClips[4];

int UsedBalls = 0;

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
    srand(time(0));

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

            //Init menu flags
            bool isMenu = true;

            //Handle event
            SDL_Event e;
            SDL_Event m;

            //Create Ball's movement
            movement Ball_move[300];

            //init flag
            bool merger[300];

            int ball_num[300];

            for (int i = 0; i < 80; i++)
                ball_num[i] = rand()%4;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    //User request quit
                    if (e.type == SDL_QUIT)
                        quit = true;

                    //Handle input for ball
                    Ball_move[UsedBalls].handleEvent(e);
                }

                //create game's menu
                openMenu(isMenu, gRenderer, menu, m);
                SDL_RenderClear(gRenderer);
                menu.free();

                frameStart = SDL_GetTicks();

                Ball_move[UsedBalls].Ball_Width = ballClips[ball_num[UsedBalls]].w;
                Ball_move[UsedBalls].Ball_Height = ballClips[ball_num[UsedBalls]].h;
                Ball_move[UsedBalls].createCollider();


                // Clear Screen
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);

                //Render Background Texture to screen
                bgTexture.render(0,0, gRenderer);

                //Render GameStage to Screen
                StageTexture.render(SCREEN_WIDTH/3, SCREEN_HEIGHT/3, gRenderer);

                //move the ball and Ball collider box
                //for (int i = 0; i < UsedBalls+1; i++)
                Ball_move[UsedBalls].moving(Ball_move, UsedBalls, merger, ball_num, ballClips);

                cout << UsedBalls << " ";
                //Render ball and check border
                for (int i = 0; i < UsedBalls+1; i++){
                    if (merger[i] == true)
                        continue;
                    ball.render(Ball_move[i].getBallPosX(), Ball_move[i].getBallPosY(), gRenderer, &ballClips[ball_num[i]]);
                }

                if (Ball_move[UsedBalls].getBallPosY() > SCREEN_HEIGHT/4 + 20 && Ball_move[UsedBalls].getBallVelX() == 0 && Ball_move[UsedBalls].getBallVelY() == 0 )
                    UsedBalls++;

                //cout << UsedBalls;

                //cout << UsedBalls;
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
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0)
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

    if (!bgTexture.loadImg("img/Hall_29.jpg", gRenderer))
    {
        cout << "Failed to load Background! " << endl;
        success = false;
    }
    if (!menu.loadImg("img/startMenuv3.png", gRenderer))
    {
        cout << "Failed to load Menu! " << endl;
        success = false;
    }
    if (! ball.loadImage("img/g_m_e_f.png", gRenderer))
    {
        //cout << BallRenderer[0] << endl;
        cout << "Failed to load Object \n";
        success = false;
    }

    //Select sprite
    ballClips[0].x = 60;
    ballClips[0].y = 0;
    ballClips[0].w = 40;
    ballClips[0].h = 35;

    ballClips[1].x = 0;
    ballClips[1].y = 0;
    ballClips[1].w = 60;
    ballClips[1].h = 46;

//    ballClips[2].x = 100;
//    ballClips[2].y = 0;
//    ballClips[2].w = 100;
//    ballClips[2].h = 93;

    ballClips[2].x = 200;
    ballClips[2].y = 0;
    ballClips[2].w = 80;
    ballClips[2].h = 67;

    ballClips[3].x = 100;
    ballClips[3].y = 0;
    ballClips[3].w = 100;
    ballClips[3].h = 93;

//    if (! ball[1].loadImage("img/Griseo_ballv2.png", gRenderer))
//    {
//        cout << "Failed to load Object \n";
//        success = false;
//    }
    return success;
}

void close(){
    //Free loaded image
    StageTexture.free();
    bgTexture.free();
    menu.free();
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
