#pragma once
#include <vector>
class Mapa
{
	int _width;
	int _height;
	int imgT;
	int imgS;

	//ha de ser cantonada up-left
	int _CameraX;
	int _CameraY;
public:
	Mapa(const char* file);
	Mapa(const char* fileBG, int layer);
	~Mapa();


	void render();
	void render(int x, int y);

	int getWidth() { return _width; };
	int getHeight() { return _height; };

	int getIDfromLayer(int PosX, int PosY);

	void setRenderInitX(int value) { _CameraX = value; };
	void setRenderInitY(int value) { _CameraY = value; };
	void reset(const char* file);
	
};

