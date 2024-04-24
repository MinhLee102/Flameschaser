#include "GameLib.h"

void HighScore(const int &UsedBalls, bool isDrop[], int& score, set<int>& droppedBall,
               bool merger[], set<int>& mergedBall){
    for(int i = 0; i < UsedBalls; i++)
    {
        if(mergedBall.find(i) == mergedBall.end() && merger[i] == true)
        {
            score += 300;
            mergedBall.insert(i);
        }
        if(droppedBall.find(i) == droppedBall.end() && isDrop[i] == true){
            score += 200;
            droppedBall.insert(i);
        }
        else
            continue;
    }
}


