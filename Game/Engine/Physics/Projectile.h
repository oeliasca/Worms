#pragma once
#include "WormPhysics.h"
#include <vector>
#include "../Timer/Timer.h"

class Projectile :
    public WormPhysics
{
private:
    bool isClicked;
    int xClickIni;
    int yClickIni;
    int Damage;
    int ID;
    int Power; // de llençament
    float TimePressed;
    Timer PowerTimer;
public:
    Projectile(int id);
    ~Projectile();
    
    void update(std::vector<WormPhysics*>* Wroms, int index);
    void render();
    void setPower(int p,float angle);
    void setDistanceFromObjective(std::vector<WormPhysics*>*Wroms);//mirem si tenim un worm dins explosio
    void setxClickIni(int x) { xClickIni = x; };
    void setyClickIni(int y) { yClickIni = y; };

};

