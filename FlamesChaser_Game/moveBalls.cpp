#include "moveBalls.h"

movement::movement(){
    //Init position
    bPosX = SCREEN_WIDTH/2 - 20;
    bPosY = SCREEN_HEIGHT/4 + 20;

    //Initial velocity
    bVelX = 0;
    bVelY = 0;
}

Circle& movement::getCollider(){
    return mCollider;
}

void movement::createCollider(){
    mCollider.x = bPosX + Ball_Width/2;
    mCollider.y = bPosY + Ball_Height/2;
    mCollider.r = Ball_Width/2;
}

void movement::shiftCollider(){
    mCollider.x = bPosX + Ball_Width/2;
    mCollider.y = bPosY + Ball_Height/2;
}

void movement::gravity(){

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

void movement::updateVel(int vx){
    bVelX += vx;
}

void movement::moving(movement Ball_move[], int n){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (checkCollision(Ball_move[i].getCollider(), Ball_move[j].getCollider()))
            {
                if (Ball_move[i].getCollider().x > Ball_move[j].getCollider().x)
                {
                    Ball_move[i].bPosX += Ball_Vel;
                    Ball_move[j].bPosX -= Ball_Vel;
                }
                else
                {
                    Ball_move[i].bPosX -= Ball_Vel;
                    Ball_move[j].bPosX += Ball_Vel;
                }
                Ball_move[i].shiftCollider();
                Ball_move[j].shiftCollider();
            }
            else
                continue;
        }
    }
    //Move the ball left or right
    bPosX += bVelX;
    shiftCollider();

    if ((bPosX < SCREEN_WIDTH/3 + 20 )|| (bPosX + Ball_Width > SCREEN_WIDTH/3 + 450))
        bPosX -= bVelX;

    //Apply Gravity-like effect
    bPosY += bVelY;
    shiftCollider();

    if (bPosY + Ball_Height > SCREEN_HEIGHT - 70)
        bVelY = 0;
}

double distance2(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) + (y1 - y2)*(y1 - y2);
}

bool checkCollision(Circle& a, Circle& b){
    bool check = false;

    int TotalRadius2 = (a.r + b.r)*(a.r + b.r);

    //Collision happens when distance between centers smaller than radius of 2 circles combined
    if (TotalRadius2 >= distance2(a.x, a.y, b.x, b.y))
        check = true;
    else
        check = false;
    return check;
}


