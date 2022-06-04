#pragma once
#include "sdl.h"
#include "sdl_ttf.h"
#include <string>
class ScreenText
{
public:
	static ScreenText* getInstance();
	void drawText(std::string string,
		std::string ID,
		int size,
		int fR, int fG, int fB,
		int bR, int bG, int bB);
	void ScreenTextQuit() { TTF_Quit(); };
	~ScreenText();
protected:
	ScreenText();

private:
	static ScreenText* pInstance;
};

