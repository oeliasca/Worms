#pragma once
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Input/Input.h"
#include "../../Engine/Scene/SceneDirector.h"


class SceneRanking :
    public Scene
{
public:
	SceneRanking();
	virtual void render();

	//! Handles the updating of the scene
	virtual void update();

	virtual void reinit();

	Rect* getRectsDeEscena() { return &RectsDeEscena; };
private:
	Rect RectsDeEscena;
	bool Hovered;
	std::vector<ScoreInfo> top10;
	std::vector<UIComponent> Ranking;
};

