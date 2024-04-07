#ifndef MOVEBALLS_H
#define MOVEBALLS_H

#include "GameLib.h"
#include "GameObject.h"

struct Circle{
    int x, y;
    int r;
};

class movement{
public:
    //Dimension of ball
    int Ball_Width , Ball_Height;

    //Maximum velocity
    static const int Ball_Vel = 8;

    static const int Ball_Ac = 5;

    //Init variable
    movement();

    //Take key press and adjust velocity;
    void handleEvent(SDL_Event &e);

    void gravity(bool &checkGrav);

    void changeRadius(Circle& a, int newDiameter);

    void destroyCollider(Circle& a);

    //Move the ball
    //void moving(Circle Balls[], int n);
    void moving(movement Ball_move[], int n, bool merger[], int ball_num[], SDL_Rect ballClips[]);

    int getBallPosX(){return bPosX;};

    int getBallPosY(){return bPosY;};

    int getBallVelX(){return bVelX;};

    int getBallVelY(){return bVelY;};

    Circle& getCollider();

//    void updateVel(int vx);

    //Update collider
    void createCollider();

private:
    //The x and y offsets of ball
    int bPosX, bPosY;

    //Velocity of ball
    int bVelX, bVelY;

    //Acceleration of ball
    int bAX, bAY;

    //Collider of ball
    Circle mCollider;

    //Moves the collision circle relative to the dot's offset
    void shiftCollider();

    bool checkGrav;
};

    //Check collision between 2 balls
    bool checkCollision(Circle &a, Circle& b);

    //Check distances between two points
    double distance2(int x1, int y1, int x2, int y2);

#endif // MOVEBALLS_H
