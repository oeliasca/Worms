#include "UIComponent.h"
#include "../Text/ScreenText.h"
UIComponent::UIComponent(const char* text, int x, int y, int sizeText)
{
	ScreenText::getInstance()->drawText(text,text,sizeText, 255, 255, 100, 0, 0, 0);
	pos.x = x;
	pos.y = y;
	id = ResourceManager::getInstance()->loadAndGetGraphicID(text);
	ResourceManager::getInstance()->getGraphicSize(id, pos.w, pos.h);
	tipus = 0;
}

UIComponent::UIComponent(const char* text, int x, int y, int w, int h, int r, int g, int b, int a)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	tipus = 1;
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}

UIComponent::UIComponent(const char* filename, int x, int y, int w, int h)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	tipus = 2;
	id = ResourceManager::getInstance()->loadAndGetGraphicID(filename);
}

void UIComponent::render()
{
	switch (tipus)
	{
	case 0:
		Video::getInstance()->renderGraphic(id,pos.x,pos.y,pos.w,pos.h);
		break;
	case 1:
		Video::getInstance()->renderRect(pos.x, pos.y, pos.w, pos.h, rgba[0], rgba[1], rgba[2], rgba[3]);
		break;
	case 2:
		Video::getInstance()->renderGraphic(id, pos.x, pos.y, pos.w, pos.h);
		break;
	default:
		break;
	}
}
