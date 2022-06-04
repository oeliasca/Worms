#include "SceneTeamEntry.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/Text/ScreenText.h"

SceneTeamEntry::SceneTeamEntry()
{

	for (int i = 0; i < 8; i++) {
		RectsDeEscena[i].x = 0;
		RectsDeEscena[i].y = 0;
		RectsDeEscena[i].w = 0;
		RectsDeEscena[i].h = 0;
		Hovered[i] = false;
		Clicked[i] = false;		
	}
	PosarNom = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/PosarNom.png");
	ScreenText::getInstance()->drawText("TEAM ENTRY", "TEAM ENTRY", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("TEAM PLAYER", "TEAM PLAYER", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("TEAM ENEMY", "TEAM ENEMY", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("TEAM NAME", "TEAM NAME", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("TEAM NAME", "TEAM NAME WHITE", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM ONE", "WORM ONE", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM ONE", "WORM ONE WHITE", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM TWO", "WORM TWO", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM TWO", "WORM TWO WHITE", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("BACK", "BACK", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("BACK", "BACK WHITE", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);

	ScreenText::getInstance()->drawText("TEAM NAME", "TEAM NAME 2", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("TEAM NAME", "TEAM NAME WHITE 2", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM ONE", "WORM ONE 2", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM ONE", "WORM ONE WHITE 2", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM TWO", "WORM TWO 2", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("WORM TWO", "WORM TWO WHITE 2", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
}

void SceneTeamEntry::render()
{
	int w;
	int h;
	ResourceManager::getInstance()->getGraphicSize(img, w, h);
	//Video::getInstance()->renderGraphic(img, 0, 0, w, h);
	//ResourceManager::getInstance()->getGraphicSize(alphabet, w, h);
	//Video::getInstance()->renderGraphic(alphabet, 0, 0, w, h);


	int Tw;
	int Th;
	int X, Y;
	if (Hovered[0] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("BACK"), Tw, Th);
		Y = h - (Th * 3);
		X = (w / 4) - (Tw * 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("BACK"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("BACK WHITE"), Tw, Th);
		Y = h - (Th * 3);
		X = (w / 4) - (Tw * 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("BACK WHITE"), X, Y, Tw, Th);
	}
	RectsDeEscena[0].x = X;
	RectsDeEscena[0].y = Y;
	RectsDeEscena[0].w = Tw;
	RectsDeEscena[0].h = Th;

	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM ENTRY"), Tw, Th);
	Y = (h/4) - Th;
	X = (w / 2) - (Tw / 2);
	Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM ENTRY"), X, Y, Tw, Th);

	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM PLAYER"), Tw, Th);
	Y += Th*2;
	X = (w / 4) -30;
	Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM PLAYER"), X, Y, Tw, Th);

	if (Hovered[2] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME"), Tw, Th);
		Y += Th*2;
		X = (w / 4) - 30;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME WHITE"), Tw, Th);
		Y += Th * 2;
		X = (w / 4) - 30;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME WHITE"), X, Y, Tw, Th);
	}
	RectsDeEscena[2].x = X;
	RectsDeEscena[2].y = Y;
	RectsDeEscena[2].w = Tw;
	RectsDeEscena[2].h = Th;

	if (Hovered[3] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE"), Tw, Th);
		Y += Th;
		X = (w / 4) - 30;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE WHITE"), Tw, Th);
		Y += Th;
		X = (w / 4) - 30;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE WHITE"), X, Y, Tw, Th);
	}
	RectsDeEscena[3].x = X;
	RectsDeEscena[3].y = Y;
	RectsDeEscena[3].w = Tw;
	RectsDeEscena[3].h = Th;

	if (Hovered[4] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO"), Tw, Th);
		Y += Th;
		X = (w / 4) - 30;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO WHITE"), Tw, Th);
		Y += Th;
		X = (w / 4) - 30;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO WHITE"), X, Y, Tw, Th);
	}
	RectsDeEscena[4].x = X;
	RectsDeEscena[4].y = Y;
	RectsDeEscena[4].w = Tw;
	RectsDeEscena[4].h = Th;

	// --- ENEMY

	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM ENTRY"), Tw, Th);
	Y = (h / 4) - Th;

	ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM ENEMY"), Tw, Th);
	Y += Th * 2;
	X = 480;
	Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM ENEMY"), X, Y, Tw, Th);

	if (Hovered[5] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME 2"), Tw, Th);
		Y += Th * 2;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME 2"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME WHITE 2"), Tw, Th);
		Y += Th * 2;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("TEAM NAME WHITE 2"), X, Y, Tw, Th);
	}
	RectsDeEscena[5].x = X;
	RectsDeEscena[5].y = Y;
	RectsDeEscena[5].w = Tw;
	RectsDeEscena[5].h = Th;

	if (Hovered[6] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE 2"), Tw, Th);
		Y += Th;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE 2"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE WHITE 2"), Tw, Th);
		Y += Th;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM ONE WHITE 2"), X, Y, Tw, Th);
	}
	RectsDeEscena[6].x = X;
	RectsDeEscena[6].y = Y;
	RectsDeEscena[6].w = Tw;
	RectsDeEscena[6].h = Th;

	if (Hovered[7] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO 2"), Tw, Th);
		Y += Th;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO 2"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO WHITE 2"), Tw, Th);
		Y += Th;
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("WORM TWO WHITE 2"), X, Y, Tw, Th);
	}
	RectsDeEscena[7].x = X;
	RectsDeEscena[7].y = Y;
	RectsDeEscena[7].w = Tw;
	RectsDeEscena[7].h = Th;
}

void SceneTeamEntry::update()
{

	for (size_t i = 0; i < getRectsDeEscenaSize(); i++)
	{
		if (Input::getInstance()->getMouseCoordinates()->x >= getRectsDeEscena(i)->x
			&&
			Input::getInstance()->getMouseCoordinates()->x <= (getRectsDeEscena(i)->x + getRectsDeEscena(i)->w)
			&&
			Input::getInstance()->getMouseCoordinates()->y >= getRectsDeEscena(i)->y
			&&
			Input::getInstance()->getMouseCoordinates()->y <= (getRectsDeEscena(i)->y + getRectsDeEscena(i)->h))
		{
			hoverText(i, true);
			if (Input::getInstance()->getMouseClick()->x != -1 && Input::getInstance()->getMouseClick()->y != -1) {
				setClicked(i);
			}
		}
		else {
			hoverText(i, false);
		}
	}

	if (Input::getInstance()->getKeyboard()->RETURN) {
		Input::getInstance()->getKeyboard()->RETURN = false;
		SceneDirector::getInstance()->changeScene(MAIN);
	}
}

void SceneTeamEntry::reinit()
{
	mReinit = true;
}

void SceneTeamEntry::hoverText(int i, bool iluminat)
{
	Hovered[i] = iluminat;
}

void SceneTeamEntry::setClicked(int i)
{
	std::string aux;

	switch (i)
	{
	case 0:
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		SceneDirector::getInstance()->changeScene(MAIN);
		break;
	case 1:// ok
		
		break;
	case 2:
		Clicked[2] = true;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		std::cout << "Enter team name: \n";
		std::cin >> aux;
		GameManager::getInstance()->setPlayerNames(0, aux);
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	case 3:
		Clicked[2] = false;
		Clicked[3] = true;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		std::cout << "Enter first worm name: \n";
		std::cin >> aux;
		GameManager::getInstance()->setPlayerNames(1, aux);
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	case 4:
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = true;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		std::cout << "Enter second worm name: \n";
		std::cin >> aux;
		GameManager::getInstance()->setPlayerNames(2, aux);
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	case 5:
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = true;
		Clicked[6] = false;
		Clicked[7] = false;
		std::cout << "Enter team name: \n";
		std::cin >> aux;
		GameManager::getInstance()->setEnemyNames(0, aux);
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	case 6:
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = true;
		Clicked[7] = false;
		std::cout << "Enter first worm name: \n";
		std::cin >> aux;
		GameManager::getInstance()->setEnemyNames(1, aux);
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	case 7:
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = true;
		std::cout << "Enter second worm name: \n";
		std::cin >> aux;
		GameManager::getInstance()->setEnemyNames(2, aux);
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	default:
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[2] = false;
		Clicked[3] = false;
		Clicked[4] = false;
		Clicked[5] = false;
		Clicked[6] = false;
		Clicked[7] = false;
		break;
	}
}

// el primer paràmatre es posa el equi que es vol la info, el segon paràmatre es per escollir teamname, worm1 o worm2
std::string SceneTeamEntry::getName(int equip, int info)
{
	switch (info)
	{
	case 0:
		return nameTeam[equip];
		break;
	case 1:
		return nameWorm1[equip];
		break;
	case 2:
		return nameWorm2[equip];
		break;
	default:
		return "cagaste";
		break;
	}

}

void SceneTeamEntry::setName(int info, std::string nom)
{
	switch (info)
	{
	case 0:
		nameTeam.push_back(nom);
		break;
	case 1:
		nameWorm1.push_back(nom);
		break;
	case 2:
		nameWorm2.push_back(nom);
		break;
	default:
		break;
	}
}

void SceneTeamEntry::initRectAlphabet()
{

	/*for (int i = 0; i < 29; i++)
	{
		letterClicked[i] = false;
	}
	//A
	RectAlphabet[0].x = 116;
	RectAlphabet[0].y = 421;
	RectAlphabet[0].w = 153-116;
	RectAlphabet[0].h = 446-421;
	//B
	RectAlphabet[1].x = 181;
	RectAlphabet[1].y = 422;
	RectAlphabet[1].w = 213 - 181;
	RectAlphabet[1].h = 446 - 422;
	//C
	RectAlphabet[2].x = 240;
	RectAlphabet[2].y = 422;
	RectAlphabet[2].w = 270 - 240;
	RectAlphabet[2].h = 446 - 422;
	//D
	RectAlphabet[3].x = 298;
	RectAlphabet[3].y = 422;
	RectAlphabet[3].w = 331 - 298;
	RectAlphabet[3].h = 444 - 422;
	//E
	RectAlphabet[4].x = 357;
	RectAlphabet[4].y = 422;
	RectAlphabet[4].w = 386 - 357;
	RectAlphabet[4].h = 447 - 422;
	//F
	RectAlphabet[5].x = 415;
	RectAlphabet[5].y = 424;
	RectAlphabet[5].w = 444 - 415;
	RectAlphabet[5].h = 446 - 424;
	//G
	RectAlphabet[6].x = 470;
	RectAlphabet[6].y = 421;
	RectAlphabet[6].w = 506 - 470;
	RectAlphabet[6].h = 446 - 421;
	//H
	RectAlphabet[7].x = 534;
	RectAlphabet[7].y = 423;
	RectAlphabet[7].w = 567 - 534;
	RectAlphabet[7].h = 446 - 423;
	//I
	RectAlphabet[8].x = 590;
	RectAlphabet[8].y = 424;
	RectAlphabet[8].w = 614 - 590;
	RectAlphabet[8].h = 447 - 424;
	//J
	RectAlphabet[9].x = 636;
	RectAlphabet[9].y = 420;
	RectAlphabet[9].w = 666 - 636;
	RectAlphabet[9].h = 445 - 420;
	//K
	RectAlphabet[10].x = 110;
	RectAlphabet[10].y = 457;
	RectAlphabet[10].w = 140 - 110;
	RectAlphabet[10].h = 482 - 457;
	//L
	RectAlphabet[11].x = 175;
	RectAlphabet[11].y = 459;
	RectAlphabet[11].w = 206 - 175;
	RectAlphabet[11].h = 482 - 459;
	//M
	RectAlphabet[12].x = 223;
	RectAlphabet[12].y = 457;
	RectAlphabet[12].w = 290 - 223;
	RectAlphabet[12].h = 481 - 457;
	//N
	RectAlphabet[13].x = 312;
	RectAlphabet[13].y = 459;
	RectAlphabet[13].w = 349 - 312;
	RectAlphabet[13].h = 482 - 459;
	//O
	RectAlphabet[14].x = 371;
	RectAlphabet[14].y = 458;
	RectAlphabet[14].w = 406 - 371;
	RectAlphabet[14].h = 480 - 458;
	//P
	RectAlphabet[15].x = 430;
	RectAlphabet[15].y = 457;
	RectAlphabet[15].w = 463 - 430;
	RectAlphabet[15].h = 481 - 457;
	//Q
	RectAlphabet[16].x = 483;
	RectAlphabet[16].y = 458;
	RectAlphabet[16].w = 518 - 483;
	RectAlphabet[16].h = 480 - 458;
	//R
	RectAlphabet[17].x = 542;
	RectAlphabet[17].y = 458;
	RectAlphabet[17].w = 574 - 542;
	RectAlphabet[17].h = 484 - 458;
	//S
	RectAlphabet[18].x = 595;
	RectAlphabet[18].y = 460;
	RectAlphabet[18].w = 622 - 595;
	RectAlphabet[18].h = 483 - 460;
	//T
	RectAlphabet[19].x = 641;
	RectAlphabet[19].y = 461;
	RectAlphabet[19].w = 675 - 641;
	RectAlphabet[19].h = 483 - 461;
	//U
	RectAlphabet[20].x = 70;
	RectAlphabet[20].y = 497;
	RectAlphabet[20].w = 103 - 70;
	RectAlphabet[20].h = 520 - 497;
	//V
	RectAlphabet[21].x = 124;
	RectAlphabet[21].y = 497;
	RectAlphabet[21].w = 164 - 124;
	RectAlphabet[21].h = 520 - 497;
	//W
	RectAlphabet[22].x = 184;
	RectAlphabet[22].y = 497;
	RectAlphabet[22].w = 246 - 184;
	RectAlphabet[22].h = 520 - 497;
	//X
	RectAlphabet[23].x = 274;
	RectAlphabet[23].y = 497;
	RectAlphabet[23].w = 313 - 274;
	RectAlphabet[23].h = 520 - 497;
	//Y
	RectAlphabet[24].x = 336;
	RectAlphabet[24].y = 497;
	RectAlphabet[24].w = 369 - 336;
	RectAlphabet[24].h = 520 - 497;
	//Z
	RectAlphabet[25].x = 398;
	RectAlphabet[25].y = 497;
	RectAlphabet[25].w = 430 - 398;
	RectAlphabet[25].h = 520 - 497;
	//DEL
	RectAlphabet[26].x = 453;
	RectAlphabet[26].y = 497;
	RectAlphabet[26].w = 553 - 453;
	RectAlphabet[26].h = 520 - 497;
	//SPACE
	RectAlphabet[27].x = 570;
	RectAlphabet[27].y = 497;
	RectAlphabet[27].w = 740 - 570;
	RectAlphabet[27].h = 520 - 497;
	//OK
	RectAlphabet[28].x = 378;
	RectAlphabet[28].y = 542;
	RectAlphabet[28].w = 450 - 378;
	RectAlphabet[28].h = 565 - 542;*/
}
