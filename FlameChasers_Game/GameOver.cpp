#include "GameOver.h"

void GameEnd(bool &GameOver, bool &quit, int &UsedBalls, game_screen &screen, game_screen &stage, gBalls &ball,
             game_screen &End, SDL_Event &gov, SDL_Renderer* gRenderer, int ball_num[], bool merger[],
             movement Ball_move[], int& score, game_screen& word, bool isDrop[], set<int>& droppedBall,
             set<int>& mergedBall){
    while (GameOver){
        while(SDL_PollEvent(&gov) != 0){

            //if user want to play again
            if(gov.type == SDL_KEYDOWN && gov.key.keysym.sym == SDLK_r)
            {
                //change gameover flags to false to quit
                GameOver = false;

                //Reset game
                for (int i = 0; i < 400; i++){
                    ball_num[i] = rand()%3;
                }

                for (int i = 0; i < UsedBalls; i++){
                    if(merger[i] == true)
                        merger[i] = false;

                    if(isDrop[i] == true)
                        isDrop[i] = false;

                    Ball_move[i].reset();
                }

                droppedBall.clear();
                mergedBall.clear();

                UsedBalls = 0;
                score = 0;
                SDL_RenderClear(gRenderer);

            }
            if((gov.type == SDL_KEYDOWN && gov.key.keysym.sym == SDLK_q) ||
               (gov.type == SDL_KEYDOWN && gov.key.keysym.sym == SDLK_ESCAPE)){
                    quit = true;
                    GameOver = false;
               }
        }

        //Render Game Over Screen
        End.render(EndImgX, EndImgY, gRenderer);

        //render highscore
        word.render(word.updateRenderPosX(HighScoreX), word.updateRenderPosY(HighScoreY), gRenderer);
        SDL_RenderPresent(gRenderer);
    }
}
