#include "moveBalls.h"

movement::movement(){
    //Init position
    bPosX = SCREEN_WIDTH/2 - 20;
    bPosY = SCREEN_HEIGHT/4 - 30;

    this->x = bPosX + Ball_Width/2;
    this->y = bPosY + Ball_Height/2;

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
    mCollider.x = this->x;
    mCollider.y = this->y;
    mCollider.r = Ball_Width/2;

    switch(mCollider.r){
        case 20:
            mCollider.m = 2;
        case 30:
            mCollider.m = 4;
        case 40:
            mCollider.m = 8;
        case 50:
            mCollider.m = 10;
        case 55:
            mCollider.m = 12;
        case 60:
            mCollider.m = 14;
        case 65:
            mCollider.m = 16;
    }
}

void movement::shiftCollider(){
//    mCollider.x = bPosX + Ball_Width/2;
//    mCollider.y = bPosY + Ball_Height/2;
    mCollider.x = this->x;
    mCollider.y = this->y;
}

void movement::handleEvent(SDL_Event &e, bool &drop){
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
                checkGrav = true;
                drop = true;
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

void movement::destroyCollider(Circle& a){
    a.x = -20;
    a.y = -20;
    a.r = 0;
    a.m = 0;
}
//
void movement::changeRadiusnMass(Circle& a, int newDiameter){
    a.r = newDiameter/2;
    a.m += 1;
}

void movement::motionNcollision(movement Ball[], int n, bool merger[], int ball_num[], SDL_Rect ballClips[], int current, bool &GameOver){
//Apply Gravity
if(checkGrav == true){
        this->y += Ball_Vel;
        this->bAY += 0.1;

        //Update velocity
        this->bVelX += this->bAX;
        this->bVelY += this->bAY;

    //Limit max velocity
    int max_speed = 2;
    int speed = sqrt(bVelX*bVelX + bVelY*bVelY);
    if (speed > max_speed)
    {
        bVelX *= max_speed/speed;
        bVelY *= max_speed/speed;
    }

    //Update position
    this->x += bVelX;
    this->y += bVelY;

    //check collision with bottom
    if(mCollider.y + mCollider.r >= GAME_BOTTOM){
        this->y = GAME_BOTTOM - mCollider.r;
        this->bVelY = -1 * bVelY * 0.2;
        shiftCollider();
    }
    //check collision with sides of box
    if(this->x - mCollider.r <= GAME_LEFT_SIDE)
    {
        this->x = GAME_LEFT_SIDE + mCollider.r;
        bVelX = -1*bVelX*0.2;
        bAX = 0.1;
        shiftCollider();
    }
    else if (mCollider.x + mCollider.r >= GAME_RIGHT_SIDE)
    {
        this->x = GAME_RIGHT_SIDE - mCollider.r;
        bVelX = -1*bVelX*0.2;
        bAX = -0.1;
        shiftCollider();
    }

    else
        bAX = 0;

    //cout << bVelX << " " << bVelY;
}
else{
    //Move the ball left or right
    this->x += bVelX;
    if (this->x - mCollider.r <= GAME_LEFT_SIDE)
        this->x = mCollider.r + GAME_LEFT_SIDE;
    if(this->x + mCollider.r >= GAME_RIGHT_SIDE)
        this->x = GAME_RIGHT_SIDE - mCollider.r;
    shiftCollider();
}

    //Check collision
    for (int i = 0; i < n; i++)
    {
        if(Ball[i].y + Ball[i].mCollider.r >= GAME_BOTTOM){
            Ball[i].y = GAME_BOTTOM - Ball[i].mCollider.r;
            Ball[i].bVelY = -1 * Ball[i].bVelY * 0.2;
            Ball[i].shiftCollider();
        }
       if(i != current)
        {
            //double distance2 = sqrt((this->x - Ball[i].x)*(this->x - Ball[i].x) + (this->y - Ball[i].y)*(this->y - Ball[i].y));
            double d2 =distance2(this->x, this->y, Ball[i].x, Ball[i].y);
            if(d2 <= (this->mCollider.r + Ball[i].getCollider().r)* (this->mCollider.r + Ball[i].getCollider().r) && this->y >= 200)
            {
                if(Ball[i].bPosY < 200 || this->bPosY < 200){
                    cnt++;
                    if (cnt == 5)
                    {
                        cout << "Game Over" << " ";
                        cnt = 0;
                    }
                }
                else if(Ball[i].getCollider().r == this->getCollider().r && this->mCollider.r != 65 && Ball[i].y > SCREEN_HEIGHT/4 )
                {
                    //destroy collision box of 1 ball
                    destroyCollider(Ball[i].getCollider());

                    //added in array of add ball
                    merger[i] = true;

                    //upgrade balls
                    ball_num[current]++;
                    Ball[current].Ball_Height = ballClips[ball_num[current]].h;
                    Ball[current].Ball_Width = ballClips[ball_num[current]].w;
                    int prevRad = mCollider.r;
                    Ball[current].changeRadiusnMass(this->getCollider(),this->Ball_Width);
                    this->y = this->y - (this->getCollider().r - prevRad);
                    this->shiftCollider();
                }
                else
                {
                    if(d2 != 0)
                    {
                        //Calculate new velocities using conservation of momentum and energy
                        double nx = (Ball[i].x - this->x)/sqrt(d2);
                        double ny = (Ball[i].y - this->y)/sqrt(d2);
                        double p = 2 * (this->bVelX*nx + this->bVelY*ny - Ball[i].bVelX*nx - Ball[i].bVelY*ny)/(Ball[i].getCollider().m + this->getCollider().m);
                        this->bVelX -= p * Ball[i].getCollider().m * nx;
                        this->bVelY -= p * Ball[i].getCollider().m * ny;
                        Ball[i].bVelX += p * this->getCollider().m * nx;
                        Ball[i].bVelY += p * this->getCollider().m * ny;

                        //seperate the ball to avoid overlapping
                        double overLap = (this->getCollider().r + Ball[i].getCollider().r - sqrt(d2))/2;
                        this->x -= overLap * nx;
                        this->y -= overLap * ny;
                        Ball[i].x += overLap * nx;
                        Ball[i].y += overLap * ny;
                    }
                    Ball[i].shiftCollider();
                    this->shiftCollider();
                }

            }
        }
    }

    //Reset acceleration
    this->bAX = 0;
    this->bAY = 0;
}

void movement::updateRenderPos(){
    bPosX = this->x - Ball_Width/2;
    bPosY = this->y - Ball_Height/2;
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

