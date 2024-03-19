#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameLib.h"
#include "moveBalls.h"

class gBalls{
public:
    //Init variables
    gBalls();

    //Deallocate memory
    ~gBalls();

    //Load img
    bool loadImage(string path, SDL_Renderer* gRenderer);

    //Update width, height
    void update(int w, int h);

    //Deallocate texture
    void free();

    //render texture at given position
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect *clip = NULL);

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
