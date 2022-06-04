#pragma once
#include "../../Engine/Physics/WormPhysics.h"
#include "Weapon.h"
#include "../../Engine/Timer/Timer.h"
#include "../../Engine/UI/UIComponent.h"

enum States{MOVING, JUMPING, AIMING, SHOOT, IDLE, DEATH, HIT, FALLING, WAITING, LANDING, BEGINGAME, PREPAREJUMP, LANDINGHIT};

class Worm :
    public WormPhysics
{
protected:
    int HealthPoints;
    States WromsState;
    float MaxJump;
    std::vector <Weapon*> WeaponSlot;

    int Puntuacio;
    bool Rigth; // true mira dreta, false esquerre
    bool isShoot;
    int IndexWeapon;

    Timer PowerTimer;
    float TimePressed;
    float Power;

    int xClickIni;
    int yClickIni;

    UIComponent* wormUIname;
    UIComponent* wormUIMaxPower;
    UIComponent* wormUICurrentPower;
    UIComponent* wormUISignal;

    Timer SignalTimer;
    bool showSignal;

public:
    Worm();
    void update();
    void render();

    int getHealth() {return HealthPoints;};
    void setHealth(int HP);
    int getIndexWeapon() { return IndexWeapon; };
    
    void updateAnimation();
    Weapon* getpWeapon(int i) {return WeaponSlot.at(i); };
    States getWormState() { return WromsState; };
    void getPowerandAngle(float& power, float& cosangle, float& sinangle) {
        power = Power;
        cosangle = cosAngle;
        sinangle = sinAngle;
    }
    void setWormState(States newState) { WromsState = newState; };

    void throwGranade();
    void shootGun();
    int getClickX() { return xClickIni; };
    int getClickY() { return yClickIni; };

    bool isProjectileReleased;

    void refreshTimer();
    UIComponent* getUI() { return wormUIname; };

    void renderSignal();

    void setWormName(const char* name);

    void playSound(int i);
};

