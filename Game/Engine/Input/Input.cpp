#include "Input.h"
Input* Input::pInstance = NULL;

Input::~Input()
{
	
}

Input* Input::getInstance()
{
	if (pInstance == NULL) {
		pInstance = new Input();
	}
	return pInstance;
}

float Input::NormalizeAxis(int value)
{
	if (value > 0) {
		return value / 32767.f;
	}
	else {
		return value / 32768.f;
	}
}

void Input::init()
{
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			
			pControler = SDL_GameControllerOpen(i);
			if (pControler)
			{
				isControler = true;
				//printf("\nController %i is connected\n", i);
				break;
			}
		}
	}
}

void Input::update(bool& endGame)
{
	while (SDL_PollEvent(&cEvent))
	{
		switch (cEvent.type) 
		{
			case SDL_QUIT:
				endGame = true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				switch (cEvent.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (click.isPressed==0) {
						if (cEvent.button.state == SDL_PRESSED) {
							click.x = cEvent.button.x;
							click.y = cEvent.button.y;
							click.isPressed=1;
						}
					}
					else {
						click.x = -1;
						click.y = -1;
						click.isPressed = 0;
					}
					
					break;
				default:
					break;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				switch (cEvent.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (click.isPressed==1) {
						if (cEvent.button.state == SDL_RELEASED) {
							click.x = -1;
							click.y = -1;
							click.isPressed = 0;
						}
					}
					
					break;
				default:
					break;
				}
				break;

			case SDL_MOUSEMOTION:
				keyboardMouse = false;
				mouse.x = cEvent.motion.x;
				mouse.y = cEvent.motion.y;
				break;
			case SDL_CONTROLLERAXISMOTION:
				switch (cEvent.caxis.axis)
				{
				case SDL_CONTROLLER_AXIS_LEFTX:
					
					break;
				case SDL_CONTROLLER_AXIS_LEFTY:
					
					break;
				case SDL_CONTROLLER_AXIS_RIGHTX:
					
					break;
				case SDL_CONTROLLER_AXIS_RIGHTY:
					
					break;
				default:
					break;
				}
			case SDL_KEYDOWN:
				keyboardMouse = true;
				switch (cEvent.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					tecles.W = true;
					break;
				case SDL_SCANCODE_S:
					tecles.S = true;
					break;
				case SDL_SCANCODE_A:
					tecles.A = true;
					break;
				case SDL_SCANCODE_D:
					tecles.D = true;
					break;
				case SDL_SCANCODE_ESCAPE:
					endGame = true;
					break;
				case SDL_SCANCODE_Z:
					if (tecles.isPressed == false) {
						tecles.Z = true;
						tecles.isPressed = true;
					}
					else {
						tecles.Z = false;
					}
					break;
				case SDL_SCANCODE_X:
					if (tecles.isPressed == false) {
						tecles.X = true;
						tecles.isPressed = true;
					}
					else {
						tecles.X= false;
					}
					
					break;
				case SDL_SCANCODE_C:
					tecles.C = true;
					break;
				case SDL_SCANCODE_V:
					tecles.V = true;
					break;
				case SDL_SCANCODE_B:
					tecles.B = true;
					break;
				case SDL_SCANCODE_RETURN:
					tecles.INTRO = true;
					break; 
				case SDL_SCANCODE_BACKSPACE:
					tecles.RETURN = true;
					break;
				case SDL_SCANCODE_SPACE:
					tecles.SPACE = true;
					break;
				default:
					break;
				}
				

				break;
			case SDL_KEYUP:
				switch (cEvent.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					tecles.W = false;
					break;
				case SDL_SCANCODE_S:
					tecles.S = false;
					break;
				case SDL_SCANCODE_A:
					tecles.A = false;
					break;
				case SDL_SCANCODE_D:
					tecles.D = false;
					break;
				case SDL_SCANCODE_Z:
					if (tecles.isPressed == true) {
						tecles.Z = false;
						tecles.isPressed = false;
					}
					else {
						tecles.Z = true;
					}
					
					break;
				case SDL_SCANCODE_X:
					if (tecles.isPressed == true) {
						tecles.X = false;
						tecles.isPressed = false;
					}
					else {
						tecles.X = true;
					}
					
					break;
				case SDL_SCANCODE_C:
					tecles.C = false;
					break;
				case SDL_SCANCODE_V:
					tecles.V = false;
					break;
				case SDL_SCANCODE_B:
					tecles.B = false;
					break;
				case SDL_SCANCODE_RETURN:
					tecles.INTRO = false;
					break;
				case SDL_SCANCODE_BACKSPACE:
					tecles.RETURN = false;
					break;
				case SDL_SCANCODE_SPACE:
					tecles.SPACE = false;
					break;
				default:
					break;
				}
				
				break;
		}
	}
}

void Input::refreshClick()
{
	click.x = -1;
	click.y = -1;
	click.isPressed = 0;
}

void Input::refreshKeyBoard()
{
	tecles.Z = false;
	tecles.X = false;
}

Input::Input()
{
	pControler = NULL;
	isControler = false;
	SDL_Init(SDL_INIT_GAMECONTROLLER);
}
