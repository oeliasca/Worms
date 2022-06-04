#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "../../Worms Scripts/Scenes/SceneMain.h"
#include "../../Worms Scripts/Scenes/SceneCredits.h"
#include "../../Worms Scripts/Scenes/SceneRanking.h"
#include "../../Worms Scripts/Scenes/SceneTeamEntry.h"
#include "../../Worms Scripts/Scenes/SceneGame.h"
#include "../../Worms Scripts/Scenes/SceneSaveLoad.h"

#include <vector>
#include "Scene.h"

/*
		0->Main Menu
		1->Play Game
		2->Team Entry
		3->Ranking
		4->Credits
		5->SaveLoad
		*/

//! Enum Scenes.
/*! All the Scenes in the game. */
enum SceneEnum {
		MAIN, GAME, TEAMENTRY, RANKING, CREDITS, EXIT, SAVE_LOAD,
		_LASTSCENE};

#define NUM_SCENES _LASTSCENE

class SceneDirector
{
	public:
		~SceneDirector();

		void init();
		
		void changeScene(SceneEnum next_scene, bool reinit = true);

		SceneEnum getCurrSceneEnum(){return mCurrScene;};

		Scene* getCurrentScene(){return mVectorScenes[mCurrScene];};
		
		//! Gets pointer to instance
		static SceneDirector* getInstance();

	protected:
		SceneDirector();
		static SceneDirector*	pInstance;	/*!<  pointer instance*/

		std::vector<Scene*>	mVectorScenes;
		SceneEnum		mCurrScene;
};

#endif
