#pragma once
#include "../../Engine/Scene/Scene.h"
#include "../../Engine/Input/Input.h"
#include "../../Engine/Scene/SceneDirector.h"
#include <string>
#include <vector>
class SceneTeamEntry :
    public Scene
{
public:
	SceneTeamEntry();
	virtual void render();

	//! Handles the updating of the scene
	virtual void update();

	virtual void reinit();

	void hoverText(int i, bool iluminat);

	Rect* getRectsDeEscena(Uint8 i) { return &RectsDeEscena[i]; };

	Rect* getRectsAlphabet(Uint8 i) { return &RectAlphabet[i]; };

	int getRectsDeEscenaSize() { return sizeof(RectsDeEscena) / sizeof(RectsDeEscena[0]); };

	int getRectsAlphabetSize() { return sizeof(RectAlphabet) / sizeof(RectAlphabet[0]); };

	bool getletterClicked(int pos) { return letterClicked[pos]; };

	void setClicked(int i);

	void setLetterClicked(int i, bool bClicked) { letterClicked[i] = bClicked; };

	bool getClicked(int i) { return Clicked[i]; };

	std::string getName(int equip, int info);

	void setName(int info, std::string nom);

private:
	
	// Posicions de vector per equip
	std::string fillName;
	std::vector<std::string> nameTeam;
	std::vector<std::string> nameWorm1;
	std::vector<std::string> nameWorm2;

	int alphabet;
	int PosarNom;
	Rect RectsDeEscena[8];//coses de menu,opcions , tornar...
	bool Hovered[8];
	bool Clicked[8]; //click 1 back, click 2 OK, click 3 teamname, click 4 worm 1, click 5 worm 2
	Rect RectAlphabet[29];//només abecedari
	bool letterClicked[29];
	void initRectAlphabet();
};


/*

nom1:

nom2:

nom3:

nom4:

*/


/*
TUTORIAL INPOT PANEL BOX
https://www.youtube.com/watch?v=uRrUcMXXJEk

*/

