#pragma once
#include "sdl.h"
#include "../Timer/Timer.h"
#include "../Definitions/definition.h"

class WormActor
{
protected:
	Rect Transform;
	Rect TransformCollision;
	int SoundsEffects[10];
	int Img;
	int Imgs;
	Timer frameTimer;
	Rect animation;
	int frameX;
	int frameY;
	int camOfX;
	int camOfY;
public:
	void setCamX(int val) { camOfX = val; };
	void setCamY(int val) { camOfY = val; };
	
	int* getWormSoundEffect() { return SoundsEffects; };
	int getWormImg() { return Img; };
	void setTransform(int x, int y) { Transform.x = x; Transform.y = y;};
	int getWidth() { return Transform.w; };
	int getHeight() { return Transform.h; };
	int getX() { return Transform.x ;};
	int getY() { return Transform.y ;};
};

