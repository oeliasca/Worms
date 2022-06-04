#include "GameManager.h"
#include "../Video/ResourceManager.h"
#include <stdlib.h>
#include <time.h> 

GameManager* GameManager::pInstance = NULL;


GameManager::~GameManager()
{
}

int GameManager::getWromToFocus()
{

	if (dynamic_cast<Worm*>(mWorms.at(torn))->getWormState() != WAITING && dynamic_cast<Worm*>(mWorms.at(torn))->getWormState() != DEATH) {
		return torn;
	}
	else {
		for (int i = 0; i < mWorms.size(); i++)
		{
			if (dynamic_cast<Worm*>(mWorms.at(i))->getWormState() == HIT || dynamic_cast<Worm*>(mWorms.at(i))->getWormState() == LANDINGHIT) {
				return i;
			}
		}
	}
	return torn;

}

void GameManager::setPlayerNames(int i, std::string name)
{
	namesPlayer[i] = name;
}

void GameManager::setEnemyNames(int i, std::string name)
{
	namesEnemy[i] = name;
}

std::string GameManager::getPlayerName(int i)
{
	return marcador[0].name[i];
}

void GameManager::updateNames()
{
	marcador[0].name[0] = namesPlayer[0];
	marcador[1].name[0] = namesEnemy[0];
	marcador[0].name[1] = namesPlayer[1];
	marcador[1].name[1] = namesEnemy[1];
	marcador[0].name[2] = namesPlayer[2];
	marcador[1].name[2] = namesEnemy[2];
}

GameManager::GameManager()
{
	dropPercent = 100;
	torn = 0;
	vent = 0;
	teamWinner = -1;
	namesPlayer[0] = "Player";
	namesPlayer[1] = "P1";
	namesPlayer[2] = "P2";
	namesEnemy[0] = "Enemy";
	namesEnemy[1] = "E1";
	namesEnemy[2] = "E2";
}

GameManager* GameManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new GameManager();
	}
	return pInstance;
}

void GameManager::init()
{
	teamWinner = -1;
	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("perlinNoiseTest.png"), MapWidth, MapHeight);

	imgbackground = ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png");
	

	std::vector<Vec2> posinit;
	posinit.resize(4);
	int x = 450;
	for (size_t i = 0; i < 4; i++)
	{
		posinit.at(i).X = x;
		x += 100;
	}
	
	
	Uint8* pixelArray = ResourceManager::getInstance()->getArrayPixels(imgbackground);
	int h = ResourceManager::getInstance()->getSurfaceH(imgbackground);
	int pitch = ResourceManager::getInstance()->getSurfacePitch(imgbackground);
	int bytesPerPixel = ResourceManager::getInstance()->getSurfaceBytesPerPixel(imgbackground);
	for (size_t x = 0; x < 4; x++)
	{
		for (size_t y = 0; y < h; y++)// mirem y
		{
			if (pixelArray[y * pitch + posinit.at(x).X * bytesPerPixel + 3] != 0) {
				posinit.at(x).Y = y - mWorms.at(x)->getHeight();
				break;
			}
		}
	}
	
	

	for (size_t i = 0; i < 4; i++)
	{
		mWorms.at(i)->setTransform(posinit.at(i).X, posinit.at(i).Y);
	}

}

void GameManager::setWormsTimer()
{
	for (size_t i = 0; i < 4; i++)
	{
		dynamic_cast<Worm*>(mWorms.at(i))->resetPhysicsTimer();
	}
}

void GameManager::nextTorn()
{
	vent = rand() % 51 - 25;
	bool isDeath = true;
	int counterAlldeath = 0;
	while (isDeath && (counterAlldeath< (mWorms.size() - 1))) {
		torn++;
		if (torn > (mWorms.size() - 1)) {
			torn = 0;
		}
		if (dynamic_cast<Worm*>(mWorms.at(torn))->getWormState() == DEATH) {
			counterAlldeath++;
		}
		else {
			isDeath = false;
		}
	}

	if (rand() % 101 < 20) {
		tocaDrop = true;

	}
	else {
		tocaDrop = false;
	}
	preparePakage();
	
}

void GameManager::beginPlay()
{
	dynamic_cast<Worm*>(mWorms.at(torn))->setWormState(IDLE);
	dynamic_cast<Worm*>(mWorms.at(torn))->renderSignal();
	dynamic_cast<Worm*>(mWorms.at(torn))->playSound(3);
}

void GameManager::checkWormsOutOfScene()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (mWorms.at(i)->getX() > MapWidth ||
			mWorms.at(i)->getX() + mWorms.at(i)->getWidth() < 0 ||
			mWorms.at(i)->getY() > MapHeight)
		{
			dynamic_cast<Worm*>(mWorms.at(i))->setWormState(DEATH);
		}
	}
}

void GameManager::checkBulletOutOfMap(WormPhysics* Projectil)
{
	if (Projectil->getX() > MapWidth ||
		Projectil->getX() + Projectil->getWidth() < 0 ||
		Projectil->getY() > MapHeight)
	{
		Projectil->setRebots(0);
	}
}

void GameManager::preparePakage()
{
	if (tocaDrop) {
		tocaDrop = false;
		mDrop.push_back(new Drop(rand() % 2 - 1));
		mDrop.at(mDrop.size() - 1)->setTransform(rand() % MapWidth - mDrop.at(mDrop.size() - 1)->getWidth(), 0);
	}
}

void GameManager::getDropUpdate(int pos)
{
	mDrop.at(pos)->update();
	if (mDrop.at(pos)->getX() > MapWidth ||
		mDrop.at(pos)->getX() + mDrop.at(pos)->getWidth() < 0 ||
		mDrop.at(pos)->getY() > MapHeight)
	{
		mDrop.erase(mDrop.begin() + pos);
	}
}

void GameManager::checkCollisionWithDrop()
{
	if (mDrop.size() > 0) {
		for (size_t i = 0; i < mDrop.size(); i++)
		{
			for (size_t x = 0; x < mWorms.size(); x++) {
				if (checkCollision(mDrop[i]->getX(), mDrop[i]->getY(), mDrop[i]->getWidth(), mDrop[i]->getHeight(),
					mWorms[x]->getX(), mWorms[x]->getY(), mWorms[x]->getWidth(), mWorms[x]->getHeight())) {
					if (mDrop[i]->getDropID() == -1) {
						dynamic_cast<Worm*>(mWorms[x])->setHealth(mDrop[i]->getDropQuantity());
					}
					else {
						dynamic_cast<Worm*>(mWorms[x])->getpWeapon(mDrop[i]->getDropID())->Ammo += mDrop[i]->getDropQuantity();
					}
					mDrop.erase(mDrop.begin() + i);
					break;
				}
			}
		}
	}
}

bool GameManager::checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if ((((x2 < x1) && (x1 < x2 + w2))
		&&
		((y2 < y1) && (y1 < y2 + h2)))
		||
		(((x2 < x1 + w1) && (x1 + w1 < x2 + w2))
		&&
		((y2 < y1) && (y1 < y2 + h2)))
		||
		(((x2 < x1) && (x1 < x2 + w2))
		&&
		((y2 < y1 + h1) && (y1 + h1 < y2 + h2)))
		||
		(((x2 < x1 + w1) && (x1 + w1 < x2 + w2))
		&&
		((y2 < y1 + h1) && (y1 + h1 < y2 + h2))))
	{
		return true;
	}
	return false;
}

void GameManager::prepareGame()
{
	teamWinner = -1;
	marcador.clear();
	for (size_t i = 0; i < mWorms.size()/2; i++)
	{
		InfoEquip a;
		marcador.push_back(a);
	}

	updateNames();

	for (size_t i = 0; i < mWorms.size(); i++)
	{
		if (i % 2 == 0) {//worm
			marcador[0].vidaActual += dynamic_cast<Worm*>(mWorms.at(i))->getHealth();
			marcador[0].Worms.push_back(mWorms[i]);
		}
		else {//enemy
			marcador[1].vidaActual += dynamic_cast<Worm*>(mWorms.at(i))->getHealth();
			marcador[1].Worms.push_back(mWorms[i]);
		}
	}
	marcador[0].vidaMax = marcador[0].vidaActual;
	marcador[1].vidaMax = marcador[1].vidaActual;
	
	dynamic_cast<Worm*>(marcador[0].Worms.at(0))->setWormName(marcador[0].name[1].c_str());
	dynamic_cast<Worm*>(marcador[0].Worms.at(1))->setWormName(marcador[0].name[2].c_str());
	dynamic_cast<Worm*>(marcador[1].Worms.at(0))->setWormName(marcador[1].name[1].c_str());
	dynamic_cast<Worm*>(marcador[1].Worms.at(1))->setWormName(marcador[1].name[2].c_str());
}

void GameManager::setTeamScore(int pos, int puntuacio) {
	marcador[pos].punts += puntuacio;
}

void GameManager::setTeamHealth() {
	for (size_t i = 0; i < marcador.size(); i++)
	{
		marcador[i].vidaActual = dynamic_cast<Worm*>(marcador[i].Worms[0])->getHealth() + dynamic_cast<Worm*>(marcador[i].Worms[1])->getHealth();
		
		if (marcador[i].vidaActual <= 0) {
			marcador[i].vidaActual = 0;
			if (i == 0) {
				teamWinner = 1;
			}
			else {
				teamWinner = 0;
			}
		}
	}
}