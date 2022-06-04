#pragma once
#include <vector>
#include "../../Worms Scripts/WormPlayer/WormEnemy.h"
#include "../../Worms Scripts/Drop/Drop.h"
#include "../Timer/Timer.h"
#include "sdl.h"
#include "../../Worms Scripts/WormPlayer/Weapon.h"
#include <string>


struct InfoEquip {
	std::string name[3];
	int vidaActual = 0;
	int vidaMax = 0;
	int punts = 0;
	std::vector <WormPhysics*> Worms;
};

class GameManager
{
	static GameManager* pInstance;
	
public:
	~GameManager();
	static GameManager* getInstance();
	void setWorms(WormPhysics* w) { mWorms.push_back(w); };
	WormPhysics* getWorm(int pos) { return mWorms.at(pos); };
	void init();
	void setWormsTimer();
	int getTorn() { return torn; };
	void nextTorn();
	void beginPlay();
	float getVent() { return vent; };
	void checkWormsOutOfScene();
	void checkBulletOutOfMap(WormPhysics* Projectil);
	void preparePakage();
	int getmDropSize() { return mDrop.size(); };
	void getDropUpdate(int pos);
	void getDropRender(int pos) { mDrop.at(pos)->render(); };
	void setDropCamOffX(int pos, int cameraPosX) { mDrop.at(pos)->setCamX(cameraPosX); };
	void setDropCamOffY(int pos, int cameraPosY) { mDrop.at(pos)->setCamY(cameraPosY); };
	void checkCollisionWithDrop();
	bool checkCollision(int x1, int y1,int w1, int h1, int x2, int y2, int w2, int h2);
	void setTeamScore(int pos, int puntuacio);
	void setTeamHealth();
	void prepareGame();
	int getCurrentTeamHP(int team) { return marcador[team].vidaActual; };
	int getMaxTeamHP(int team) { return marcador[team].vidaMax; };
	int getTeamScore(int team) { return marcador[team].punts; };
	std::string getTeamName(int team) { return marcador[team].name[0]; };
	int getTeamWinner() { return teamWinner; };
	void setTeamWinner(int i) { teamWinner = i; };
	void resetWorms() { mWorms.clear(); }
	int getWromToFocus();
	void setPlayerNames(int i, std::string name);
	void setEnemyNames(int i, std::string name);
	std::string getPlayerName(int i);
	void updateNames();

private:
	GameManager();
	std::vector <InfoEquip> marcador;
	std::string namesPlayer[3];
	std::string namesEnemy[3];
	bool tocaDrop;
	std::vector<Drop*> mDrop;
	std::vector<WormPhysics*> mWorms;
	std::vector<Weapon*> mWeapons;
	float vent;
	int imgbackground;
	int torn;
	int MapWidth;
	int MapHeight;
	int dropPercent;
	int teamWinner;
};

