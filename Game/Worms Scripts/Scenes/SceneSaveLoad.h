#pragma once
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Definitions/definition.h"

class SceneSaveLoad :
    public Scene
{
private:
	std::vector<ScoreInfo> top10;
	void readScores();
	void writeScores();
	bool isDone;
public:
	SceneSaveLoad();
	virtual void render();

	//! Handles the updating of the scene
	virtual void update();

	virtual void reinit();
};

