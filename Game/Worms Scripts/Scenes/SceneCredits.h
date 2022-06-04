#pragma once
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Input/Input.h"
#include "../../Engine/Scene/SceneDirector.h"
class SceneCredits :
    public Scene
{
public:
	SceneCredits();
	virtual void render();

	//! Handles the updating of the scene
	virtual void update();

	virtual void reinit();
};

