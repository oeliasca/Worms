#include "SceneMain.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/Text/ScreenText.h"
#include "../../Engine/Definitions/definition.h"
#include "../../Engine/Audio/SoundManager.h"

int id;

SceneMain::SceneMain()
{
	img = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/Main.png");

	ScreenText::getInstance()->drawText("Play Game", "Play Game", TTF_MENUSIZE,255,255,100,0,0,0);
	ScreenText::getInstance()->drawText("Team Entry", "Team Entry", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("Ranking", "Ranking", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("Credits", "Credits", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);
	ScreenText::getInstance()->drawText("Exit", "Exit", TTF_MENUSIZE, 255, 255, 100, 0, 0, 0);

	ScreenText::getInstance()->drawText("Play Game", "Play Game White", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("Team Entry", "Team Entry White", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("Ranking", "Ranking White", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("Credits", "Credits White", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);
	ScreenText::getInstance()->drawText("Exit", "Exit White", TTF_MENUSIZE, 255, 255, 255, 0, 0, 0);

	for (size_t i = 0; i < 5; i++)
	{
		Hovered[i] = false;
	}
	
	pantalla = 0;

	id = SoundManager::getInstance()->loadAndGetSoundID("Assets/Sounds/WormsThemeSong.ogg");

	if (SoundManager::getInstance()->isPlaying(id)) {
		SoundManager::getInstance()->PlaySound(id, id, -1);
		SoundManager::getInstance()->graduateVolume(id, 10);
	}

}

void SceneMain::render()
{
	int w;
	int h;
	ResourceManager::getInstance()->getGraphicSize(img, w, h);
	Video::getInstance()->renderGraphic(img,0,0,w,h);

	int Tw;
	int Th;
	int X, Y;
	if (Hovered[0] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Play Game"), Tw, Th);
		Y = ((h - 35) / 2) - (Th / 2);
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Play Game"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Play Game White"), Tw, Th);
		Y = ((h - 35) / 2) - (Th / 2);
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Play Game White"), X, Y, Tw, Th);
	}
	RectsDeEscena[0].x = X;
	RectsDeEscena[0].y = Y;
	RectsDeEscena[0].w = Tw;
	RectsDeEscena[0].h = Th;

	if (Hovered[1] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Team Entry"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Team Entry"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Team Entry White"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Team Entry White"), X, Y, Tw, Th);
	}
	RectsDeEscena[1].x = X;
	RectsDeEscena[1].y = Y;
	RectsDeEscena[1].w = Tw;
	RectsDeEscena[1].h = Th;

	if (Hovered[2] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Ranking"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Ranking"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Ranking White"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Ranking White"), X, Y, Tw, Th);
	}
	RectsDeEscena[2].x = X;
	RectsDeEscena[2].y = Y;
	RectsDeEscena[2].w = Tw;
	RectsDeEscena[2].h = Th;

	if (Hovered[3] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Credits"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Credits"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Credits White"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Credits White"), X, Y, Tw, Th);
	}
	RectsDeEscena[3].x = X;
	RectsDeEscena[3].y = Y;
	RectsDeEscena[3].w = Tw;
	RectsDeEscena[3].h = Th;

	if (Hovered[4] == false) {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Exit"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Exit"), X, Y, Tw, Th);
	}
	else {
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("Exit White"), Tw, Th);
		Y += Th;
		X = (w / 2) - (Tw / 2);
		Video::getInstance()->renderText(ResourceManager::getInstance()->loadAndGetGraphicID("Exit White"), X, Y, Tw, Th);
	}
	RectsDeEscena[4].x = X;
	RectsDeEscena[4].y = Y;
	RectsDeEscena[4].w = Tw;
	RectsDeEscena[4].h = Th;
}

void SceneMain::update()
{

		//mirem si l'input ve de ratolí o teclat
		if (!Input::getInstance()->getKeyboardMouse()) {

			//mirem si seguim sent MainMenu o no
			
				//mirar colisio de rectangles de text 1 amb ratoli
				if (Input::getInstance()->getMouseCoordinates()->x >= getRectsDeEscena(0)->x
					&&
					Input::getInstance()->getMouseCoordinates()->x <= (getRectsDeEscena(0)->x + getRectsDeEscena(0)->w)
					&&
					Input::getInstance()->getMouseCoordinates()->y >= getRectsDeEscena(0)->y
					&&
					Input::getInstance()->getMouseCoordinates()->y <= (getRectsDeEscena(0)->y + getRectsDeEscena(0)->h))
				{
					hoverText(0, true);
					if (Input::getInstance()->getMouseClick()->x != -1 && Input::getInstance()->getMouseClick()->y != -1) {
						pantalla = 1;
						SceneDirector::getInstance()->changeScene(GAME, true);
						
					}
				}
				else {
					hoverText(0, false);
				}
			

			
				//mirar colisio de rectangles de text 2 amb ratoli
				if (Input::getInstance()->getMouseCoordinates()->x >= getRectsDeEscena(1)->x
					&&
					Input::getInstance()->getMouseCoordinates()->x <= (getRectsDeEscena(1)->x + getRectsDeEscena(1)->w)
					&&
					Input::getInstance()->getMouseCoordinates()->y >= getRectsDeEscena(1)->y
					&&
					Input::getInstance()->getMouseCoordinates()->y <= (getRectsDeEscena(1)->y + getRectsDeEscena(1)->h))
				{
					hoverText(1, true);
					if (Input::getInstance()->getMouseClick()->x != -1 && Input::getInstance()->getMouseClick()->y != -1) {
						pantalla = 2;
						SceneDirector::getInstance()->changeScene(TEAMENTRY, true);
						
					}
				}
				else {
					hoverText(1, false);
				}
			

			
				//mirar colisio de rectangles de text 3 amb ratoli
				if (Input::getInstance()->getMouseCoordinates()->x >= getRectsDeEscena(2)->x
					&&
					Input::getInstance()->getMouseCoordinates()->x <= (getRectsDeEscena(2)->x + getRectsDeEscena(2)->w)
					&&
					Input::getInstance()->getMouseCoordinates()->y >= getRectsDeEscena(2)->y
					&&
					Input::getInstance()->getMouseCoordinates()->y <= (getRectsDeEscena(2)->y + getRectsDeEscena(2)->h))
				{
					hoverText(2, true);
					if (Input::getInstance()->getMouseClick()->x != -1 && Input::getInstance()->getMouseClick()->y != -1) {
						pantalla = 3;
						SceneDirector::getInstance()->changeScene(RANKING, true);
						
					}
				}
				else {
					hoverText(2, false);
				}
			

			
				//mirar colisio de rectangles de text 4 amb ratoli
				if (Input::getInstance()->getMouseCoordinates()->x >= getRectsDeEscena(3)->x
					&&
					Input::getInstance()->getMouseCoordinates()->x <= (getRectsDeEscena(3)->x + getRectsDeEscena(3)->w)
					&&
					Input::getInstance()->getMouseCoordinates()->y >= getRectsDeEscena(3)->y
					&&
					Input::getInstance()->getMouseCoordinates()->y <= (getRectsDeEscena(3)->y + getRectsDeEscena(3)->h))
				{
					hoverText(3, true);
					if (Input::getInstance()->getMouseClick()->x != -1 && Input::getInstance()->getMouseClick()->y != -1) {
						pantalla = 4;
						SceneDirector::getInstance()->changeScene(CREDITS, true);
						
					}
				}
				else {
					hoverText(3, false);
				}
			

			
				//mirar colisio de rectangles de text 5 amb ratoli
				if (Input::getInstance()->getMouseCoordinates()->x >= getRectsDeEscena(4)->x
					&&
					Input::getInstance()->getMouseCoordinates()->x <= (getRectsDeEscena(4)->x + getRectsDeEscena(4)->w)
					&&
					Input::getInstance()->getMouseCoordinates()->y >= getRectsDeEscena(4)->y
					&&
					Input::getInstance()->getMouseCoordinates()->y <= (getRectsDeEscena(4)->y + getRectsDeEscena(4)->h))
				{
					hoverText(4, true);
					if (Input::getInstance()->getMouseClick()->x != -1 && Input::getInstance()->getMouseClick()->y != -1) {
						
						EndGame = !EndGame;
					}
				}
				else {
					hoverText(4, false);
				}
			
		}
		else {
			//aqui ve els inputs de tecles
			if (Input::getInstance()->getKeyboard()->W) {
				Input::getInstance()->getKeyboard()->W = false;
				
				hoverText(pantalla - 1, false);
				
				pantalla--;
				if (pantalla < 1) {
					pantalla = 1;
				}
				
				hoverText(pantalla - 1, true);
				



			}

			if (Input::getInstance()->getKeyboard()->S) {
				Input::getInstance()->getKeyboard()->S = false;
				
				hoverText(pantalla - 1, false);
				
				pantalla++;
				if (pantalla > 5) {
					pantalla = 5;
				}
				
				hoverText(pantalla - 1, true);
				

			}
		}
		if (Input::getInstance()->getKeyboard()->INTRO) {
			Input::getInstance()->getKeyboard()->INTRO = false;
			if (pantalla == 5) {
				EndGame = !EndGame;
			}
			else {
				hoverText(pantalla - 1, false);
				SceneDirector::getInstance()->changeScene((SceneEnum)pantalla, true);
			}
		}
	

}

void SceneMain::reinit()
{
	mReinit = false;
	if (SoundManager::getInstance()->isPlaying(id)) {
		SoundManager::getInstance()->PlaySound(id, -1, -1);
	}
}

void SceneMain::hoverText(int i, bool iluminat)
{
	Hovered[i] = iluminat;
}
