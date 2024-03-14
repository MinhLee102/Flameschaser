#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameLib.h"

class gBalls{
public:
    //Init variables
    gBalls();

    //Deallocate memory
    ~gBalls();

    //Load img
    bool loadImage(string path, SDL_Renderer* gRenderer);

    //Deallocate texture
    void free();

    //render texture at given position
    void render(int x, int y, SDL_Renderer* gRenderer);

    //Get image dimension
    int getWidth();
    int getHeight();

private:
    //image texture
    SDL_Texture* Balls;
    int b_width;
    int b_height;
};

#endif // GAMEOBJECT_H
