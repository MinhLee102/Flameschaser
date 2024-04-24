#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "game_screen.h"
#include "GameLib.h"
#include "GameObject.h"
#include "moveBalls.h"

void GameEnd(bool &GameOver, bool &quit, int &UsedBalls, game_screen &screen, game_screen &stage, gBalls &ball,
             game_screen &End, SDL_Event &gov, SDL_Renderer* gRenderer, int ball_num[], bool merger[],
             movement Ball_move[], int &score, game_screen& word, bool isDrop[],set<int>& droppedBall,
             set<int>& mergedBall);

#endif // GAMEOVER_H
