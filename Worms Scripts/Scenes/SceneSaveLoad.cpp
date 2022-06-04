#include "SceneSaveLoad.h"
#include "../../Engine/ReadWrite/ReadWrite.h"
#include "../../Engine/GameManager/GameManager.h"
#include "../../Engine/Scene/SceneDirector.h"


bool compareScore(const ScoreInfo& a, const ScoreInfo& b) {

	return a.punctuation > b.punctuation;
}

void sortList(std::vector<ScoreInfo>& _toOrder) {
	std::sort(_toOrder.begin(), _toOrder.end(), compareScore);
}


void SceneSaveLoad::readScores()
{
	ReadWrite::getInstance()->readBinary("Scores.bin");
	top10 = ReadWrite::getInstance()->getLadder();
}

void SceneSaveLoad::writeScores()
{
	ReadWrite::getInstance()->initWrite("Scores.bin");
	ReadWrite::getInstance()->writeBinary(top10);
}

SceneSaveLoad::SceneSaveLoad()
{
	//isDone = false;
}

void SceneSaveLoad::render()
{
}

void SceneSaveLoad::update()
{
	if (!isDone) {
		readScores();

		//---Mirar si s'ha d'actualitzar top10
		if (top10.size() < 10) {
			ScoreInfo aux;
			aux.punctuation = GameManager::getInstance()->getTeamScore(GameManager::getInstance()->getTeamWinner());
			aux.teamName= GameManager::getInstance()->getTeamName(GameManager::getInstance()->getTeamWinner());

			std::cout << "Team name: " << aux.teamName << " Puntuacio: " << aux.punctuation << std::endl;

			top10.push_back(aux);

			//Ordenar el top10
			sortList(top10);

			writeScores();
		}
		else {
			ScoreInfo aux;
			aux.punctuation = GameManager::getInstance()->getTeamScore(GameManager::getInstance()->getTeamWinner());
			aux.teamName = GameManager::getInstance()->getTeamName(GameManager::getInstance()->getTeamWinner());
			top10.push_back(aux);
			std::cout << "Team name: " << aux.teamName << " Puntuacio: " << aux.punctuation << std::endl;
			//Ordenar el top10
			sortList(top10);
			top10.pop_back();
			writeScores();
		}



		//Anar a MAIN
		isDone = true;
		SceneDirector::getInstance()->changeScene(MAIN);
	}
}

void SceneSaveLoad::reinit()
{
	isDone = false;
}

