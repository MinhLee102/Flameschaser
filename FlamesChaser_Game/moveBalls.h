#ifndef MOVEBALLS_H
#define MOVEBALLS_H

#include "GameLib.h"
#include "GameObject.h"

class movement{
public:
    //Dimension of ball
    int Ball_Width , Ball_Height;

    //Maximum velocity
    static const int Ball_Vel = 5;

    //Init variable
    movement();

    //Take key press and adjust velocity;
    void handleEvent(SDL_Event &e);

    //Move the ball
    void moving();

    //Shows ball on the screen
    //  void render(SDL_Renderer* gRenderer);

    int getBallPosX(){return bPosX;};

    int getBallPosY(){return bPosY;};

    int getBallVelX(){return bVelX;};

    int getBallVelY(){return bVelY;};

private:
    //The x and y offsets of ball
    int bPosX, bPosY;

    //Velocity of ball
    int bVelX, bVelY;

};

#endif // MOVEBALLS_H
