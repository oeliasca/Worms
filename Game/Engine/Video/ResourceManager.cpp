#include "ResourceManager.h"
#include "Video.h"
ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	SDL_DestroyTexture(mGraphicsVector[it->second]);
	mGraphicsVector[it->second] = NULL;
	mIDMap.erase(file);
	updateFirstFreeSlotGraphic();
}

Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end()) {
		//file no s'ha trobat, l'hem de carregar
		return addGraphic(file);

	}
	else {
		return it->second;
		
	}

	
}

std::string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	std::map<std::string, Sint32>::iterator it;
	for (it = mIDMap.begin(); it != mIDMap.end(); it++)
	{
		if (it->second==ID) {
			return it->first;
		}
	}

	return "";
}

void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	//width = mGraphicsVector[img]->w;
	//height = mGraphicsVector[img]->h;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, &width, &height);
}

void ResourceManager::getGraphicPitch(Sint32 img, int& pitch)
{
	int w;
	int h;
	Uint32 format ;

	SDL_QueryTexture(mGraphicsVector[img], &format, NULL, &w, &h);


	std::cout << (SDL_BITSPERPIXEL(format)/8)*w << std::endl;
	pitch = (SDL_BITSPERPIXEL(format) / 8) * w;
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	int* w = nullptr;
	int* h = nullptr;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, w, h);
	return *w;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	int* w = nullptr;
	int* h = nullptr;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, w, h);
	return *h;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	return mGraphicsVector[ID];
}

int ResourceManager::getGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);

	return it->second;
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetTextureAlphaMod(mGraphicsVector[ID], alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
	std::map<std::string, Sint32>::iterator it;
	for (it= mIDMap.begin(); it != mIDMap.end(); it++)
	{
		std::cout << "File path: " << it->first << std::endl;
	}
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = width;
	rect.h = height;
	SDL_Surface* aux = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(aux, &rect, 0x000000);

	
	SDL_Texture* temp = SDL_CreateTextureFromSurface(Video::getInstance()->gScreen,aux);
	//temp->clip_rect.h = height;
	//temp->clip_rect.w = width;
	
	
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int inited = IMG_Init(flags);
	if ((inited & flags) != flags) {
		return -1;
	}
	if (mFirstFreeSlot != NULL) {
		mIDMap.insert(std::pair<std::string, Sint32>(name, mFirstFreeSlot));
		mGraphicsVector[mFirstFreeSlot] = temp;
		int temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else {
		mIDMap.insert(std::pair<std::string, Sint32>(name, mGraphicsVector.size()));
		mGraphicsVector.push_back(temp);
		return mGraphicsVector.size() - 1;
	}

	return -1;
}

ResourceManager* ResourceManager::getInstance()
{
	if (pInstance == NULL) {
		pInstance = new ResourceManager();
	}
	return pInstance;
}

Sint32 ResourceManager::loadAndGetGraphicTextID(std::string file, SDL_Texture* text)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMapSurface.find(file);
	if (it == mIDMapSurface.end()) {
		//file no s'ha trobat, l'hem de carregar
		return addGraphicText(file,text);

	}
	else {
		return it->second;

	}
}

Sint32 ResourceManager::addGraphicText(std::string file, SDL_Texture* text)
{
	if (mFirstFreeSlot != NULL) {
		mIDMap.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		mGraphicsVector[mFirstFreeSlot] = text;
		int temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else {
		mGraphicsVector.push_back(text);
		mIDMap.insert(std::pair<std::string, Sint32>(file, mGraphicsVector.size() - 1));

		return mGraphicsVector.size() - 1;
	}
}

Uint8* ResourceManager::getArrayPixels(int idSurf)
{
	
	return (Uint8*)getGraphicSurfaceByID(idSurf)->pixels;
}

int ResourceManager::getSurfaceH(int idSurf)
{
	return getGraphicSurfaceByID(idSurf)->h;
}

int ResourceManager::getSurfaceW(int idSurf)
{
	return getGraphicSurfaceByID(idSurf)->w;
}

int ResourceManager::getSurfacePitch(int idSurf)
{
	return getGraphicSurfaceByID(idSurf)->pitch;
}

int ResourceManager::getSurfaceBytesPerPixel(int idSurf)
{
	return getGraphicSurfaceByID(idSurf)->format->BytesPerPixel;
}

SDL_Rect* ResourceManager::getSurfaceClipRect(int idSurf)
{
	return &getGraphicSurfaceByID(idSurf)->clip_rect;
}

Sint32 ResourceManager::loadTextureID(SDL_Texture* texture, const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end()) {
		//file no s'ha trobat, l'hem de carregar
		int aux;
		aux = AddTexture(texture, file);
		SDL_UpdateTexture(texture, NULL, getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file))->pixels, getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file))->pitch);
		return aux;

	}
	else {
		return it->second;

	}
}

Sint32 ResourceManager::loadAndGetGraphicSurfaceID(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMapSurface.find(file);
	if (it == mIDMapSurface.end()) {
		//file no s'ha trobat, l'hem de carregar
		return addGraphicSurface(file);

	}
	else {
		return it->second;

	}
	
	
}

Sint32 ResourceManager::addGraphicSurface(const char* file)
{
	if (mFirstFreeSlotSurface != NULL) {
		mIDMapSurface.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlotSurface));
		mGraphicsSurfaceVector[mFirstFreeSlotSurface] = IMG_Load(file);
		int temp = mFirstFreeSlotSurface;
		mFirstFreeSlotSurface = NULL;
		return temp;
	}
	else {
		mGraphicsSurfaceVector.push_back(IMG_Load(file));
		mIDMapSurface.insert(std::pair<std::string, Sint32>(file, mGraphicsSurfaceVector.size() - 1));

		return mGraphicsSurfaceVector.size() - 1;
	}
}

SDL_Surface* ResourceManager::getGraphicSurfaceByID(Sint32 ID)
{
	return mGraphicsSurfaceVector[ID];
}

void ResourceManager::removeGraphicSurface(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMapSurface.find(file);
	SDL_FreeSurface(mGraphicsSurfaceVector[it->second]);
	mGraphicsSurfaceVector[it->second] = NULL;
	mIDMapSurface.erase(file);
	updateFirstFreeSlotGraphicSurface();
}

Sint32 ResourceManager::createSurfaceFromPixels(const char* file, float* pixels,int maxValue,int w, int h)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMapSurface.find(file);
	if (it == mIDMapSurface.end()) {
		//file no s'ha trobat, l'hem de carregar
		return addGraphicFromPixels(file, pixels, maxValue, w, h);

	}
	else {
		return it->second;
	}
}

void ResourceManager::resetSurfaceFromPixels(const char* file, float* pixels, int maxValue, int w, int h)
{
	SDL_Surface* surf = getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file));
	SDL_LockSurface(surf);
	Uint8* pixelArray = (Uint8*)surf->pixels;
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 0] = 0;
			pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 1] = 0;
			pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 2] = 0;
			pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 3] = 0;
		}
	}

	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			//Mirem de pintar per sota la linia del Perlin noise
			if ((h - (int)pixels[j]) < i) {

				int r = 255;
				int g = 255;
				int b = 255;
				int a = 0;
				int fluctuation = rand() % 5;
				int sinLine = 7 * sinf(j * sinf(rand() % 30));
				int sinEvaluation = 20 * sinf(j * 0.01);

				int evaluatePixel = (h - i) + sinLine - fluctuation - sinEvaluation;


				if (evaluatePixel < maxValue && evaluatePixel >(maxValue * 0.83)) {
					r = r;
					g = g;
					b = b;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.83) && evaluatePixel > (maxValue * 0.67)) {
					r = 204;
					g = 255;
					b = 255;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.67) && evaluatePixel > (maxValue * 0.51)) {
					r = 102;
					g = 255;
					b = 102;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.51) && evaluatePixel > (maxValue * 0.34)) {
					r = 128;
					g = 255;
					b = 0;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.34) && evaluatePixel > (maxValue * 0.18)) {
					r = 204;
					g = 204;
					b = 0;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.18)) {
					r = 153;
					g = 76;
					b = 0;
					a = 255;
				}


				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 0] = r;
				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 1] = g;
				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 2] = b;
				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 3] = a;
			}

		}
	}

	SDL_UnlockSurface(surf);

	SDL_UpdateTexture(getGraphicByID(loadAndGetGraphicID(file)), NULL, pixelArray, surf->pitch);

}

Sint32 ResourceManager::addGraphicFromPixels(const char* file, float* pixels,int maxValue,int w, int h)
{
	SDL_Surface* surf;
	surf = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
	if (surf == NULL) {
		SDL_Log("SDL_CreateRGBSurfaceWithFormat() failed: %s", SDL_GetError());
		exit(1);
	}
	SDL_LockSurface(surf);
	Uint8* pixelArray = (Uint8*)surf->pixels;
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			//Mirem de pintar per sota la linia del Perlin noise
			if ((h - (int)pixels[j]) < i) {

				int r = 255;
				int g = 255;
				int b = 255;
				int a = 0;
				int fluctuation = rand() % 5;
				int sinLine = 7*sinf(j*sinf(rand() % 30));
				int sinEvaluation = 20 * sinf(j*0.01);

				int evaluatePixel = (h - i) + sinLine - fluctuation - sinEvaluation;


				if (evaluatePixel < maxValue && evaluatePixel > (maxValue * 0.83)) {
					r = r;
					g = g;
					b = b;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.83) && evaluatePixel > (maxValue * 0.67)) {
					r = 204;
					g = 255;
					b = 255;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.67) && evaluatePixel > (maxValue * 0.51)) {
					r = 102;
					g = 255;
					b = 102;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.51) && evaluatePixel > (maxValue * 0.34)) {
					r = 128;
					g = 255;
					b = 0;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.34) && evaluatePixel > (maxValue * 0.18)) {
					r = 204;
					g = 204;
					b = 0;
					a = 255;
				}
				else if (evaluatePixel <= (maxValue * 0.18)) {
					r = 153;
					g = 76;
					b = 0;
					a = 255;
				}


				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 0] = r;
				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 1] = g;
				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 2] = b;
				pixelArray[i * surf->pitch + j * surf->format->BytesPerPixel + 3] = a;
			}
			


		}
	}
	
	SDL_UnlockSurface(surf);

	if (mFirstFreeSlotSurface != NULL) {
		mIDMapSurface.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlotSurface));
		mGraphicsSurfaceVector[mFirstFreeSlotSurface] = surf;
		int temp = mFirstFreeSlotSurface;
		mFirstFreeSlotSurface = NULL;
		return temp;
	}
	else {
		mGraphicsSurfaceVector.push_back(surf);
		mIDMapSurface.insert(std::pair<std::string, Sint32>(file, mGraphicsSurfaceVector.size() - 1));

		return mGraphicsSurfaceVector.size() - 1;
	}
}

Sint32 ResourceManager::createTextureFromPixels(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end()) {
		//file no s'ha trobat, l'hem de carregar
		return addGraphicTextureFromPixels(file);

	}
	else {
		return it->second;

	}
}

Sint32 ResourceManager::addGraphicTextureFromPixels(const char* file)
{
	SDL_Texture* ObjectTexture = SDL_CreateTexture(Video::getInstance()->gScreen, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file))->w, getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file))->h);
	SDL_SetTextureBlendMode(ObjectTexture, SDL_BLENDMODE_BLEND);

	return loadTextureID(ObjectTexture, file);

}

void ResourceManager::SetPixel(int imgS, int imgT, Uint32 X, Uint32 Y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float radi)
{
	SDL_Surface* aux = ResourceManager::getInstance()->getGraphicSurfaceByID(imgS);

	SDL_LockSurface(aux);
	Uint8* pixelArray = (Uint8*)aux->pixels;

	for (size_t i = 0; i < aux->h; i++)
	{
		for (size_t j = 0; j < aux->w; j++)
		{
			if (sqrt((j - X) * (j - X) + (i - Y) * (i - Y)) <= radi) {
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 0] = r;
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 1] = g;
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 2] = b;
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 3] = a;
			}
		}
	}
	SDL_UnlockSurface(aux);
	SDL_UpdateTexture(ResourceManager::getInstance()->getGraphicByID(imgT), NULL, pixelArray, aux->pitch);
}

void ResourceManager::SetPixelsToColor(int imgS, int imgT, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Surface* aux = ResourceManager::getInstance()->getGraphicSurfaceByID(imgS);

	SDL_LockSurface(aux);
	Uint8* pixelArray = (Uint8*)aux->pixels;

	for (size_t i = 0; i < aux->h; i++)
	{
		for (size_t j = 0; j < aux->w; j++)
		{
			pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 0] = r;
			pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 1] = g;
			pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 2] = b;
			pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 3] = a;
		}
	}
	SDL_UnlockSurface(aux);
	SDL_UpdateTexture(ResourceManager::getInstance()->getGraphicByID(imgT), NULL, pixelArray, aux->pitch);
}

void ResourceManager::SetSinglePixel(int imgS, int imgT, Uint32 X, Uint32 Y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float radi)
{
	SDL_Surface* aux = ResourceManager::getInstance()->getGraphicSurfaceByID(imgS);

	SDL_LockSurface(aux);
	Uint8* pixelArray = (Uint8*)aux->pixels;

	for (size_t i = Y - (int)radi; i < Y + (int)radi; i++)
	{
		for (size_t j = X - (int)radi; j < X - (int)radi; j++)
		{
			if (sqrt((j - X) * (j - X) + (i - Y) * (i - Y)) <= radi) {
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 0] = r;
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 1] = g;
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 2] = b;
				pixelArray[i * aux->pitch + j * aux->format->BytesPerPixel + 3] = a;
			}
		}
	}
	SDL_UnlockSurface(aux);
	SDL_UpdateTexture(ResourceManager::getInstance()->getGraphicByID(imgT), NULL, pixelArray, aux->pitch);
}

Uint32 ResourceManager::updateFirstFreeSlotGraphicSurface()
{
	for (int i = 0; i < mGraphicsSurfaceVector.size(); i++)
	{
		if (mGraphicsSurfaceVector[i] == NULL) {
			return i;
		}
	}
}

ResourceManager::ResourceManager()
{
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	//std::map<std::string, Sint32>::iterator it;
	

	//int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	//int inited = IMG_Init(flags);
	//if ((inited & flags) != flags) {
	//	return -1;
	//}
	if (mFirstFreeSlot!=NULL) {
		mIDMap.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		mGraphicsVector[mFirstFreeSlot]=IMG_LoadTexture(Video::getInstance()->gScreen,file);
		int temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else {
		mGraphicsVector.push_back(IMG_LoadTexture(Video::getInstance()->gScreen, file));
		mIDMap.insert(std::pair<std::string, Sint32>(file, mGraphicsVector.size()-1));
		
		return mGraphicsVector.size() - 1;
	}
	
}

Sint32 ResourceManager::AddTexture(SDL_Texture* texture, const char* file)
{
	if (mFirstFreeSlot != NULL) {
		mIDMap.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		mGraphicsVector[mFirstFreeSlot] = texture;
		int temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else {
		mGraphicsVector.push_back(texture);
		mIDMap.insert(std::pair<std::string, Sint32>(file, mGraphicsVector.size() - 1));

		return mGraphicsVector.size() - 1;
	}
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	for (int i = 0; i < mGraphicsVector.size(); i++)
	{
		if (mGraphicsVector[i] == NULL) {
			return i;
		}
	}
	
}


/*
Sint32 ResourceManager::loadTextureID(SDL_Texture* texture, const char* file)
{

	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end()) {
		//file no s'ha trobat, l'hem de carregar
		int aux;
		aux = AddTexture(texture, file);
		SDL_UpdateTexture(texture, NULL, getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file))->pixels, getGraphicSurfaceByID(loadAndGetGraphicSurfaceID(file))->pitch);
		return aux;

	}
	else {
		return it->second;

	}

}
Sint32 ResourceManager::AddTexture(SDL_Texture* texture, const char* file)
{
	if (mFirstFreeSlot != NULL) {
		mIDMap.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		mGraphicsVector[mFirstFreeSlot] = texture;
		int temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else {
		mGraphicsVector.push_back(texture);
		mIDMap.insert(std::pair<std::string, Sint32>(file, mGraphicsVector.size() - 1));

		return mGraphicsVector.size() - 1;
	}

}
*/
