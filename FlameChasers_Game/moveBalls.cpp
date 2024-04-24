#include "moveBalls.h"

movement::movement(){
    //Init position
    this->x = StartPosX;
    this->y = StartPosY;

    //Initial velocity
    bVelX = 0;
    bVelY = 0;

    //Init acceleretion
    bAX = 0;
    bAY = 0;

    checkGrav = false;
    degrees = 0;
}

void movement::reset(){
    //Reset to initial position
    this->x = StartPosX;
    this->y = StartPosY;

    //Initial velocity
    bVelX = 0;
    bVelY = 0;

    //Init acceleretion
    bAX = 0;
    bAY = 0;

    checkGrav = false;
    degrees = 0;
}

Circle& movement::getCollider(){
    return mCollider;
}

void movement::createCollider(){
    //set collider center to ball center and radius
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
    //shift collider according to ball current position
    mCollider.x = this->x;
    mCollider.y = this->y;
}

void movement::handleEvent(SDL_Event &e, bool drop[], const int &UsedBalls){
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
                drop[UsedBalls] = true;
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
    //shift collider outside of screen
    a.x = -20;
    a.y = -20;

    //set radius back to zero
    a.r = 0;
    a.m = 0;
}
//
void movement::changeRadiusnMass(Circle& a, int newDiameter){
    a.r = newDiameter/2;
    a.m += 2;
}

void movement::motionNcollision(movement Ball[], int n, bool merger[], int ball_num[], SDL_Rect ballClips[],
                                int current, bool &GameOver, Mix_Chunk* Pop){
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

    this->prevX = this->x;
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
        //check collision with bottom border
        if(Ball[i].y + Ball[i].mCollider.r >= GAME_BOTTOM){
            Ball[i].y = GAME_BOTTOM - Ball[i].mCollider.r;
            Ball[i].bVelY = -1 * Ball[i].bVelY * 0.2;
            Ball[i].shiftCollider();
        }

        //check collision with left side border
        if(this->x - mCollider.r - 1 <= GAME_LEFT_SIDE && this->y > SCREEN_HEIGHT/4 - 30)
        {
            this->x = GAME_LEFT_SIDE + mCollider.r;
            bVelX = -1*bVelX*0.2;
            bAX = 0.1;
            this->prevX = GAME_LEFT_SIDE + mCollider.r;
            shiftCollider();
        }
        //check collision with right side border
        else if (mCollider.x + mCollider.r + 1 >= GAME_RIGHT_SIDE && this->y > SCREEN_HEIGHT/4 - 30)
        {
            this->x = GAME_RIGHT_SIDE - mCollider.r;
            bVelX = -1*bVelX*0.2;
            bAX = -0.1;
            this->prevX = GAME_RIGHT_SIDE - mCollider.r;
            shiftCollider();
        }
        else
            bAX = 0;

       //if ball is not the current ball
       if(i != current)
        {
            //Calculate distance between 2 balls center
            double d2 = distance2(this->x, this->y, Ball[i].x, Ball[i].y);

            //check collision if distance square <= sum of two ball radius square
            if(d2 <= (this->mCollider.r + Ball[i].getCollider().r)* (this->mCollider.r + Ball[i].getCollider().r) && this->y >= 150)
            {

                if(Ball[i].bPosY <= LinePosY || this->bPosY <= LinePosY){
                    cnt++;
                    if (cnt == 10)
                    {
                        GameOver = true;
                        cnt = 0;
                    }
                }
                //check merge condition: radius are the same and it is not the last ball (Radius = 65)
                else if(Ball[i].getCollider().r == this->getCollider().r && this->mCollider.r != 65 && Ball[i].y > SCREEN_HEIGHT/4 )
                {
                    //destroy collision box of 1 ball
                    destroyCollider(Ball[i].getCollider());

                    //added in array of merged ball
                    merger[i] = true;

                    //sound effect when merges
                    Mix_PlayChannel(-1, Pop, 0);

                    //upgrade balls
                    ball_num[current]++;
                    Ball[current].Ball_Height = ballClips[ball_num[current]].h;
                    Ball[current].Ball_Width = ballClips[ball_num[current]].w;

                    //Correct ball positions
                    int prevRad = mCollider.r;
                    Ball[current].changeRadiusnMass(this->getCollider(),this->Ball_Width);
                    this->y = this->y - (this->getCollider().r - prevRad);
                    this->shiftCollider();

                    SDL_Delay(50);
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

                        prevX = this->x;
                        Ball[i].prevX = Ball[i].x;

                        //seperate the ball to avoid overlapping
                        double overLap = (this->getCollider().r + Ball[i].getCollider().r - sqrt(d2))/2;
                        this->x -= overLap * nx;
                        this->y -= overLap * ny;
                        Ball[i].x += overLap * nx;
                        Ball[i].y += overLap * ny;

                        //Add angle to make the ball roll
                        if(this->x - prevX > 0)
                            this->degrees++;
                        if(this->x - prevX < 0)
                            this->degrees--;

                        if(Ball[i].x - prevX > 0)
                            Ball[i].degrees++;
                        if(Ball[i].x - prevX < 0)
                            Ball[i].degrees--;

                    }
                    Ball[i].shiftCollider();
                    this->shiftCollider();
                }

            }
        }
        this->prevX = this->x;
        Ball[i].prevX = Ball[i].x;

    }

    //Reset acceleration
    this->bAX = 0;
    this->bAY = 0;
}

void movement::updateRenderPos(){
    bPosX = this->x - Ball_Width/2;
    bPosY = this->y - Ball_Height/2;
}

//Calculate distance between two point on screen
double distance2(int x1, int y1, int x2, int y2){
    return (x1-x2)*(x1-x2) + (y1 - y2)*(y1 - y2);
}


