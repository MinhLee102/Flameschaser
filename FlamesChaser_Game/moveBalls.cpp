#include "moveBalls.h"

movement::movement(){
    //Init position
    bPosX = 500;
    bPosY = 120;

    //Initial velocity
    bVelX = 0;
    bVelY = 0;
}

void movement::handleEvent(SDL_Event &e){
    //if key pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_LEFT:
                bVelX -= Ball_Vel;
                break;
            case SDLK_RIGHT:
                bVelX += Ball_Vel;
                break;
        }
    }
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_LEFT:
                    bVelX += Ball_Vel;
                    break;
                case SDLK_RIGHT:
                    bVelX -= Ball_Vel;
                    break;
            }
        }
}


void movement::moving(){
    //Move the ball left or right
    bPosX += bVelX;

    if (bPosX < 346 || bPosX + Ball_Width > 669)
        bPosX -= bVelX;

    bPosY += bVelY;
    if (bPosY < 0 || bPosY + Ball_Height >  SCREEN_HEIGHT)
        bPosY -= bVelY;
}
