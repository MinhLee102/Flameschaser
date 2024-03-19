#include "moveBalls.h"

movement::movement(){
    //Init position
    bPosX = SCREEN_WIDTH/2 - 20;
    bPosY = SCREEN_HEIGHT/4 + 20;

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
            case SDLK_DOWN:
                if (bVelY > 0)
                    break;
                bVelY += Ball_Vel;
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

    if ((bPosX - Ball_Width < SCREEN_WIDTH/3 - 20 )|| (bPosX + Ball_Width > SCREEN_WIDTH/3 + 450))
        bPosX -= bVelX;

    //Apply Gravity-like effect
    bPosY += bVelY;
    if (bPosY + Ball_Height > SCREEN_HEIGHT - 70)
        bVelY = 0;
}

