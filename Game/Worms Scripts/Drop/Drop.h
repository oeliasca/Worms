#pragma once
#include "../../Engine/Physics/WormPhysics.h"

enum DropStates { APPEAR, DROP, LANDED };

class Drop :
    public WormPhysics
{
    int ID;
    int Quantity;
    DropStates state;
public:
    Drop(int id);
    int getDropID() { return ID; };
    int getDropQuantity() { return Quantity; };
    void update();
    void render();
};

