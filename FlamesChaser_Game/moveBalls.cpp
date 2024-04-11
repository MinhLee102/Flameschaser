#include "moveBalls.h"

movement::movement(){
    //Init position
    bPosX = SCREEN_WIDTH/2 - 20;
    bPosY = SCREEN_HEIGHT/4 + 20;

    //Initial velocity
    bVelX = 0;
    bVelY = 0;

    //Init acceleretion
    bAX = 0;
    bAY = 0;

    checkGrav = false;
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
                //bVelY += Ball_Vel;
                checkGrav = true;
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

//void movement::updateVel(int vx){
//    bVelX += vx;
//}

void movement::gravity(bool &checkGrav){
    if (checkGrav == true)
    {
       bVelY = Ball_Ac;
    }
    bPosY += bVelY;
}

void movement::destroyCollider(Circle& a){
    a.x = -20;
    a.y = -20;
    a.r = 0;
}

void movement::changeRadius(Circle& a, int newDiameter){
    a.r = newDiameter/2;
}


void movement::moving(movement Ball_move[], int n, bool merger[], int ball_num[], SDL_Rect ballClips[]){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            //int distance;
            //check collision
            if (checkCollision(Ball_move[i].getCollider(), Ball_move[j].getCollider()))
            {
                //If two ball of the same type (same radius) collided --> merge and upgrade
                if(Ball_move[i].getCollider().r == Ball_move[j].getCollider().r)
                {
                    //destroy collision box of 1 ball
                    destroyCollider(Ball_move[i].getCollider());

                    //added in array of add ball
                    merger[i] = true;

                    //upgrade balls
                    ball_num[j]++;
                    Ball_move[j].Ball_Height = ballClips[ball_num[j]].h;
                    Ball_move[j].Ball_Width = ballClips[ball_num[j]].w;
                    Ball_move[j].changeRadius(Ball_move[j].getCollider(),Ball_move[j].Ball_Width);
                    Ball_move[j].bPosY = SCREEN_HEIGHT - 70 - Ball_move[j].Ball_Height;
                }
                else
                {
//                    int overLap = (Ball_move[i].getCollider().r  + Ball_move[j].getCollider().r - distance)/2;
//                    //Calculate new velocities using conservation of momentum and energy
//                        int nx = (Ball_move[i].bPosX - Ball_move[j].bPosX) / distance;
//                        int ny = (Ball_move[i].bPosY - Ball_move[j].bPosY) / distance;
//
//                        int p = 2 * (Ball_move[i].bVelX * nx + Ball_move[i].bVelY * ny - Ball_move[j].bVelX * nx - Ball_move[j].bVelY * ny) / (Ball_move[i].bMass + Ball_move[j].bMass);
//
//                        Ball_move[i].bVelX -= p * Ball_move[j].bMass * nx;
//                        Ball_move[i].bVelY -= p * Ball_move[j].bMass * ny;
//                        Ball_move[j].bVelX += p * Ball_move[i].bMass * nx;
//                        Ball_move[j].bVelY += p * Ball_move[i].bMass * ny;
//
//                    //Separate the orbs to prevent them from overlapping
//                        //overlap = (self.radius + other_orb.radius - distance) / 2
//                        Ball_move[i].bPosX -= overLap * nx;
//                        Ball_move[i].bPosY -= overLap * ny;
//                        Ball_move[j].bPosX += overLap * nx;
//                        Ball_move[j].bPosY += overLap * ny;
                    if (Ball_move[i].getCollider().x > Ball_move[j].getCollider().x)
                    {
                        Ball_move[i].bPosX += 5;
                        Ball_move[j].bPosX -= 5;
                    }
                    else
                    {
                        Ball_move[i].bPosX -= 5;
                        Ball_move[j].bPosX += 5;
                    }
                    if (Ball_move[j].bPosX < SCREEN_WIDTH/3 + 20)
                        Ball_move[j].bPosX = SCREEN_WIDTH/3 + 20;
                    if (Ball_move[j].bPosX + Ball_move[j].Ball_Width > SCREEN_WIDTH/3 + 450)
                        Ball_move[j].bPosX = SCREEN_WIDTH/3 + 450 - Ball_Width;

                    if (Ball_move[i].bPosX < SCREEN_WIDTH/3 + 20)
                        Ball_move[i].bPosX = SCREEN_WIDTH/3 + 20;
                    if (Ball_move[i].bPosX + Ball_move[j].Ball_Width > SCREEN_WIDTH/3 + 450)
                        Ball_move[i].bPosX = SCREEN_WIDTH/3 + 450 - Ball_Width;
                }
                    Ball_move[i].shiftCollider();
                    Ball_move[j].shiftCollider();
            }
            else
                continue;
        }
    }

    if (bPosX < SCREEN_WIDTH/3 + 20)
        bPosX = SCREEN_WIDTH/3 + 20;
    if (bPosX + Ball_Width > SCREEN_WIDTH/3 + 450)
        bPosX = SCREEN_WIDTH/3 + 450 - Ball_Width;
    //Move the ball left or right
    bPosX += bVelX;
    shiftCollider();

    gravity(checkGrav);
    shiftCollider();

    if (bPosY + Ball_Height > SCREEN_HEIGHT - 70){
        bVelY = 0;
        bPosY = SCREEN_HEIGHT - 70 - Ball_Height;
    }
}

double distance2(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) + (y1 - y2)*(y1 - y2);
}

bool checkCollision(Circle& a, Circle& b){
    bool check = false;

    int TotalRadius2 = (a.r + b.r)*(a.r + b.r);

    //Collision happens when distance between centers smaller than radius of 2 circles combined
    if (TotalRadius2 >= distance2(a.x, a.y, b.x, b.y))
        {
            check = true;
            //distance = sqrt(distance2(a.x, a.y, b.x, b.y));
        }
    else
        check = false;
    return check;
}


