#include "GameLib.h"
#include "game_screen.h"
#include "GameObject.h"
#include "moveBalls.h"
#include "Menu.h"
#include "GameOver.h"

//Create Window to render to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;

//The music that will be played
Mix_Music* Piano = NULL;

//The sound effect that will be used
Mix_Chunk* Pop = NULL;

//Game screen
game_screen StageTexture;
game_screen bgTexture;

//Game menu
game_screen menu;

//Game tutorial
game_screen tutorial;

//GameOver screen
game_screen End;

//Ball texture
gBalls ball;
SDL_Rect ballClips[7];

//Globally used font
TTF_Font* font = NULL;
TTF_Font* bestscore = NULL;
SDL_Color TextColor = {0, 0, 0};

//used to manage word
game_screen word;
game_screen bestscr;

//Numbers of balls that were used
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

            //init score
            int score = 0;

            //Init menu & tutorial flags
            bool isMenu = true;
            bool isTutorial = true;

            //Init flag to track Game over condition
            bool GameOver = false;

            //Handle event
            SDL_Event e;
            SDL_Event m;
            SDL_Event gov;

            //In memory text stream
            stringstream timeText;

            //Keep track of ball that were drop
            set<int> droppedBall;

            //Keep track of ball that were merged
            set<int> mergedBall;

            //Create Ball's movement
            movement Ball_move[400];

            //init flag
            bool merger[400];

            //bool isDrop = false;
            bool isDrop[400];

            int ball_num[400];

            for (int i = 0; i < 400; i++)
                ball_num[i] = rand()%3;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    //User request quit
                    if (e.type == SDL_QUIT)
                        quit = true;

                    //Handle key press
                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym )
                        {
                            case SDLK_l:
                                //if there is no music playing
                                if( Mix_PlayingMusic() == 0)
                                {
                                    //Play the music
                                    Mix_PlayMusic(Piano, -1);
                                }
                                //if music is being played
                                else
                                {
                                    //If the music is paused
                                    if( Mix_PausedMusic() == 1)
                                        //Resume music
                                        Mix_ResumeMusic();

                                    //if the music is playing
                                    else
                                        //paused the music
                                        Mix_PauseMusic();
                                }
                                break;

                            case SDLK_m:
                                //Stop the music
                                Mix_HaltMusic();
                                break;
                        }
                    }

                    //Handle input for ball
                    Ball_move[UsedBalls].handleEvent(e, isDrop, UsedBalls);
                }

                //create game's menu
                openMenu(isMenu, gRenderer, menu, m);
                SDL_RenderClear(gRenderer);
                menu.free();

                //render game tutorial
                Guide(isTutorial, gRenderer, tutorial, m);
                SDL_RenderClear(gRenderer);
                tutorial.free();

                //Update score
                HighScore(UsedBalls, isDrop, score, droppedBall, merger, mergedBall);

                //Set text to render
                timeText.str(" ");
                timeText << score;
                if(!word.loadText(timeText.str().c_str(), TextColor, gRenderer, font))
                {
                    cout << "Unable to render time text! \n";
                }

                if(!bestscr.loadText(timeText.str().c_str(), TextColor, gRenderer, bestscore))
                {
                    cout << "Unable to render time text! \n";
                }


                frameStart = SDL_GetTicks();

                //Create new ball on the screen
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
                    Ball_move[i].motionNcollision(Ball_move, UsedBalls, merger, ball_num, ballClips, i, GameOver, Pop);
                    Ball_move[i].updateRenderPos();
                    ball.render(Ball_move[i].getBallPosX(), Ball_move[i].getBallPosY(), gRenderer,
                                &ballClips[ball_num[i]], Ball_move[i].getAngle(), NULL, SDL_FLIP_NONE);
                }

                //print Highscore to the screen
                word.render(word.updateRenderPosX(ScorePosX), word.updateRenderPosY(ScorePosY), gRenderer);

                //count the number of the balls were used
                if(isDrop[UsedBalls] == true){
                    UsedBalls++;
                }

                //Render end screen if conditions are met
                GameEnd(GameOver, quit, UsedBalls, bgTexture, StageTexture, ball, End, gov, gRenderer, ball_num,
                        merger, Ball_move, score, bestscr, isDrop, droppedBall, mergedBall);

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

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if ( !(IMG_Init(imgFlags) & imgFlags))
                    {
                        cout << "SDL image could not be rendered: " << SDL_GetError();
                        success = false;
                    }

                //Initialize SDL_TTF
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				//Initialize SDL_Mixer
				if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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

    //Load menu
    if (!menu.loadImg("img/startMenuv4.png", gRenderer))
    {
        cout << "Failed to load Menu! " << endl;
        success = false;
    }

    //Load tutorial
    if(!tutorial.loadImg("img/tutorial.png", gRenderer))
    {
        cout << "Failed to load tutorial! \n";
        success = false;
    }

    //Load ball img
    if (!ball.loadImage("img/allCharacters.png", gRenderer))
    {
        cout << "Failed to load Object \n";
        success = false;
    }

    //Load game over screen
    if(!End.loadImg("img/Game_overv4.png", gRenderer))
    {
        cout << "Failed to load End Screen \n";
        success = false;
    }

    //Load font
    font = TTF_OpenFont("ShadeBlue.ttf", 28);
    if(font == NULL)
    {
        cout << "Failed to load font \n";
        success = false;
    }

    bestscore = TTF_OpenFont("ShadeBlue.ttf", 60);
    if(bestscore == NULL)
    {
        cout << "Failed to load font \n";
        success = false;
    }

    //Load music
    Piano = Mix_LoadMUS("Sound/Scott Buckley - Jul.mp3");
    if(Piano == NULL)
    {
        cout << "Failed to load music \n";
        success = false;
    }

    //Load sound effect
    Pop = Mix_LoadWAV("Sound/Popping_sound.wav");
    if(Pop == NULL)
    {
        cout << "Failed to load sound effect \n";
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

    return success;
}

void close(){
    //Free loaded image
    StageTexture.free();
    bgTexture.free();
    menu.free();
    tutorial.free();
    ball.free();
    End.free();
    word.free();
    bestscr.free();

    //Free global font
	TTF_CloseFont(font);
	TTF_CloseFont(bestscore);
	font = NULL;
	bestscore = NULL;

	//Free the music
	Mix_FreeMusic(Piano);
	Piano = NULL;

	//Free sound effect
	Mix_FreeChunk(Pop);
	Pop = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL Subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
