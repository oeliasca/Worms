#include "Projectile.h"
#include "../Input/Input.h"
#include "../Video/Video.h"
#include "../../Worms Scripts/WormPlayer/WormEnemy.h"
#include <math.h>   
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../GameManager/GameManager.h"
#include "../Audio/SoundManager.h"


Projectile::Projectile(int id)
{
	isClicked = false;
	//Transform.x = 10;
	//Transform.y = 10;
	Img = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/bala1.png");
	SoundsEffects[0] = -1;
	switch (id)
	{
	case 0:
		//missil
		ID = id;
		TimePressed = 0;
		ResourceManager::getInstance()->getGraphicSize(Img,Transform.w, Transform.h);
		//Transform.w = 58;
		//Transform.h = 60;
		TransformCollision.w = Transform.w;
		TransformCollision.h = Transform.h;
		explosionRange = 75;
		rebots = 1;
		friction = 0.9;
		Damage = 35;
		SoundsEffects[0] = SoundManager::getInstance()->loadAndGetSoundID("Assets/Sounds/explosio.ogg");
		//g = 30;
		break;
	case 1:
		//rifle
		ID = id;
		TimePressed = 0;
		ResourceManager::getInstance()->getGraphicSize(Img, Transform.w, Transform.h);
		TransformCollision.w = Transform.w;
		TransformCollision.h = Transform.h;
		explosionRange = 5;
		rebots = 1;
		friction = 0.9;
		Damage = 60;
		break;
	case 2:
		//granada
		ID = id;
		TimePressed = 0;
		ResourceManager::getInstance()->getGraphicSize(Img, Transform.w, Transform.h);
		TransformCollision.w = Transform.w;
		TransformCollision.h = Transform.h;
		explosionRange = 100;
		rebots = 3;
		friction = 0.9;
		Damage = 70;
		break;
	case 3:
		//atac aeri
		ID = id;
		TimePressed = 0;
		ResourceManager::getInstance()->getGraphicSize(Img, Transform.w, Transform.h);
		TransformCollision.w = Transform.w;
		TransformCollision.h = Transform.h;
		explosionRange = 100;
		rebots = 1;
		friction = 0.9;
		Damage = 33;
		break;
	default:
		break;
	}
}

void Projectile::update(std::vector<WormPhysics*>* Wroms, int torn)
{
	switch (ID)
	{
	case 0:
		WormPhysics::translatePhysicsObjects();
		WormPhysics::checkWormCollision(Wroms);
		break;
	case 1:
		int index = WormPhysics::rayCast(Transform.x + (Wroms->at(torn)->getWidth() / 2), Transform.y + (Wroms->at(torn)->getHeight() / 2), xClickIni + camOfX, yClickIni + camOfY, Wroms, explosionRange, torn);
		if (index != -1) {
			if (torn % 2 == 0) {
				if (index % 2 == 0) {
					dynamic_cast<Worm*>(Wroms->at(index))->setWormState(HIT);
				}
				else {
					dynamic_cast<WormEnemy*>(Wroms->at(index))->setWormState(HIT);
					GameManager::getInstance()->setTeamScore(torn % 2, Damage);
				}
			}
			else {
				if (index % 2 != 0) {
					dynamic_cast<WormEnemy*>(Wroms->at(index))->setWormState(HIT);
				}
				else {
					dynamic_cast<Worm*>(Wroms->at(index))->setWormState(HIT);
					GameManager::getInstance()->setTeamScore(torn % 2, Damage);
				}
			}
			dynamic_cast<Worm*>(Wroms->at(index))->setHealth(Damage);
		}
		break;
	}
}

void Projectile::render()
{
	switch (ID)
	{
	case 0:
		Video::getInstance()->renderGraphic(Img, Transform.x - camOfX, Transform.y - camOfY, Transform.w, Transform.h);
		break;
	case 1:
		//WormPhysics::rayCast(Transform.x + Transform.w / 2, Transform.y + Transform.h / 2, xClickIni + camOfX, yClickIni + camOfY, Wroms, explosionRange);
		break;
	case 2:
		//WormPhysics::rayCast(Transform.x + Transform.w / 2, Transform.y + Transform.h / 2, xClickIni + camOfX, yClickIni + camOfY, Wroms, explosionRange);
		break;
	case 3:
		//si no he clickat {
		//moure porjectile"indicador" segons input mouse
		// }
		//else he clickat{
		//fer apareixer porjects mb ID = 0
		//for i = 0 / i < apareixerporjects.siz() bla bla
		//update
		//}
		break;
	}
}

void Projectile::setPower(int p, float angle)
{
	WormPhysics::setUpParabolicTrajectory(p * cosf(angle), p * sinf(angle));
}

void Projectile::setDistanceFromObjective(std::vector<WormPhysics*> *Wroms)
{
	float DistX = 0;
	float DistY = 0;
	float Dist = 0;
	float posX;
	float posY;
	for (size_t i = 0; i < Wroms->size(); i++)
	{
		posX = Wroms->at(i)->getX() + (Wroms->at(i)->getWidth()/2);
		posY= Wroms->at(i)->getY() + (Wroms->at(i)->getHeight()/2);
		DistX = posX - (Transform.x + Transform.w / 2);
		DistY = posY - (Transform.y + Transform.h / 2);
		Dist = sqrt((DistX * DistX) + (DistY* DistY));

		if((abs(Wroms->at(i)->getX() - (Transform.x + Transform.w / 2)) < explosionRange
			||
			abs((Wroms->at(i)->getX()+ Wroms->at(i)->getWidth()) - (Transform.x + Transform.w / 2)) < explosionRange)
			&&
			(abs(Wroms->at(i)->getY() - (Transform.y + Transform.h / 2)) < explosionRange
			||
			abs((Wroms->at(i)->getY() + Wroms->at(i)->getHeight()) - (Transform.y + Transform.h / 2)) < explosionRange))
		{
			cosAngle = (-(Transform.x + (Transform.w / 2)) + posX) / Dist;
			sinAngle = (-(Transform.y + (Transform.h / 2)) + posY) / Dist;
			if (Dist > explosionRange) {
				Dist = explosionRange - 5.0f;
			}
			
			dynamic_cast<Worm*>(Wroms->at(i))->setHealth((int)(Damage *(1.01f-(Dist/explosionRange))));
			if (GameManager::getInstance()->getTorn() % 2 == 0 && i % 2 != 0) {
				GameManager::getInstance()->setTeamScore(GameManager::getInstance()->getTorn() % 2, (int)(Damage * (1.00f - (Dist / explosionRange))));
			}
			else if (GameManager::getInstance()->getTorn() % 2 != 0 && i % 2 == 0) {
				GameManager::getInstance()->setTeamScore(GameManager::getInstance()->getTorn() % 2, (int)(Damage * (1.00f - (Dist / explosionRange))));
			}
			if (i % 2 == 0) {
				dynamic_cast<Worm*>(Wroms->at(i))->setWormState(HIT);
			}
			else {
				dynamic_cast<WormEnemy*>(Wroms->at(i))->setWormState(HIT);
			}
			Wroms->at(i)->setUpParabolicTrajectory(cosAngle * 25, sinAngle * 25);

			dynamic_cast<Worm*>(Wroms->at(i))->playSound(2);
		}
	}
	if (SoundsEffects[0] != -1) {
		SoundManager::getInstance()->PlaySound(SoundsEffects[0], -1, 0);
	}
}

Projectile::~Projectile()
{

}
