#include "Worm.h"
#include "../../Engine/Definitions/definition.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/Input/Input.h"
#include "../../Engine/Audio/SoundManager.h"


Worm::Worm() {
	Img = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/worms.png");
	Imgs = ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("Assets/img/worms.png");
	WromsState = BEGINGAME;
	stable = false;
	Rigth = true;
	lastTime = Video::getInstance()->getTicks();
	Transform.h = 60;//60
	Transform.w = 58;//58
	Transform.x = 450;
	Transform.y = 350;
	TransformCollision.x = 0;
	TransformCollision.y = 0;
	TransformCollision.w = 21;
	TransformCollision.h = 21;
	radius = 13;
	IndexWeapon = 0;
	friction = 0.1f;
	WeaponSlot.resize(4);
	for (size_t i = 0; i < 4; i++)
	{
		WeaponSlot.at(i) = new Weapon(i);
	}
	PowerTimer.setTimer(5000);
	isShoot = false;
	isProjectileReleased = false;
	xClickIni = 0;
	yClickIni = 0;
	frameX = 0;
	frameY = 0;
	ResourceManager::getInstance()->getGraphicSize(Img ,animation.w, animation.h);
	animation.w = animation.w / 11;
	animation.h = animation.h / 32;
	animation.x = 0;
	animation.y = 0;
	camOfX = 0;
	camOfY = 0;
	rebots = -1;
	HealthPoints = 100;
	Puntuacio = 0;

	//-- UI
	//wormUIname = new UIComponent("Joanot MArtorell",Transform.x - camOfX,Transform.y - camOfY,26);
	wormUIMaxPower = new UIComponent("Worm", Transform.x - camOfX, Transform.y - camOfY, POWER_BAR_WIDTH, POWER_BAR_HEIGHT, 0, 0, 255, 200);
	wormUICurrentPower = new UIComponent("TeamEnemyHP", wormUIMaxPower->getX() + 3, wormUIMaxPower->getY() + 3, 0, wormUIMaxPower->getH() - 6, 0, 0, 0, 255);
	wormUISignal = new UIComponent("Assets/img/fletxa.png", Transform.x, Transform.y, 43, 64);
	SignalTimer.setTimer(3000);
	showSignal = false;

	SoundsEffects[0] = SoundManager::getInstance()->loadAndGetSoundID("Assets/Sounds/Escopeta.ogg");
	SoundsEffects[1] = SoundManager::getInstance()->loadAndGetSoundID("Assets/Sounds/missil.ogg");
	SoundsEffects[2] = SoundManager::getInstance()->loadAndGetSoundID("Assets/Sounds/Noooo.ogg");
	SoundsEffects[3] = SoundManager::getInstance()->loadAndGetSoundID("Assets/Sounds/OuDear.ogg");
}

void Worm::update()
{
	wormUIname->setX(Transform.x - camOfX - (wormUIname->getW()/2) + Transform.w/2);
	wormUIname->setY(Transform.y - camOfY);
	wormUIMaxPower->setX(Transform.x - camOfX - (wormUIMaxPower->getW() / 2) + Transform.w / 2);
	wormUIMaxPower->setY(Transform.y - camOfY + Transform.h - 10);
	wormUICurrentPower->setX(wormUIMaxPower->getX() + wormUIMaxPower->getW() - 3);
	wormUICurrentPower->setY(Transform.y - camOfY + Transform.h -10 + 3);
	wormUISignal->setX(Transform.x - camOfX - (wormUISignal->getW() / 2) + Transform.w / 2);
	wormUISignal->setY(Transform.y - camOfY - wormUISignal->getH());


	int npixels = 0;
	switch (WromsState)
	{
	case MOVING:
		showSignal = false;
		temps.resetTimer();
		if (stable) {
			if (Input::getInstance()->getKeyboard()->A) {
				
				Rigth = false;
			}
			else if (Input::getInstance()->getKeyboard()->D) {
				
				Rigth = true;
			}
			else {
				WromsState = IDLE;
			}
			int MoveHorizontal = FrontVerticlaCollision(ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png"), Rigth);
			if (MoveHorizontal != -1)
			{
				if (MoveHorizontal != 0){
					if (Rigth) {
						Transform.x += 1;
						Transform.y -= MoveHorizontal;
					}
					else {
						Transform.x -= 1;
						Transform.y -= MoveHorizontal;
					}
				}
				else {
					if (Rigth) {
						Transform.x += 1;
						if (!checkCollisionGround(ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png"), npixels)) {
							
							
							WromsState = FALLING;
						}
						else {
							Transform.y += npixels;
						}
					}
					else {
						Transform.x -= 1;
						if (!checkCollisionGround(ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png"), npixels)) {
							
							
							WromsState = FALLING;
						}
						else {
							Transform.y += npixels;
						}
					}
				}
			}
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		break;
	case JUMPING:
		if (stable) {
			if (Rigth == true) {
				VelocityX = 10;
			}
			else {
				VelocityX = -10;
			}
			VelocityY = -30;
			stable = false;
			lastTime = Video::getInstance()->getTicks();
			WromsState = FALLING;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		break;
	case AIMING: // acabas de apretar per disparar
		switch (IndexWeapon)
		{
		case 0:
			throwGranade();
			break;
		case 1:
			//rayCast(Transform.x + Transform.w / 2, Transform.y + Transform.h / 2, xClickIni + camOfX, yClickIni + camOfY,
			shootGun();

			break;
		case 2:
			throwGranade();
			break;
		case 3:
			break;
		default:
			break;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		break;
	case SHOOT:
		temps.resetTimer();
		if (getpWeapon(IndexWeapon)->pProjectile==nullptr) {
			WromsState = WAITING;
			isShoot = false;
			Power = 0;
		}

		break;
	case IDLE: // tens torn, estas quiet
		temps.resetTimer();
		if (Input::getInstance()->getMouseClick()->isPressed == 1) {
			WromsState = AIMING;
		}
		else if ((Input::getInstance()->getKeyboard()->A || Input::getInstance()->getKeyboard()->D)) {
			WromsState = MOVING;

		}
		else if (Input::getInstance()->getKeyboard()->SPACE) {
			WromsState = PREPAREJUMP;
			frameTimer.resetTimer();
			frameY = 0;
		}
		else if (!stable){
			WromsState = FALLING;
			frameTimer.resetTimer();
			frameY = 0;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		if (Input::getInstance()->getKeyboard()->Z) {
			IndexWeapon--;
			Input::getInstance()->refreshKeyBoard();
		}
		if (Input::getInstance()->getKeyboard()->X) {
			IndexWeapon++;
			Input::getInstance()->refreshKeyBoard();
		}
		if (IndexWeapon < 0) {
			IndexWeapon = 0;
		}
		if (IndexWeapon > 3) {
			IndexWeapon = 3;
		}
		break;
	case DEATH:
		Transform.x = -100;
		Transform.y = -100;
		HealthPoints = 0;

		break;
	case HIT:
		WormPhysics::translatePhysicsObjects();
		if (stable) {
			frameY = 0;
			WromsState = LANDINGHIT;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}

		break;
	case FALLING: 
		WormPhysics::translatePhysicsObjects();
		if (stable) {
			frameY = 0;
			WromsState = LANDING;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		break;
	case WAITING: // no et toca el tron
		temps.resetTimer();
		WormPhysics::translatePhysicsObjects();
		frameY = 0;
		isProjectileReleased = false;
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		wormUICurrentPower->setW(-wormUIMaxPower->getW() + 6);
		Power = 0.0f;
		SignalTimer.resetTimer();
		showSignal = false;
		break;
	case BEGINGAME:
		if (!stable) {
			WormPhysics::translatePhysicsObjects();
		}
		else {
			WromsState = WAITING;
		}
		break;
	default:
		break;
	}

	updateAnimation();

}

void Worm::render()
{
	Vec2 wormPoint;
	wormPoint.X = Transform.x - (Transform.w / 2);
	wormPoint.Y = Transform.y - (Transform.h / 2);
	if (!Rigth) {
		Video::getInstance()->renderGraphic(Img, Transform.x-camOfX, Transform.y-camOfY, Transform.w, Transform.h, animation);
	}
	else {
		Video::getInstance()->renderGraphic(Img, Transform.x-camOfX, Transform.y-camOfY, Transform.w, Transform.h, animation, 0, &wormPoint, FLIP_HORIZONTAL);
	}
	wormUIname->render();
	if (WromsState == AIMING) {
		wormUIMaxPower->render();
		wormUICurrentPower->render();
	}
	if (showSignal) {
		wormUISignal->render();
		SignalTimer.refreshTimer();
		if (SignalTimer.hasCompleted()) {
			SignalTimer.resetTimer();
			showSignal = false;
		}
	}
}

void Worm::setHealth(int HP)
{
	HealthPoints -= HP;
	if (HealthPoints <= 0) {
		HealthPoints = 0;
	}
}

void Worm::updateAnimation() {

	frameTimer.refreshTimer();

	int x = 0;
	int y = 0;
	float auxsin = 0.0f;
	float auxcos = 0.0f;

	switch (WromsState)
	{
	case MOVING:
		animation.x = 2 * Transform.w;
		if (frameTimer.getTimer() > 120) {
			frameY++;
			frameTimer.resetTimer();
		}
		if (frameY >= 15) {
			frameY = 0;
		}
		animation.y = frameY * (animation.h);
		break;
	case PREPAREJUMP:
		animation.x = 6 * Transform.w;
		if (frameTimer.getTimer() > 100) {
			frameY++;
			frameTimer.resetTimer();
		}
		animation.y = frameY * (animation.h);
		if (frameY >= 9) {
			WromsState = JUMPING;
			frameY = 0;
			frameTimer.resetTimer();
		}
		break;
	/*case AIMING: // acabas de apretar per disparar
		if (Input::getInstance()->getMouseClick()->isPressed) {
			PowerTimer.refreshTimer();
			TimePressed = PowerTimer.getTimer();
			Power = 35 + (35 * sinf(((2 * 3.1415) / 5000) * TimePressed));
			
			if (!isShoot) {
				xClickIni = Input::getInstance()->getMouseClick()->x;
				yClickIni = Input::getInstance()->getMouseClick()->y;
			}
			isShoot = true;
		}
		else if (!Input::getInstance()->getMouseClick()->isPressed && isShoot) {
			PowerTimer.resetTimer();
			Power = 35 + (35 * sinf(((2 * 3.1415) / 5) * TimePressed));


			cosAngle = (-(Transform.x + (Transform.w / 2)) + xClickIni) / sqrtf(((-(Transform.x + (Transform.w / 2)) + xClickIni) * (-(Transform.x + (Transform.w / 2)) + xClickIni)) + ((-(Transform.y + (Transform.h / 2)) + yClickIni) * ((-(Transform.y + (Transform.h / 2)) + yClickIni))));
			sinAngle = (-(Transform.y + (Transform.h / 2)) + yClickIni) / sqrtf(((-(Transform.x + (Transform.w / 2)) + xClickIni) * (-(Transform.x + (Transform.w / 2)) + xClickIni)) + ((-(Transform.y + (Transform.h / 2)) + yClickIni) * ((-(Transform.y + (Transform.h / 2)) + yClickIni))));

			isShoot = false;
			//WromsState = WAITING;
			isProjectileReleased = true;

			std::modf((Transform.x + (Transform.w / 2)) + ((WeaponSlot->getWidth() + WeaponSlot->getWidth() * 1.7) * cosAngle), &fNoDecimalX);
			std::modf((Transform.y + (Transform.h / 2)) + ((WeaponSlot->getHeight() + WeaponSlot->getHeight() * 1.7) * sinAngle), &fNoDecimalY);

		


			WeaponSlot->setTransform((int)fNoDecimalX, (int)fNoDecimalY);
		}
		break;*/
	case IDLE: // tens torn, estas quiet
		x = Input::getInstance()->getMouseCoordinates()->x;
		y = Input::getInstance()->getMouseCoordinates()->y;		
		auxsin = ((Transform.y + (Transform.h / 2)) - (y + camOfY)) / sqrtf(((-(Transform.x + (Transform.w / 2)) + x + camOfX) * (-(Transform.x + (Transform.w / 2)) + x + camOfX)) + (((Transform.y + (Transform.h / 2)) - (y + camOfY)) * (((Transform.y + (Transform.h / 2)) - (y + camOfY)))));
		AngleAnimacio = (asin(auxsin) + M_PI/2) * 180.0 / M_PI;
		frameY = (int)AngleAnimacio / 6;

		if (x + camOfX < Transform.x) {
			Rigth = false;
		}
		else {
			Rigth = true;
		}
		
		switch (IndexWeapon)
		{
		case 0:
			animation.x = 5 * Transform.w;
			animation.y = frameY * (animation.h);
			break;
		case 1:
			animation.x = 10 * Transform.w;
			animation.y = frameY * (animation.h);
			break;
		case 2:
			animation.x = 5 * Transform.w;
			animation.y = 13 * (animation.h);
			break;
		case 3:
			animation.x = 5 * Transform.w;
			animation.y = 13 * (animation.h);
			break;
		default:
			break;
		}
		break;
	//case DEATH:
	//	break;
	case HIT:
		animation.x = 0 * Transform.w;
		if (frameTimer.getTimer() > 100) {
			frameY++;
			frameTimer.resetTimer();
		}
		if (frameY >= 31) {
			frameY = 0;
		}
		animation.y = frameY * (animation.h);
		break;
	case FALLING:
		animation.x = 7 * Transform.w;
		if (frameTimer.getTimer() > 120) {
			frameY++;
			frameTimer.resetTimer();
		}
		if (frameY >= 7) {
			frameY = 6;
		}
		animation.y = frameY * (animation.h);
		break;
	case LANDINGHIT:
		animation.x = 9 * Transform.w;
		if (frameTimer.getTimer() > 100) {
			frameY++;
			frameTimer.resetTimer();
		}
		if (frameY >= 6) {
			frameY = 5;
			WromsState = WAITING;
		}
		animation.y = frameY * (animation.h);
		break;
	case LANDING:
		animation.x = 9 * Transform.w;
		if (frameTimer.getTimer() > 100) {
			frameY++;
			frameTimer.resetTimer();
		}
		if (frameY >= 6) {
			frameY = 5;
			WromsState = IDLE;
		}
		animation.y = frameY * (animation.h);
		break;
	case WAITING:
		animation.x = 6 * Transform.w;
		frameY = 0;
		animation.y = frameY * (animation.h);
		break;
	default:
		break;
	}

}

void Worm::throwGranade()
{

	double fNoDecimalX;
	double fNoDecimalY;

	if (Input::getInstance()->getMouseClick()->isPressed) {
		PowerTimer.refreshTimer();
		TimePressed = PowerTimer.getTimer();
		
		Power = 35 + (35 * sinf(((2 * 3.1415) / 5000) * TimePressed));
		if (!isShoot) {
			xClickIni = Input::getInstance()->getMouseClick()->x;
			yClickIni = Input::getInstance()->getMouseClick()->y;
		}
		isShoot = true;
		wormUICurrentPower->setW(-(int)Utiles.mapValue((70.0f - (70.0f * (Power / 70.0f))), 0.0f, 70.0f, 0.0f, POWER_BAR_WIDTH - 6.0f));
		//printf("cos: %f\n", Power);
	}
	else if (!Input::getInstance()->getMouseClick()->isPressed && isShoot) {

		PowerTimer.resetTimer();
		Power = 35 + (35 * sinf(((2 * 3.1415) / 5) * TimePressed));

		cosAngle = (-(Transform.x - camOfX + (Transform.w / 2)) + xClickIni) / sqrtf(((-(Transform.x - camOfX + (Transform.w / 2)) + xClickIni) * (-(Transform.x - camOfX + (Transform.w / 2)) + xClickIni)) + ((-(Transform.y - camOfY + (Transform.h / 2)) + yClickIni) * ((-(Transform.y - camOfY + (Transform.h / 2)) + yClickIni))));
		sinAngle = (-(Transform.y - camOfY + (Transform.h / 2)) + yClickIni) / sqrtf(((-(Transform.x - camOfX + (Transform.w / 2)) + xClickIni) * (-(Transform.x - camOfX + (Transform.w / 2)) + xClickIni)) + ((-(Transform.y - camOfY + (Transform.h / 2)) + yClickIni) * ((-(Transform.y - camOfY + (Transform.h / 2)) + yClickIni))));

		//printf("cos: %f, sin: %f", cosAngle, sinAngle);
		//isShoot = false;
		WromsState = SHOOT;
		isProjectileReleased = true;

		std::modf((Transform.x + (Transform.w / 2)) + ((WeaponSlot[IndexWeapon]->getWidth() + WeaponSlot[IndexWeapon]->getWidth() * 1.7) * cosAngle), &fNoDecimalX);
		std::modf((Transform.y + (Transform.h / 2)) + ((WeaponSlot[IndexWeapon]->getHeight() + WeaponSlot[IndexWeapon]->getHeight() * 1.7) * sinAngle), &fNoDecimalY);
		
		WeaponSlot[IndexWeapon]->setTransform((int)fNoDecimalX, (int)fNoDecimalY);

		SoundManager::getInstance()->PlaySound(SoundsEffects[1], -1, 0);
	}
}

void Worm::shootGun()
{
	isProjectileReleased = true;
	xClickIni = Input::getInstance()->getMouseClick()->x;
	yClickIni = Input::getInstance()->getMouseClick()->y;
	SoundManager::getInstance()->PlaySound(SoundsEffects[0], -1, 0);
	WromsState = SHOOT;
	Input::getInstance()->getMouseClick()->isPressed=0;
//	isProjectileReleased = false;
}

void Worm::refreshTimer()
{
	temps.resetTimer();
}


void Worm::renderSignal() {
	showSignal = true;
}

void Worm::setWormName(const char* name)
{
	wormUIname = new UIComponent(name, Transform.x - camOfX, Transform.y - camOfY, 26);
}

void Worm::playSound(int i)
{
	SoundManager::getInstance()->PlaySound(SoundsEffects[i], -1, 0);
}


