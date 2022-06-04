#pragma once
#include "sdl.h"
#include "../Definitions/definition.h"
class Video
{
	static Video* pInstance;

	Video();
public:
	
	~Video();
	static Video* getInstance();
	void renderRect(int x, int y, int w, int h, int r,int g,int b, int a);
	void renderGraphic(int img, int posX, int posY, int width, int height);
	void renderGraphic(int img, int posXS, int posYS, int wS, int hS, int posXT, int posYT, int wT, int hT);
	void renderText(int img, int posX, int posY, int width, int height);
	void renderGraphic(int img, int posX, int posY, int width, int height,double angle,Vec2 pivot,Flip flip);
	void renderGraphic(int img, int posX, int posY, int width, int height, Rect &sRect,double angle = 0, Vec2* pivot = NULL, Flip flip = FLIP_NONE);
	void clearScreen(unsigned int color_key);
	void updateScreen();
	void waitTime(int ms);
	void close();
	Uint32 getTicks() { return SDL_GetTicks(); };
	SDL_Window* gWindow;
	SDL_Renderer* gScreen;
	void vSync();
private:
	float msFrame;
	unsigned int lastTime;
	unsigned int currentTime;
	unsigned int deltaTime;
};

