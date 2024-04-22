#include "GameLib.h"

int HighScore(const int &UsedBalls, bool merger[]){
    int score;
    for(int i = 0; i < UsedBalls; i++)
    {
        if(merger[i] == true)
            score += 200;
        else
            continue;
    }

    score = UsedBalls*200;
    return score;
}
