#include "Drop.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/Video/ResourceManager.h"

Drop::Drop(int id)
{
	ID = id;
	radius = 16;
	switch (ID)
	{
	case -1:
		Quantity = 75;
		break;
	case 0:
		Quantity = 1;
		break;
	case 1:
		Quantity = 1;
		break;
	case 2:
		Quantity = 1;
		break;
	case 3:
		Quantity = 1;
		break;
	default:
		break;
	}
	Img = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/Atac_Aeri.png");
	Imgs = ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("Assets/img/Atac_Aeri.png");
	state = APPEAR;
	rebots = 0;
	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/Atac_Aeri.png"), Transform.w, Transform.h);
}

void Drop::update()
{
	switch (state)
	{
	case APPEAR:
		temps.refreshTimer();
		state = DROP;
		break;
	case DROP:
		translatePhysicsObjects();
		if (stable) {
			state = LANDED;
		}
		break;
	case LANDED:
		translatePhysicsObjects();
		if (!stable) {
			state = DROP;
		}
		break;
	default:
		break;
	}
}

void Drop::render()
{
	Video::getInstance()->renderGraphic(Img, Transform.x - camOfX, Transform.y - camOfY, Transform.w, Transform.h);
}
