#pragma once
#include "../Player/WormActor.h"
#include "../Timer/Timer.h"
#include <vector>



class WormPhysics :
    public WormActor
{
protected:
    float AngleAnimacio; // Angle de rotació
    float VelocityX;
    float VelocityY;
    bool isTouched;
    float AcceleracioX;
    float AcceleracioY;
    float g;//Sera la gravetat
    bool stable;
    float radius;
    float lastTime;
    float friction;
    Timer temps;
    float acumulatePixelX;
    float acumulatePixelY;
    Timer SyncPhysics;
    float cosAngle;
    float sinAngle;
    int rebots; // -1 = player / 0 = missil(peta de una) / n = cantitat rebots i peta
    float explosionRange;
    Vec2 AlturaMax;
    Vec2 AlturaMin;
    Vec2 AmpleMin;
    Vec2 AmpleMax;
    std::vector <bool> VerticalCollision;
public:
    WormPhysics(float x=0.0f, float y = 0.0f, float r=2.0f, float fr=0.1);
    bool checkCollision(int img, float radi,float IniAngle,float EndAngle);
    bool checkCollisionPoints(int img,float TestPostX, float TestPostY);
    bool checkExplosionCollision(); // retorna isTouched
    void translatePhysicsObjects();
    void setUpParabolicTrajectory(float _ax,float _ay);
    void resetPhysicsTimer() { temps.resetTimer(); };
    int getRebots() { return rebots; };
    void checkWormCollision(std::vector<WormPhysics*>* Wroms);
    bool checkCollisionGround(int imgSB, int& npixels);
    int FrontVerticlaCollision(int imgSB, bool right);
    void setXAcceleration(float acceleraciox) { AcceleracioX = acceleraciox; };
    int rayCast(int x, int y, int Xclick, int Yclick, std::vector<WormPhysics*>* Worms, int radi, int torn);
    void setRebots(int n) { rebots = n; };
    
    float getExplosionRange() { return explosionRange; };

    virtual int Dummy() { return 0; };

    void offset(Rect* rect, int& xOffset, int& yOffset);
    void SetPixel(int img, int imgT, Uint32 X, Uint32 Y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float radi);
};

//28,43 peu
//left 18,42-40
//right w-18/42-40