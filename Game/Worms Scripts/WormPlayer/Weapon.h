#pragma once
#include "../../Engine/Physics/Projectile.h"
#include "../../Engine/Player/WormActor.h"
class Weapon :
    public WormActor
{
public:
    Weapon(int id);
    int ID; // és igual al i(iteracio) del array d'armes del worm
    Projectile* pProjectile;
    int Ammo;
    Projectile* shoot();
    
};

