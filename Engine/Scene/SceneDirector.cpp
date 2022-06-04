#include "SceneDirector.h"


//#include "SceneSaveLoad.h"
//#include "SceneGame.h"





SceneDirector* SceneDirector::pInstance = NULL;

SceneDirector* SceneDirector::getInstance(){
	if (!pInstance) {
		pInstance = new SceneDirector();
	}
	return pInstance;
}

SceneDirector::SceneDirector(){
	init();
}

SceneDirector::~SceneDirector(){
}

void SceneDirector::init(){
	mVectorScenes.resize(NUM_SCENES);

	SceneMain*       main      = new SceneMain();
	SceneCredits*    credits   = new SceneCredits();
	SceneRanking*    ranking   = new SceneRanking();
	SceneTeamEntry*  teamEntry = new SceneTeamEntry();
	SceneGame*       game      = new SceneGame();
	SceneSaveLoad* saveload = new SceneSaveLoad();

	mVectorScenes[MAIN]      = main;
	mVectorScenes[GAME]      = game;
	mVectorScenes[RANKING]   = ranking;
	mVectorScenes[TEAMENTRY] = teamEntry;
	mVectorScenes[CREDITS]   = credits;
	mVectorScenes[SAVE_LOAD] = saveload;

	main->init();//Main menu
	game->init();
	ranking->init();
	teamEntry->init();
	credits->init();
	saveload->init();
	

	mCurrScene = MAIN;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit){
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}
