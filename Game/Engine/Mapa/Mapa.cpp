#include "Mapa.h"
#include "../Video/ResourceManager.h"
#include "../Video/Video.h"
#include "Perlin.h"
Mapa::Mapa(const char* file)
{
	int w = 2048;
	int seed = rand() % 512;
	int octaves = 8;
	Perlin* p = new Perlin(seed,w,octaves);
	p->generatePerlinNoise1D(w);
	float* noise = p->getPerlinNoise1D();
	int maxValue = 300;
	
	
	for (int i = 0; i < w; i++) {
		noise[i] = noise[i] * maxValue;
	}

	imgS = ResourceManager::getInstance()->createSurfaceFromPixels(file, noise, maxValue, w, 720);
	imgT = ResourceManager::getInstance()->createTextureFromPixels(file);

	_width=0;
	_height=0;
	ResourceManager::getInstance()->getGraphicSize(imgT,_width,_height);

	_CameraX=0;
	_CameraY=0;
}

Mapa::Mapa(const char* fileBG, int layer)
{
	std::string aux = "Assets/";
	aux.append(fileBG);
	aux.append(std::to_string(layer));
	aux.append(".png");
	imgT = ResourceManager::getInstance()->loadAndGetGraphicID(aux.c_str());
	ResourceManager::getInstance()->getGraphicSize(imgT, _width, _height);
	
	_CameraX = 0;
	_CameraY = 0;
}

Mapa::~Mapa()
{
}


void Mapa::render()
{
	int xS = _CameraX;
	int yS = _CameraY;
	int wS = SCREEN_WIDTH;
	int hS = SCREEN_HEIGHT;
	int xT = 0;
	int yT = 0;
	int wT = SCREEN_WIDTH;
	int hT = SCREEN_HEIGHT;
	
	Video::getInstance()->renderGraphic(imgT,xS,yS,wS,hS,xT,yT,wT,hT);
}

void Mapa::render(int x, int y)
{
	Video::getInstance()->renderGraphic(imgT, 0, 0, _width, _height);
}

int Mapa::getIDfromLayer(int PosX, int PosY)
{
	return 0;
}

void Mapa::reset(const char* file)
{
	int w = 2048;
	int seed = rand() % 512;
	int octaves = 8;
	Perlin* p = new Perlin(seed, w, octaves);
	p->generatePerlinNoise1D(w);
	float* noise = p->getPerlinNoise1D();
	int maxValue = 300;


	for (int i = 0; i < w; i++) {
		noise[i] = noise[i] * maxValue;
	}

	ResourceManager::getInstance()->resetSurfaceFromPixels(file, noise, maxValue, w, 720);
	

	_width = 0;
	_height = 0;
	ResourceManager::getInstance()->getGraphicSize(imgT, _width, _height);

	_CameraX = 0;
	_CameraY = 0;
}
