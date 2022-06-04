#include "Video.h"
#include "ResourceManager.h"

Video* Video::pInstance = NULL;
Video::Video()
{
	lastTime = 0;
	currentTime = 0;
	deltaTime = 0;
	msFrame = 1 / (FPS / 1000.0f);

	gWindow = NULL;
	
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);// SDL_WINDOW_FULLSCREEN
	gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

Video::~Video()
{
}

Video* Video::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Video();
	}
	return pInstance;
}

void Video::renderRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(gScreen, r, g, b, a);
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	SDL_SetRenderDrawBlendMode(gScreen, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(gScreen, &rectangle);
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height)
{
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	rectAux.h = height;
	rectAux.w = width;
	rectAux.x = 0;
	rectAux.y = 0;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopy(gScreen,origin,&rectAux,&r);
	
}

void Video::renderGraphic(int img, int posXS, int posYS, int wS, int hS, int posXT, int posYT, int wT, int hT)
{
	SDL_Rect r, rectAux;
	r.x = posXT;
	r.y = posYT;
	r.w = wT;
	r.h = hT;
	rectAux.h = hS;
	rectAux.w = wS;
	rectAux.x = posXS;
	rectAux.y = posYS;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopy(gScreen, origin, &rectAux, &r);
}

void Video::renderText(int img, int posX, int posY, int width, int height)
{
	SDL_Rect r;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopy(gScreen, origin, NULL, &r);
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height, double angle, Vec2 pivot, Flip flip)
{
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	rectAux.h = height;
	rectAux.w = width;
	rectAux.x = 0;
	rectAux.y = 0;
	SDL_Point auxpivot;
	auxpivot.x = pivot.X;
	auxpivot.y = pivot.Y;
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RendererFlip auxFlip = (SDL_RendererFlip)flip;
	SDL_RenderCopyEx(gScreen, origin, &rectAux, &r,angle, &auxpivot, auxFlip);
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height, Rect &sRect, double angle, Vec2* pivot, Flip flip)
{
	SDL_Rect r, rectAux;
	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;
	rectAux.h = sRect.h;
	rectAux.w = sRect.w;
	rectAux.x = sRect.x;
	rectAux.y = sRect.y;
	SDL_Point auxpivot;
	if (pivot!=nullptr) {
		auxpivot.x = pivot->X;
		auxpivot.y = pivot->Y;
	}
	
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RendererFlip auxFlip = (SDL_RendererFlip)flip;
	SDL_RenderCopyEx(gScreen, origin, &rectAux, &r, angle, &auxpivot, auxFlip);
}

void Video::clearScreen(unsigned int color_key)
{
	SDL_SetRenderDrawColor(gScreen, 0, 0, 0, 0);
	SDL_RenderClear(gScreen);
	
}

void Video::updateScreen()
{
	SDL_RenderPresent(gScreen);
}

void Video::waitTime(int ms)
{
	SDL_Delay(ms);
}

void Video::close()
{
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

void Video::vSync()
{
	currentTime = SDL_GetTicks();
	deltaTime = currentTime - lastTime;
	if (deltaTime < (unsigned int)msFrame)
	{
		waitTime((int)msFrame - deltaTime);
	}
	lastTime = currentTime;
}
