#include "WormPhysics.h"
#include "../Video/ResourceManager.h"
#include "../Video/Video.h"

#include <math.h> 
#define PI 3.14159265

WormPhysics::WormPhysics(float x, float y,float r,float fr)
{
	Transform.x = x;
	Transform.y = y;
	radius = r;
	stable = false;
	g = 15.0f;
	lastTime = 0;///SE TE KCAMBIAR
	AcceleracioX = 0;
	AcceleracioY = 0;
	VelocityX = 0;
	VelocityY = 0;
	AngleAnimacio=0; // Angle de rotació
	isTouched=false;
	friction = fr;
	acumulatePixelX = 0.0f;
	acumulatePixelY = 0.0f;
	cosAngle = 0;
	sinAngle = 0;
}

bool WormPhysics::checkCollision(int img, float radi, float IniAngle, float EndAngle)
{
	
	int offX;
	int offY;
	
	Rect auxRect;
	auxRect.x = ResourceManager::getInstance()->getSurfaceClipRect(img)->x;
	auxRect.y = ResourceManager::getInstance()->getSurfaceClipRect(img)->y;
	auxRect.w = ResourceManager::getInstance()->getSurfaceClipRect(img)->w;
	auxRect.h = ResourceManager::getInstance()->getSurfaceClipRect(img)->h;

	offset(&auxRect, offX, offY);
	int X = (Transform.x + (TransformCollision.w / 2)) - offX;//centre cercle
	int Y = (Transform.y + (TransformCollision.h / 2)) - offY;//centre cercle

	
	Uint8* pixelArray = ResourceManager::getInstance()->getArrayPixels(img);
	int w = ResourceManager::getInstance()->getSurfaceW(img);
	int h = ResourceManager::getInstance()->getSurfaceH(img);
	int pitch = ResourceManager::getInstance()->getSurfacePitch(img);
	int bytesPerPixel = ResourceManager::getInstance()->getSurfaceBytesPerPixel(img);


	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{

			//mirem un cercle de radi 'radi' i la part de l'angle en el que es troba
			if (sqrt((j - X) * (j - X) + (i - Y) * (i - Y)) == radi) {
				float actualAngle;
				if ((j - X)==0 && (i - Y)>0) {
					actualAngle = 90;
				}
				else if ((j - X) == 0 && (i - Y) < 0) {
					actualAngle = 270;
				}
				else {
					actualAngle = atan((i - Y) / (j - X)) * 180 / PI;
				}

				if (actualAngle>IniAngle && actualAngle<EndAngle) {
					//s'ha de mirar quin era el canal alfa
					pixelArray[i * pitch + j * bytesPerPixel + 0];//r;
					pixelArray[i * pitch + j * bytesPerPixel + 1];//g;
					pixelArray[i * pitch + j * bytesPerPixel + 2];//b;
					pixelArray[i * pitch + j * bytesPerPixel + 3];//a;

					/*if alfa = transparent return true*/
					if (pixelArray[i * pitch + j * bytesPerPixel + 3]!=0) {
						return true;
					}
				}
			}


		}
	}
	
	
	return false;
}

bool WormPhysics::checkExplosionCollision()
{
	return false;
}

bool WormPhysics::checkCollisionPoints(int img, float TestPostX, float TestPostY)
{

	int offX;
	int offY;

	Rect auxRect;
	auxRect.x = ResourceManager::getInstance()->getSurfaceClipRect(img)->x;
	auxRect.y = ResourceManager::getInstance()->getSurfaceClipRect(img)->y;
	auxRect.w = ResourceManager::getInstance()->getSurfaceClipRect(img)->w;
	auxRect.h = ResourceManager::getInstance()->getSurfaceClipRect(img)->h;

	offset(&auxRect, offX, offY);
	int X = (TestPostX) - offX;//punt del cercle de colisio
	int Y = (TestPostY) - offY;//punt del cercle de colisio

	
	Uint8* pixelArray = ResourceManager::getInstance()->getArrayPixels(img);
	int pitch = ResourceManager::getInstance()->getSurfacePitch(img);
	int bytesPerPixel = ResourceManager::getInstance()->getSurfaceBytesPerPixel(img);
	//mirem canal alfa en el punt
	if (pixelArray[Y * pitch + X * bytesPerPixel + 3]!=0) {
		return true;
	}
	
	return false;
}

void WormPhysics::translatePhysicsObjects()
{
	temps.refreshTimer();

	SyncPhysics.setTimer(17);
	SyncPhysics.refreshTimer();
	while (!SyncPhysics.hasCompleted()) {
		SyncPhysics.refreshTimer();
	}

	//Apliquem gravetat al worm
	AcceleracioY += g;
	VelocityY += AcceleracioY * (temps.getDeltaTimer() / 1000.0f);
	VelocityX += AcceleracioX * (temps.getDeltaTimer() / 1000.0f);
	

	//Update position
	float fPotentialX = Transform.x + VelocityX * (temps.getDeltaTimer() / 1000.0f);
	float fPotentialY = Transform.y + VelocityY * (temps.getDeltaTimer() / 1000.0f);
	
	
	
	
	//Reset Acceleration
	AcceleracioX = 0;
	AcceleracioY = 0;
	stable = false;

	//Collision check with map
	float fAngle = atan2f(VelocityY, VelocityX);// *(180.0f / 3.141592);
	float responseX = 0;
	float responseY = 0;
	bool bCollision = false;

	for (float r = fAngle - M_PI / 2.0f; r < fAngle + M_PI / 2.0f; r += M_PI / 10.0f)
	{
		float fTestPosX = radius * cosf(r) + fPotentialX + (Transform.w / 2);//coordenades dels punts del cercle de colisio que poden xocar
		float fTestPosY = radius * sinf(r) + fPotentialY + (Transform.h / 2);//coordenades dels punts del cercle de colisio que poden xocar


		//Falta mirar que fTestPos no sigui una coordenada fora de la imatge
		int w;
		int h;
		ResourceManager::getInstance()->getGraphicSize(ResourceManager::getInstance()->loadAndGetGraphicID("perlinNoiseTest.png"), w, h);

		if (fTestPosX<w && fTestPosX>0 && fTestPosY < h && fTestPosY>0) {
			if (checkCollisionPoints(ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png"), fTestPosX, fTestPosY)) {
				responseX += fPotentialX - fTestPosX;
				responseY += fPotentialY - fTestPosY;
				bCollision = true;
			}
		}
		

	}

	//find angle of collision
	float fMagVelocity = sqrtf(VelocityX * VelocityX + VelocityY * VelocityY);
	float fMagResponse = sqrtf(responseX * responseX + responseY * responseY);

	if (bCollision) {
		
		//calculate reflection vector
		float dot = VelocityX * (responseX / fMagResponse) + VelocityY * (responseY / fMagResponse);

		VelocityX = friction * (-2.0f * dot * (responseX / fMagResponse) + VelocityX);
		VelocityY = friction * (-2.0f * dot * (responseY / fMagResponse) + VelocityY);

		if (rebots != -1) {
			rebots--;
		}

	}
	else {
		//double f = 123.45;
		//double f3;
		//double f2 = std::modf(f, &f3);
		//std::cout << "modf() makes " << f3 << " + " << f2 << '\n';
		//modf() makes 123 + 0.45
		double fNoDecimalX;
		double fNoDecimalY;
		double decimalX = std::modf(fPotentialX, &fNoDecimalX);
		double decimalY = std::modf(fPotentialY, &fNoDecimalY);
		acumulatePixelX = acumulatePixelX + decimalX;
		acumulatePixelY = acumulatePixelY + decimalY;
		if (acumulatePixelX>=1.0f) {
			fNoDecimalX = fNoDecimalX + 1;
			acumulatePixelX = acumulatePixelX - 1;
		}
		if (acumulatePixelY >= 1.0f) {
			fNoDecimalY = fNoDecimalY + 1;
			acumulatePixelY = acumulatePixelY - 1;
		}
		Transform.x = (int)fNoDecimalX;
		Transform.y = (int)fNoDecimalY;
	}

	if (fMagVelocity < 10.0f && bCollision) {
		VelocityY = 0;
		VelocityX = 0;
		stable = true;
	}

	
	
	temps.resetTimer();
}

void WormPhysics::SetPixel(int imgS,int imgT, Uint32 X, Uint32 Y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float radi)
{

	ResourceManager::getInstance()->SetPixel(imgS,imgT,X,Y,r,g,b,a,radi);

}


void WormPhysics::checkWormCollision(std::vector<WormPhysics*>*Wroms)
{
	for (size_t i = 0; i < Wroms->size(); i++)
	{
		if (((Transform.x >= Wroms->at(i)->Transform.x) && (Transform.x <= (Wroms->at(i)->Transform.x + Wroms->at(i)->Transform.w)))
			&&
			((Transform.y >= Wroms->at(i)->Transform.y) && (Transform.y <= (Wroms->at(i)->Transform.y + Wroms->at(i)->Transform.h))))
		{
			rebots--;
		}
	}
}

bool WormPhysics::checkCollisionGround(int imgSB, int &npixels)
{
	int contador = 0;

	Uint8* MapArray = ResourceManager::getInstance()->getArrayPixels(imgSB);
	int pitch = ResourceManager::getInstance()->getSurfacePitch(imgSB);
	int bytesPerPixel = ResourceManager::getInstance()->getSurfaceBytesPerPixel(imgSB);
	for (int i = 0; i < 6; i++)
	{
		if (MapArray[(43 + Transform.y + i) * pitch + (28 + Transform.x) * bytesPerPixel + 3] != 0) {
			npixels = contador;
			return true;//
		}
		contador++;
	}
	
	return false;
}

void WormPhysics::offset(Rect* rect, int& xOffset, int& yOffset) {
	xOffset = rect->x;
	yOffset = rect->y;
}

int WormPhysics::FrontVerticlaCollision(int imgSB, bool right)
{
	int contador = 0;
	VerticalCollision.clear();
	VerticalCollision.resize(5);
	for (size_t i = 0; i < VerticalCollision.size(); i++)
	{
		VerticalCollision.at(i) = true;
	}

	//SDL_Surface* auxB = ResourceManager::getInstance()->getGraphicSurfaceByID(imgSB);
	
	Uint8* MapArray = ResourceManager::getInstance()->getArrayPixels(imgSB);
	int pitch = ResourceManager::getInstance()->getSurfacePitch(imgSB);
	int bytesPerPixel = ResourceManager::getInstance()->getSurfaceBytesPerPixel(imgSB);
	int posVector = 0;

	//comprovar que tenim terra davant nostre 3 pixels de dalt a baix
	for (int i = 4; i >= 0; i--)
	{
		if (!right) {

			//0  
			//255 false
			//255 false
			//0   true
			if (MapArray[(40 + i + Transform.y) * pitch + (27 + Transform.x) * bytesPerPixel + 3] != 0) {
				VerticalCollision.at(posVector) = false;
			}
		}
		else {
			if (MapArray[(40 + i + Transform.y) * pitch + (Transform.w - 27 + Transform.x) * bytesPerPixel + 3] != 0) {
				VerticalCollision.at(posVector) = false;
			}
		}
		posVector++;

	}
	



	//Mirem 
	for (int i = VerticalCollision.size()-1; i >= 0 ; i--)
	{
		if (VerticalCollision.at(i) == false) {
			contador++;
		}
	}
	if (contador == 5) {
		return -1;
	}
	else {
		return contador;
	}

	//return 0 == caminar recta
	//return >0 <5 == pujar com a maxim 4 pixels
	//return -1 == pared
	//
	//
}

int WormPhysics::rayCast(int x, int y, int Xclick, int Yclick, std::vector<WormPhysics*>* Worms, int radi, int torn)
{
	int index = -1;
	float modul = sqrt(((Xclick-x)* (Xclick - x)) + ((Yclick - y) * (Yclick - y)));
	int imgS = ResourceManager::getInstance()->loadAndGetGraphicSurfaceID("perlinNoiseTest.png");
	int imgT = ResourceManager::getInstance()->loadAndGetGraphicID("perlinNoiseTest.png");


	Uint8* MapArray = ResourceManager::getInstance()->getArrayPixels(imgS);
	int pitch = ResourceManager::getInstance()->getSurfacePitch(imgS);
	int bytesPerPixel = ResourceManager::getInstance()->getSurfaceBytesPerPixel(imgS);

	Vec2f posicio;
	Vec2f direccio;
	direccio.X = (Xclick - x)/modul;
	posicio.X = x;
	direccio.Y = (Yclick - y)/modul;
	posicio.Y = y;
	bool tocatWorm = false;
	bool tocatGround = false;
	bool forapantalla = false;
	while (!tocatWorm && !forapantalla && !tocatGround) {
		for (size_t i = 0; i < Worms->size(); i++)
		{
			if (i != torn) {
				if ((((int)posicio.X >= Worms->at(i)->Transform.x) && ((int)posicio.X <= (Worms->at(i)->Transform.x + Worms->at(i)->Transform.w)))
					&&
					(((int)posicio.Y >= Worms->at(i)->Transform.y) && ((int)posicio.Y <= (Worms->at(i)->Transform.y + Worms->at(i)->Transform.h))))
				{
					index = i;
					tocatWorm = true;
				}
			}
		}
		//falta mirar lo de abs
		posicio.X += 5 * abs(direccio.X) * (direccio.X / abs(direccio.X));
		posicio.Y += 5 * abs(direccio.Y) * (direccio.Y / abs(direccio.Y));
		
		if ((int)posicio.X > ResourceManager::getInstance()->getGraphicSurfaceByID(imgS)->w || (int)posicio.X < 0) {
			forapantalla = true;
			rebots = 0;
		}
		if ((int)posicio.Y > ResourceManager::getInstance()->getGraphicSurfaceByID(imgS)->h || (int)posicio.Y < 0) {
			forapantalla = true;
			rebots = 0;
		}
		tocatGround = checkCollisionPoints(imgS, (int)posicio.X, (int)posicio.Y);
	}
	rebots = 0;
	Transform.x = (int)posicio.X;
	Transform.y = (int)posicio.Y;


	if (tocatGround) {
		SetPixel(imgS, imgT, (int)posicio.X, (int)posicio.Y, 0, 0, 0, 0, radi);
	}

	return index;

}

void WormPhysics::setUpParabolicTrajectory(float _ax, float _ay) {
	//posar X, Y, ax, ay i despres cridar translet object
	VelocityX = _ax;
	VelocityY = _ay;
}