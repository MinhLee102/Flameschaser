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

SDL_Rect ballClips[7];

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

    //Init flag to track Game over condition
    bool GameOver = false;

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
            movement Ball_move[400];

            //init flag
            bool merger[400];
            bool isDrop = false;

            int ball_num[400];

            for (int i = 0; i < 350; i++)
                ball_num[i] = rand()%4;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    //User request quit
                    if (e.type == SDL_QUIT)
                        quit = true;

                    //Handle input for ball
                    Ball_move[UsedBalls].handleEvent(e, isDrop);
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

                //Set next ball render position
                int RPosX = Next_Ball_Center_X - ballClips[ball_num[UsedBalls+1]].w/2;
                int RPosY = Next_Ball_Center_Y - ballClips[ball_num[UsedBalls+1]].h/2;

                //Render next ball to spawn
                ball.render(RPosX, RPosY, gRenderer, &ballClips[ball_num[UsedBalls+1]]);

                //Render ball and check border
                for (int i = 0; i <= UsedBalls; i++){
                    if (merger[i] == true)
                        continue;
                    Ball_move[i].motionNcollision(Ball_move, UsedBalls, merger, ball_num, ballClips, i, GameOver);
                    Ball_move[i].updateRenderPos();
                    ball.render(Ball_move[i].getBallPosX(), Ball_move[i].getBallPosY(), gRenderer, &ballClips[ball_num[i]]);
                }

                while(GameOver == true){
                    cout << "Game Over" << endl;
                }
                //count the number of the balls were used
                if(isDrop == true){
                    UsedBalls++;
                    isDrop = false;
                }
                //cout << UsedBalls << " ";

                //SDL_RenderDrawLine(gRenderer, 0, 200, SCREEN_WIDTH, 200);
                //Update screen
                SDL_RenderPresent(gRenderer);

                //cout << HighScore(UsedBalls, merger) << " ";
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

    if (!bgTexture.loadImg("img/Hall_29v2.png", gRenderer))
    {
        cout << "Failed to load Background! " << endl;
        success = false;
    }
    if (!menu.loadImg("img/startMenuv4.png", gRenderer))
    {
        cout << "Failed to load Menu! " << endl;
        success = false;
    }
    if (! ball.loadImage("img/allCharacters.png", gRenderer))
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

    ballClips[4].x = 280;
    ballClips[4].y = 0;
    ballClips[4].w = 110;
    ballClips[4].h = 114;

    ballClips[5].x = 390;
    ballClips[5].y = 0;
    ballClips[5].w = 120;
    ballClips[5].h = 120;

    ballClips[6].x = 510;
    ballClips[6].y = 0;
    ballClips[6].w = 130;
    ballClips[6].h = 127;

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
