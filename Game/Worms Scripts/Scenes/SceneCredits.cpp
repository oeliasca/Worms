#include "SceneCredits.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"

SceneCredits::SceneCredits()
{
	img = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/Credits.png");
}

void SceneCredits::render()
{
	int w;
	int h;
	ResourceManager::getInstance()->getGraphicSize(img, w, h);
	Video::getInstance()->renderGraphic(img, 0, 0, w, h);
}

void SceneCredits::update()
{
	if (Input::getInstance()->getKeyboard()->RETURN) {
		Input::getInstance()->getKeyboard()->RETURN = false;
		SceneDirector::getInstance()->changeScene(MAIN);
	}
}

void SceneCredits::reinit()
{
	mReinit = true;
}
