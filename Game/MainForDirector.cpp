#include "Engine/Scene/SceneDirector.h"
#include "Engine/Input/Input.h"
#include "Engine/Video/Video.h"
#include "Engine/GameManager/GameManager.h"

#include <stdlib.h>
#include <time.h> 

//#include "GameManager.h"


extern bool		         EndGame       = false;
extern SceneDirector	*sDirector     = NULL;
extern Input	        *sInputControl = NULL;
Video* sVideo = NULL;
int main( int argc, char* argv[] ) { 
	srand(time(NULL));

	//Init Singletons
	sInputControl	= Input::getInstance();
	sDirector		= SceneDirector::getInstance();
	sVideo = Video::getInstance();
	


	int pantalla = 0;

	while (!EndGame){
		sVideo->clearScreen(0x000000);
		//ReInit o no
		if(sDirector->getCurrentScene()->mustReInit()){
			sDirector->getCurrentScene()->reinit();
		}
		// Read controls
		sInputControl->update(EndGame);
		
		/*
		0->Main Menu --------------- done
		1->Play Game ---------------
		2->Team Entry -------------- done
		3->Ranking   --------------- done
		4->Credits   --------------- done
		5->Exit//No es escena
		6->SaveLoad//com si no existis
		*/
		
		// Updates scene
		sDirector->getCurrentScene()->update();

		sDirector->getCurrentScene()->render();
		sVideo->updateScreen();


		if(!sDirector->getCurrentScene()->mustReInit()){
			sDirector->getCurrentScene()->render();
		}

		sVideo->vSync();
	}

	return 0;
}

