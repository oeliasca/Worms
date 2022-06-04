#pragma once
#include "../Video/ResourceManager.h"
#include "../Video/Video.h"
#include "../Definitions/definition.h"


class UIComponent
{
private:
	Rect pos;
	int id;
	int tipus;
	int rgba[4];
public:
	//To write text
	UIComponent(const char* text,int x,int y,int sizeText);
	//To place a rectangle
	UIComponent(const char* text,int x, int y, int w, int h, int r, int g, int b, int a);
	//To place an img
	UIComponent(const char* filename, int x, int y, int w, int h);

	void setX(int value) { pos.x = value; };
	void setY(int value) { pos.y = value; };
	void setW(int value) { pos.w = value; };
	void setH(int value) { pos.h = value; };
	int getX() { return pos.x; };
	int getY() { return pos.y; };
	int getW() { return pos.w; };
	int getH() { return pos.h; };

	void render();

};

