#include "ScreenText.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include <Windows.h>
#include <stdio.h>

ScreenText* ScreenText::pInstance = NULL;

ScreenText* ScreenText::getInstance()
{
	if (pInstance == NULL) {
		pInstance = new ScreenText();
	}
	return pInstance;
}

void ScreenText::drawText(std::string String, std::string ID, int size, int fR, int fG, int fB, int bR, int bG, int bB)
{
	TTF_Font* font = TTF_OpenFont("Assets/ttf/Cute Cartoon.ttf", size);
	SDL_Color foregroundColor = { fR,fG,fB };
	SDL_Color backgroundColor = { bR,bG,bB };

	SDL_Surface* textSurface;// = TTF_RenderText_Shaded(font, string, foregroundColor, backgroundColor);
	if (!(textSurface = TTF_RenderText_Solid(font, String.c_str(), foregroundColor))) {
		//handle error here, perhaps print TTF_GetError at least
		printf(TTF_GetError());
	}
	else {
	


		//SDL_Texture* ObjectTexture = SDL_CreateTexture(Video::getInstance()->gScreen, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, textSurface->w, textSurface->h);
		//SDL_SetTextureBlendMode(ObjectTexture, SDL_BLENDMODE_BLEND);
		//ResourceManager::getInstance()->loadTextureID(ObjectTexture, string);
		
		SDL_Texture* temp = SDL_CreateTextureFromSurface(Video::getInstance()->gScreen, textSurface);

		ResourceManager::getInstance()->loadAndGetGraphicTextID(ID, temp);
		
		SDL_FreeSurface(textSurface);
	}
	
	TTF_CloseFont(font);
}

ScreenText::~ScreenText()
{
	ScreenTextQuit();
}

ScreenText::ScreenText()
{
	TTF_Init();
}
