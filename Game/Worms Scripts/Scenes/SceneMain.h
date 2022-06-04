#pragma once
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Input/Input.h"
#include "../../Engine/Scene/SceneDirector.h"
//Falta #include TextManager
extern bool		EndGame;
class SceneMain :
    public Scene
{
public:
	
	SceneMain();
	//! Handles the drawing of the scene
	virtual void render();

	//! Handles the updating of the scene
	virtual void update();

	virtual void reinit();

	Rect * getRectsDeEscena(Uint8 i) { return &RectsDeEscena[i]; };

	void hoverText(int i, bool iluminat);
private:
	Rect RectsDeEscena[5];
	bool Hovered[5];
	
	int pantalla;
};

