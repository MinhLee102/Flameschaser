#ifndef MOVEBALLS_H
#define MOVEBALLS_H

#include "GameLib.h"
#include "GameObject.h"

struct Circle{
    int x, y;
    int r;
    //Ball mass
    int m;
};

class movement{
public:
    //Dimension of ball
    int Ball_Width , Ball_Height;

    //Maximum velocity
    static const int Ball_Vel = 8;

    static const int Ball_Ac = 10;

    int cnt = 0;

    //Init variable
    movement();

    //Reset game object
    void reset();

    //Take key press and adjust velocity;
    void handleEvent(SDL_Event &e, bool drop[], const int &UsedBalls);

    void changeRadiusnMass(Circle& a, int newDiameter);

    void destroyCollider(Circle& a);

    //Move the ball and handle collision
    void motionNcollision(movement Ball_move[], int n, bool merger[], int ball_num[], SDL_Rect ballClips[],
                          int current, bool &GameOver, Mix_Chunk* Pop);

    void updateRenderPos();

    int getBallPosX(){return bPosX;};

    int getBallPosY(){return bPosY;};

    int getBallVelX(){return bVelX;};

    int getBallVelY(){return bVelY;};

    double getAngle(){return degrees;};

    Circle& getCollider();

//    void updateVel(int vx);

    //Update collider
    void createCollider();

private:
    //The x and y to Render ball
    int bPosX, bPosY;

    //the x and y of center
    int x, y;

    //Velocity of ball
    int bVelX, bVelY;

    //Acceleration of ball
    int bAX, bAY;

    //Collider of ball
    Circle mCollider;

    //Moves the collision circle relative to the dot's offset
    void shiftCollider();

    //rotation angle
    double degrees;

    bool checkGrav;

    int prevX;
};

    //Check distances between two points
    double distance2(int x1, int y1, int x2, int y2);

#endif // MOVEBALLS_H
