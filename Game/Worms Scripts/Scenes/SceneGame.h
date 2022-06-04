#pragma once
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Physics/Projectile.h"
//--
#include <vector>
//--
#include "../../Engine/GameManager/GameManager.h"
#include "../../Engine/Mapa/Mapa.h"



class SceneGame :
    public Scene
{
public:
	SceneGame();
	virtual void render();

	//! Handles the updating of the scene
	virtual void update();

	virtual void reinit();
private:
	int imgSurface;
	std::vector <Mapa*> MapaBG;
	std::vector<WormPhysics*> Worms;
	Mapa map = Mapa("perlinNoiseTest.png");
	int W, H;
	bool vsIA;
	bool beginGame;
	//--
	GameManager* GM;
	Projectile* projectil;
	//--
	Timer tempsdejoc;
	bool escaros;
	//--
	int cameraPosX;
	int cameraPosY;
	//--
	UIComponent* playerUICurrentHp;
	UIComponent* playerUIMaxHp;
	UIComponent* teamPlayerName;

	UIComponent* enemyUICurrentHp;
	UIComponent* enemyUIMaxHp;
	UIComponent* teamEnemyName;

	UIComponent* windUICurrentValue;
	UIComponent* windUIMaxValue;
	UIComponent* windUIMaxValue2;

};

