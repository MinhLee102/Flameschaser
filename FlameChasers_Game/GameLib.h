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

using namespace std;

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;

const int GAME_LEFT_SIDE = SCREEN_WIDTH/3 + 22;
const int GAME_RIGHT_SIDE = SCREEN_WIDTH/3 + 450;
const int GAME_BOTTOM = SCREEN_HEIGHT - 70;
const int Next_Ball_Center_X = 110;
const int Next_Ball_Center_Y = 320;

int HighScore(const int &UsedBalls, bool merger[]);

#endif // GAMELIB_H
