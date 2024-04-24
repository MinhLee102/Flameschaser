#ifndef GAMELIB_H
#define GAMELIB_H

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;

const int GAME_LEFT_SIDE = SCREEN_WIDTH/3 + 15;
const int GAME_RIGHT_SIDE = SCREEN_WIDTH/3 + 335;
const int GAME_BOTTOM = SCREEN_HEIGHT - 45;
const int Next_Ball_Center_X = 80;
const int Next_Ball_Center_Y = 250;

const int StartPosX = SCREEN_WIDTH/2;
const int StartPosY = SCREEN_HEIGHT/4 - 30;

const int EndImgX = SCREEN_WIDTH/3 - 220;
const int EndImgY = SCREEN_HEIGHT/3 - 130;

const int HighScoreX = 510;
const int HighScoreY = 250;

const int ScorePosX = SCREEN_WIDTH - 87;
const int ScorePosY = 180;

const int LinePosY = 150;


void HighScore(const int &UsedBalls, bool isDrop[], int& score, set<int>& droppedBall,
               bool merger[], set<int>& mergedBall);

#endif // GAMELIB_H
