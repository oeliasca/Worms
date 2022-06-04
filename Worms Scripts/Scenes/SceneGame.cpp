#include "SceneGame.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/Input/Input.h"
#include "../../Engine/Scene/SceneDirector.h"

SceneGame::SceneGame()
{
	
	GM = GameManager::getInstance();
	
	imgSurface= ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png");
	img=ResourceManager::getInstance()->loadAndGetGraphicID("perlinNoiseTest.png");
	MapaBG.clear();
	for (size_t i = 0; i < 7; i++)
	{
		MapaBG.push_back(new Mapa("BackGround", i));
	}
	

	//posar variables pel get torn
	vsIA = true;
	cameraPosX = 0;
	cameraPosY = 0;
	if (vsIA) {
		for (size_t i = 0; i < 4; i++)
		{
			if (i % 2 == 0) {
				Worms.push_back(new Worm());
			}
			else {
				Worms.push_back(new WormEnemy());
			}
			GM->setWorms(Worms.at(i));
		}
		//Diem als enemics qui es player
		dynamic_cast<WormEnemy*>(Worms.at(1))->setPlayerWorms(Worms.at(0));
		dynamic_cast<WormEnemy*>(Worms.at(1))->setPlayerWorms(Worms.at(2));
		dynamic_cast<WormEnemy*>(Worms.at(1))->init();
		dynamic_cast<WormEnemy*>(Worms.at(3))->setPlayerWorms(Worms.at(0));
		dynamic_cast<WormEnemy*>(Worms.at(3))->setPlayerWorms(Worms.at(2));
		dynamic_cast<WormEnemy*>(Worms.at(3))->init();
	}
	GM->init();
	GM->prepareGame();
	ResourceManager::getInstance()->getGraphicSize(img, W, H);
	beginGame = false;
	escaros = false;

	projectil = nullptr;

	playerUIMaxHp = new UIComponent("TeamPlayerHP", 20, 10, HP_BAR_WIDTH, HP_BAR_HEIGHT, 255, 0, 0, 200);
	playerUICurrentHp = new UIComponent("TeamPlayerHP", playerUIMaxHp->getX() + 3, playerUIMaxHp->getY() + 3, 0, HP_BAR_HEIGHT - 6, 0, 0, 0, 255);
	teamPlayerName = new UIComponent(GM->getTeamName(0).c_str(), 50, 30, 40);

	enemyUIMaxHp = new UIComponent("TeamEnemyHP", SCREEN_WIDTH - 20 - HP_BAR_WIDTH, 10, HP_BAR_WIDTH, HP_BAR_HEIGHT, 255, 0, 0, 200);
	enemyUICurrentHp = new UIComponent("TeamEnemyHP", SCREEN_WIDTH - 20 - 3, enemyUIMaxHp->getY() + 3, 0, HP_BAR_HEIGHT - 6, 0, 0, 0, 255);
	teamEnemyName = new UIComponent(GM->getTeamName(1).c_str(), 50, 30, 40);

	windUIMaxValue = new UIComponent("WindValue", (SCREEN_WIDTH/2) - WIND_BAR_WIDTH/2, 20, WIND_BAR_WIDTH, WIND_BAR_HEIGHT, 0, 75, 75, 255);
	windUIMaxValue2 = new UIComponent("WindValue1", (SCREEN_WIDTH / 2) - (WIND_BAR_WIDTH / 2) + 3, windUIMaxValue->getY() + 3, WIND_BAR_WIDTH - 6, WIND_BAR_HEIGHT - 6, 0, 0, 0, 255);
	windUICurrentValue = new UIComponent("WindValue2", (SCREEN_WIDTH / 2) - (WIND_BAR_WIDTH / 2) + 3 + (windUIMaxValue2->getW()/2), windUIMaxValue->getY() + 3, 0, WIND_BAR_HEIGHT - 6, 0, 255, 0, 255);
}

void SceneGame::render()
{
	for (size_t i = 6; i > 0; i--)
	{
		MapaBG.at(i)->render();
	}
	map.render();
	for (size_t i = 0; i < 4; i++)
	{
		if (i % 2 == 0) {
			dynamic_cast<Worm*>(Worms.at(i))->render();
		}
		else {
			dynamic_cast<WormEnemy*>(Worms.at(i))->render();
		}
		if (dynamic_cast<Worm*>(Worms.at(i))->getpWeapon(dynamic_cast<Worm*>(Worms.at(i))->getIndexWeapon())->pProjectile != nullptr) {
			dynamic_cast<Worm*>(Worms.at(i))->getpWeapon(dynamic_cast<Worm*>(Worms.at(i))->getIndexWeapon())->pProjectile->render();
		}
	}
	if (GM->getmDropSize() > 0) {
		for (size_t i = 0; i < GM->getmDropSize(); i++)
		{
			GM->getDropRender(i);
			// falta render, borrar drop al pillar
		}
	}
	playerUIMaxHp->render();
	playerUICurrentHp->render();
	enemyUIMaxHp->render();
	enemyUICurrentHp->render();
	teamPlayerName->render();
	teamEnemyName->render();
	windUIMaxValue->render();
	windUIMaxValue2->render();
	windUICurrentValue->render();
}

void SceneGame::update()
{
	int torn = GM->getTorn();

	playerUICurrentHp->setW(playerUICurrentHp->getW() - 1);
	//comença game
	if (!escaros) {
		escaros = true;
		GM->setWormsTimer();
		playerUICurrentHp->setW(GM->getMaxTeamHP(0)- (GM->getMaxTeamHP(0)*((float)GM->getCurrentTeamHP(0)/(float)GM->getMaxTeamHP(0))));
		enemyUICurrentHp->setW(GM->getMaxTeamHP(1) - (GM->getMaxTeamHP(1) * ((float)GM->getCurrentTeamHP(1) / (float)GM->getMaxTeamHP(1))));
		teamPlayerName->setX(playerUIMaxHp->getX() + ((playerUIMaxHp->getW() / 2) - (teamPlayerName->getW() / 2)));
		teamEnemyName->setX(enemyUIMaxHp->getX() + ((enemyUIMaxHp->getW() / 2) - (teamEnemyName->getW() / 2)));
	}

	if (GM->getmDropSize() > 0) {
		for (size_t i = 0; i < GM->getmDropSize(); i++)
		{
			GM->getDropUpdate(i);
		}
	}

	if (!vsIA) {
		for (size_t i = 0; i < 4; i++)
		{
			dynamic_cast<Worm*>(Worms.at(i))->update();
			dynamic_cast<Worm*>(Worms.at(i))->setXAcceleration(GM->getVent());
		}
		GM->setTeamHealth();
	}
	else {
		
		for (size_t i = 0; i < 4; i++)
		{
			
			if (i % 2 == 0) {
				dynamic_cast<Worm*>(Worms.at(i))->update();
			}
			else {
				dynamic_cast<WormEnemy*>(Worms.at(i))->update();
			}
			dynamic_cast<Worm*>(Worms.at(i))->setXAcceleration(GM->getVent());
		}
		GM->setTeamHealth();
	}

	if (!beginGame) {
		int contador = 0;
		for (size_t i = 0; i < 4; i++)
		{
			if (dynamic_cast<Worm*>(Worms.at(i))->getWormState() == WAITING) {
				contador++;
			}
		}
		if (contador == 4) {
			beginGame = true;
		}
	}
	else {
		int contador = 0;
		for (size_t i = 0; i < 4; i++)
		{
			if (dynamic_cast<Worm*>(Worms.at(i))->getWormState() == WAITING || dynamic_cast<Worm*>(Worms.at(i))->getWormState() == DEATH) {
				contador++;
			}
		}
		if (contador == 4) {
			GM->nextTorn();
			GM->beginPlay();
		}
	}

	if (projectil == nullptr) {
		cameraPosX = dynamic_cast<Worm*>(Worms.at(GM->getWromToFocus()))->getX() - (SCREEN_WIDTH / 2);
		cameraPosY = dynamic_cast<Worm*>(Worms.at(GM->getWromToFocus()))->getY() - (SCREEN_HEIGHT / 2);
	}
	else {
		cameraPosX = projectil->getX() - (SCREEN_WIDTH / 2);
		cameraPosY = projectil->getY() - (SCREEN_HEIGHT / 2);
	}

	GM->checkWormsOutOfScene();

	if (cameraPosX > map.getWidth() - SCREEN_WIDTH) {
		cameraPosX = map.getWidth() - SCREEN_WIDTH;
	}
	if (cameraPosY > map.getHeight() - SCREEN_HEIGHT) {
		cameraPosY = map.getHeight() - SCREEN_HEIGHT;
	}

	if (cameraPosX < 0) {
		cameraPosX = 0;
	}
	if (cameraPosY < 0) {
		cameraPosY = 0;
	}
	map.setRenderInitX(cameraPosX);
	map.setRenderInitY(cameraPosY);
	for (size_t i = 0; i < 7; i++)
	{
		MapaBG.at(i)->setRenderInitX(cameraPosX + ((7 - i) * 10));
		MapaBG.at(i)->setRenderInitY(cameraPosY);
	}

	for (size_t i = 0; i < 4; i++)
	{
		dynamic_cast<Worm*>(Worms.at(i))->setCamX(cameraPosX);
		dynamic_cast<Worm*>(Worms.at(i))->setCamY(cameraPosY);
	}

	if (GM->getmDropSize() > 0) {
		for (size_t i = 0; i < GM->getmDropSize(); i++)
		{
			GM->setDropCamOffX(i, cameraPosX);
			GM->setDropCamOffY(i, cameraPosY);
		}
		GM->checkCollisionWithDrop();
	}
	
	if (!vsIA) {
		if (dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->isProjectileReleased == true) {
			float cAngle;
			float sAngle;
			float Power;
			dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getPowerandAngle(Power, cAngle, sAngle);
			if (projectil == nullptr) {
				if (dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon() == 1) {
					dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->setTransform(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getX(), dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getY());
				}
				projectil = dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->shoot();
				projectil->setCamX(cameraPosX);
				projectil->setCamY(cameraPosY);
				projectil->setxClickIni(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getClickX());
				projectil->setyClickIni(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getClickY());
			}
			projectil->setUpParabolicTrajectory(Power * cAngle, Power * sAngle);
			dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->isProjectileReleased = false;
			projectil->resetPhysicsTimer();
		}
	}
	else {
		if (GM->getTorn() % 2 == 0) {
			if (dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->isProjectileReleased == true) {
				float cAngle;
				float sAngle;
				float Power;
				dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getPowerandAngle(Power, cAngle, sAngle);
				if (projectil == nullptr) {
					if (dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon() == 1) {
						dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->setTransform(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getX(), dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getY());
					}
					projectil = dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->shoot();
					projectil->setCamX(cameraPosX);
					projectil->setCamY(cameraPosY);
					projectil->setxClickIni(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getClickX());
					projectil->setyClickIni(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getClickY());
				}
				projectil->setUpParabolicTrajectory(Power * cAngle, Power * sAngle);
				dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->isProjectileReleased = false;
				projectil->resetPhysicsTimer();
			}
		}
		else {
			if (dynamic_cast<WormEnemy*>(Worms.at(GM->getTorn()))->isProjectileReleased == true) {
				float cAngle;
				float sAngle;
				float Power;
				dynamic_cast<WormEnemy*>(Worms.at(GM->getTorn()))->getPowerandAngle(Power, cAngle, sAngle);
				if (projectil == nullptr) {
					if (dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon() == 1) {
						dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->setTransform(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getX(), dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getY());
					}
					projectil = dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->shoot();
					projectil->setCamX(cameraPosX);
					projectil->setCamY(cameraPosY);
					projectil->setxClickIni(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getClickX());
					projectil->setyClickIni(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getClickY());
				}
				projectil->setUpParabolicTrajectory(Power* cAngle, Power* sAngle);
				dynamic_cast<WormEnemy*>(Worms.at(GM->getTorn()))->isProjectileReleased = false;
				projectil->resetPhysicsTimer();
			}
		}
	}


	if (projectil != nullptr) {
		GM->checkBulletOutOfMap(projectil);
		projectil->setXAcceleration(GM->getVent());
		projectil->setCamX(cameraPosX);
		projectil->setCamY(cameraPosY);
		projectil->update(&Worms, GM->getTorn());
		if (projectil->getRebots() <= 0) {
			//if
			projectil->setDistanceFromObjective(&Worms);
			dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->SetPixel(imgSurface , img, projectil->getX(), projectil->getY(), 0, 0, 0, 0, projectil->getExplosionRange());
			GM->setTeamHealth();
			dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->pProjectile = nullptr;
			delete dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getpWeapon(dynamic_cast<Worm*>(Worms.at(GM->getTorn()))->getIndexWeapon())->pProjectile;
			projectil = nullptr;
		}
	}

	playerUICurrentHp->setW(Utiles.mapValue((GM->getMaxTeamHP(0) - (GM->getMaxTeamHP(0) * ((float)GM->getCurrentTeamHP(0) / (float)GM->getMaxTeamHP(0)))), 0.0f, GM->getMaxTeamHP(0), 0.0f , HP_BAR_WIDTH));
	enemyUICurrentHp->setW((-1) * Utiles.mapValue((GM->getMaxTeamHP(1) - (GM->getMaxTeamHP(1) * ((float)GM->getCurrentTeamHP(1) / (float)GM->getMaxTeamHP(1)))), 0.0f, GM->getMaxTeamHP(1), 0.0f, HP_BAR_WIDTH));
	windUICurrentValue->setW(Utiles.mapValue(GM->getVent(), -25.0f, 25.0f, -65.0f, 65.f));
	
	if (GM->getTeamWinner() != -1) {
		mReinit = true;
		SceneDirector::getInstance()->changeScene(SAVE_LOAD);
	}

}

void SceneGame::reinit()
{
	mReinit = false;
	//GM = GameManager::getInstance();
	map.reset("perlinNoiseTest.png");
	Worms.clear();
	GM->resetWorms();
	imgSurface = ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png");
	img = ResourceManager::getInstance()->loadAndGetGraphicID("perlinNoiseTest.png");
	MapaBG.clear();

	for (size_t i = 0; i < 7; i++)
	{
		MapaBG.push_back(new Mapa("BackGround", i));
	}

	//posar variables pel get torn
	vsIA = true;
	cameraPosX = 0;
	cameraPosY = 0;
	if (vsIA) {
		for (size_t i = 0; i < 4; i++)
		{
			if (i % 2 == 0) {
				Worms.push_back(new Worm());
			}
			else {
				Worms.push_back(new WormEnemy());
			}
			GM->setWorms(Worms.at(i));
		}
		//Diem als enemics qui es player
		dynamic_cast<WormEnemy*>(Worms.at(1))->setPlayerWorms(Worms.at(0));
		dynamic_cast<WormEnemy*>(Worms.at(1))->setPlayerWorms(Worms.at(2));
		dynamic_cast<WormEnemy*>(Worms.at(1))->init();
		dynamic_cast<WormEnemy*>(Worms.at(3))->setPlayerWorms(Worms.at(0));
		dynamic_cast<WormEnemy*>(Worms.at(3))->setPlayerWorms(Worms.at(2));
		dynamic_cast<WormEnemy*>(Worms.at(3))->init();
	}
	GM->init();
	GM->prepareGame();
	ResourceManager::getInstance()->getGraphicSize(img, W, H);
	beginGame = false;
	escaros = false;

	projectil = nullptr;

	playerUIMaxHp = new UIComponent("TeamPlayerHP", 20, 10, HP_BAR_WIDTH, HP_BAR_HEIGHT, 255, 0, 0, 200);
	playerUICurrentHp = new UIComponent("TeamPlayerHP", playerUIMaxHp->getX() + 3, playerUIMaxHp->getY() + 3, 0, HP_BAR_HEIGHT - 6, 0, 0, 0, 255);
	teamPlayerName = new UIComponent(GM->getTeamName(0).c_str(), 50, 30, 40);

	enemyUIMaxHp = new UIComponent("TeamEnemyHP", SCREEN_WIDTH - 20 - HP_BAR_WIDTH, 10, HP_BAR_WIDTH, HP_BAR_HEIGHT, 255, 0, 0, 200);
	enemyUICurrentHp = new UIComponent("TeamEnemyHP", SCREEN_WIDTH - 20 - 3, enemyUIMaxHp->getY() + 3, 0, HP_BAR_HEIGHT - 6, 0, 0, 0, 255);
	teamEnemyName = new UIComponent(GM->getTeamName(1).c_str(), 50, 30, 40);

	windUIMaxValue = new UIComponent("WindValue", (SCREEN_WIDTH / 2) - WIND_BAR_WIDTH / 2, 20, WIND_BAR_WIDTH, WIND_BAR_HEIGHT, 0, 75, 75, 255);
	windUIMaxValue2 = new UIComponent("WindValue1", (SCREEN_WIDTH / 2) - (WIND_BAR_WIDTH / 2) + 3, windUIMaxValue->getY() + 3, WIND_BAR_WIDTH - 6, WIND_BAR_HEIGHT - 6, 0, 0, 0, 255);
	windUICurrentValue = new UIComponent("WindValue2", (SCREEN_WIDTH / 2) - (WIND_BAR_WIDTH / 2) + 3 + (windUIMaxValue2->getW() / 2), windUIMaxValue->getY() + 3, 0, WIND_BAR_HEIGHT - 6, 0, 255, 0, 255);
}
