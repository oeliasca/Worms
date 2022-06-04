#include "WormEnemy.h"
#include "../../Engine/Definitions/definition.h"
#include "../../Engine/Video/ResourceManager.h"
#include "../../Engine/Video/Video.h"
#include "../../Engine/Audio/SoundManager.h"

void WormEnemy::update()
{
	wormUIname->setX(Transform.x - camOfX - (wormUIname->getW() / 2) + Transform.w / 2);
	wormUIname->setY(Transform.y - camOfY);
	wormUISignal->setX(Transform.x - camOfX - (wormUISignal->getW() / 2) + Transform.w / 2);
	wormUISignal->setY(Transform.y - camOfY - wormUISignal->getH());

	switch (WromsState)
	{
	case MOVING:
		if (stable) {
			moveToNearestWorm();
			if (checkDistance() < 250) {
				throwGranade();
			}
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		if (CaminarIntents >= 3) {
			if (!alreadyJump) {
				WromsState = JUMPING;
				CaminarIntents = 0;
			}
			else {
				WromsState = AIMING;
			}
		}
		temps.resetTimer();
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
			alreadyJump = true;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		temps.resetTimer();
		break;
	case AIMING: // acabas de apretar per disparar
		switch (IndexWeapon)
		{
		case 0:
			throwGranade();
			break;
		case 1:
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
		temps.resetTimer();
		break;
	case SHOOT:
		temps.resetTimer();
		if (getpWeapon(IndexWeapon)->pProjectile == nullptr) {
			WromsState = WAITING;
			isShoot = false;
			Power = 0;
		}
		break;
	case IDLE: // tens torn, estas quiet
		temps.resetTimer();
		startDelay.refreshTimer();
		//per algun motiu al començament no sempre es estable...
		if (!stable) {
			stable = true;
		}
		
		if (startDelay.hasCompleted()) {
			if (stable) {
				getNearestWorm();
			}
			if (FocusedWorm != -1) {
				WromsState = MOVING;
			}
			if (IndexWeapon < 0) {
				IndexWeapon = 0;
			}
			if (IndexWeapon > 3) {
				IndexWeapon = 3;
			}
		}
		break;
	case DEATH:
		Transform.x = -100;
		Transform.y = -100;
		HealthPoints = 0;
		break;
	case HIT:
		WormPhysics::translatePhysicsObjects();
		startDelay.resetTimer();
		if (stable) {
			frameY = 0;
			WromsState = LANDINGHIT;
		}
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
		temps.resetTimer();
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
		temps.resetTimer();
		break;
	case WAITING: // no et toca el tron
		temps.resetTimer();
		startDelay.resetTimer();
		CaminarIntents = 0;
		alreadyJump = false;
		frameY = 0;
		WormPhysics::translatePhysicsObjects();
		FocusedWorm = -1;
		isProjectileReleased = false;
		if (HealthPoints <= 0) {
			WromsState = DEATH;
		}
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

void WormEnemy::init()
{
	FocusedWorm = -1;
	alreadyJump = false;
	CaminarIntents = 0;
	Img = ResourceManager::getInstance()->loadAndGetGraphicID("Assets/img/wormsEnemy.png");
	Imgs = ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("Assets/img/wormsEnemy.png");
	startDelay.setTimer(3000);
}

void WormEnemy::render()
{
	
	Vec2 wormPoint;
	wormPoint.X = Transform.x - (Transform.w / 2);
	wormPoint.Y = Transform.y - (Transform.h / 2);
	if (!Rigth) {
		Video::getInstance()->renderGraphic(Img, Transform.x - camOfX, Transform.y - camOfY, Transform.w, Transform.h, animation);
	}
	else {
		Video::getInstance()->renderGraphic(Img, Transform.x - camOfX, Transform.y - camOfY, Transform.w, Transform.h, animation, 0, &wormPoint, FLIP_HORIZONTAL);
		
	}
	wormUIname->render();
	if (showSignal) {
		wormUISignal->render();
		SignalTimer.refreshTimer();
		if (SignalTimer.hasCompleted()) {
			SignalTimer.resetTimer();
			showSignal = false;
		}
	}
}

void WormEnemy::getNearestWorm()
{
	int dist = 3000000;

	for (int i = 0; i < mWorms.size(); i++)
	{
		if (dynamic_cast<Worm*>(mWorms.at(i))->getWormState() != DEATH) {
			int aux = abs(mWorms.at(i)->getX() - Transform.x);
			if (aux < dist) {
				if (mWorms.at(i)->getX() - Transform.x < 0) {
					Rigth = false;
				}
				else {
					Rigth = true;
				}
				dist = aux;
				FocusedWorm = i;
			}
		}
	}

}

void WormEnemy::moveToNearestWorm()
{
	int npixels = 0;
	int MoveHorizontal = FrontVerticlaCollision(ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png"), Rigth);
	if (MoveHorizontal != -1)
	{
		if (MoveHorizontal != 0) {
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
					CaminarIntents++;
				}
				else {
					Transform.y += npixels;
				}
			}
			else {
				Transform.x -= 1;
				if (!checkCollisionGround(ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png"), npixels)) {
					WromsState = FALLING;
					CaminarIntents++;
				}
				else {
					Transform.y += npixels;
				}
			}
		}
	}
	else {
		CaminarIntents++;
	}
}

int WormEnemy::checkDistance()
{
	return abs(mWorms.at(FocusedWorm)->getX() - Transform.x);
}

void WormEnemy::throwGranade()
{
	double fNoDecimalX;
	double fNoDecimalY;
	float angle;// = (rand() % 50 + 10) * M_PI / 180;

	//-45->315 = top-right
	if (Rigth) {
		//angle = 315 * M_PI / 180;
		angle = (rand() % 50 + 300) * M_PI / 180;
	}else {
		//angle = 225 * M_PI / 180;
		angle = (rand() % 50 + 190) * M_PI / 180;
	}
	

	cosAngle = cos(angle);
	sinAngle = sin(angle);

	

	int x = abs(mWorms.at(FocusedWorm)->getX() - Transform.x);
	int y = abs(mWorms.at(FocusedWorm)->getY() - Transform.y);
	Power = sqrt((x*x*g)/(2* cosAngle* cosAngle*(y+x*tan(angle))));
	if ((2 * cosAngle * cosAngle * (y + x * tan(angle))) < 0) {
	Power = sqrt((x * x * g) / abs(2 * cosAngle * cosAngle * (y + x * tan(angle))));
	}

	WromsState = SHOOT;
	isProjectileReleased = true;

	std::modf((Transform.x + (Transform.w / 2)) + ((WeaponSlot[IndexWeapon]->getWidth() + WeaponSlot[IndexWeapon]->getWidth() * 1.7) * cosAngle), &fNoDecimalX);
	std::modf((Transform.y + (Transform.h / 2)) + ((WeaponSlot[IndexWeapon]->getHeight() + WeaponSlot[IndexWeapon]->getHeight() * 1.7) * sinAngle), &fNoDecimalY);

	WeaponSlot[IndexWeapon]->setTransform((int)fNoDecimalX, (int)fNoDecimalY);

	SoundManager::getInstance()->PlaySound(SoundsEffects[1], -1, 0);
}

void WormEnemy::updateAnimation() {

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

		AngleAnimacio = 100;
		frameY = (int)AngleAnimacio / 6;

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
