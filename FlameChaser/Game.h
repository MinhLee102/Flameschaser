#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;

//Load indivisual image as texture
SDL_Texture* loadTexture(std::string path);

//Create Window to render to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(std::string path);

