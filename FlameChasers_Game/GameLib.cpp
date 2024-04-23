#include "GameLib.h"

void HighScore(const int &UsedBalls, bool merger[], int& score){
    for(int i = 0; i < UsedBalls; i++)
    {
        if(merger[i] == true)
            score *= 2;
        else
            continue;
    }

    score = UsedBalls*200;
}
