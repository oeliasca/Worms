#include "SceneRanking.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/ReadWrite/ReadWrite.h"


SceneRanking::SceneRanking()
{
	
	
}

void SceneRanking::render()
{


	

	for (int i = 0; i < Ranking.size(); i++)
	{
		Ranking[i].render();
	}

}

void SceneRanking::update()
{

	//RectsDeEscena.x = 362;
	//RectsDeEscena.y = 372;
	//RectsDeEscena.w = 465-362;
	//RectsDeEscena.h = 393-372;

	for (int i = 0; i < Ranking.size(); i++)
	{
		Ranking[i].setX(200);
		Ranking[i].setY(50 + i * Ranking[i].getH());
		
	}


	if (Input::getInstance()->getKeyboard()->RETURN) {
		Input::getInstance()->getKeyboard()->RETURN = false;
		SceneDirector::getInstance()->changeScene(MAIN);
	}
}

void SceneRanking::reinit()
{
	mReinit = true;
	top10.clear();
	top10.resize(0);
	Ranking.clear();
	//Ranking.resize(0);
	ReadWrite::getInstance()->readBinary("Scores.bin");
	top10 = ReadWrite::getInstance()->getLadder();

	for (int i = 0; i < top10.size(); i++)
	{
		std::string aux;
		aux.append(std::to_string(i + 1));
		aux.append(". ");
		aux.append(top10[i].teamName);
		aux.append(":  ");
		aux.append(std::to_string(top10[i].punctuation));
		UIComponent newComp = UIComponent(aux.c_str(),0,0,40);
		Ranking.push_back(newComp);
	}

}
