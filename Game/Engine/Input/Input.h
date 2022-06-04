#pragma once
#include "sdl.h"
#include <iostream>
class Input
{
	struct MouseCoordinates {
		int x;
		int y;
	};
	struct MouseClickCoordinates {
		int x = -1;
		int y = -1;
		int isPressed = 0;
	};

	struct Keyboard {
		bool A;
		bool D;
		bool Z;
		bool X;
		bool C;
		bool V;
		bool B;
		bool W;
		bool S;
		bool INTRO;
		bool RETURN;
		bool SPACE;
		bool isPressed = false;
	};
	bool keyboardMouse;//true keyboard, false mouse
public:
	~Input();
	static Input* getInstance();
	float NormalizeAxis(int value);
	void init();
	void update(bool &endGame);

	MouseClickCoordinates* getMouseClick() { return &click; };
	MouseCoordinates* getMouseCoordinates() { return &mouse; };
	Keyboard* getKeyboard() { return &tecles; };
	bool getKeyboardMouse() { return keyboardMouse; };
	void refreshClick();
	void refreshKeyBoard();
protected:
	Input();

private:
	static Input* pInstance;
	SDL_Event cEvent;
	
	MouseClickCoordinates click;
	MouseCoordinates mouse;
	SDL_GameController* pControler;
	Keyboard tecles;
	bool isControler;
};

