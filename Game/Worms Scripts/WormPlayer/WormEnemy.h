#pragma once
#include "Worm.h"
class WormEnemy :
    public Worm
{
public:
    void update();
    void setPlayerWorms(WormPhysics* w) { mWorms.push_back(w); };
    void init();
    void render();
private:
    std::vector<WormPhysics*> mWorms;
    int FocusedWorm;
    int CaminarIntents;
    bool alreadyJump;
    Timer startDelay;

    void getNearestWorm();
    void moveToNearestWorm();
    int checkDistance();
    void throwGranade();
    void updateAnimation();
};

