#include "LoadingState.h"
#include "GameStateManager.h"
#include <ctime>
#include <iostream>

LoadingState LoadingState::m_LoadingState;

LoadingState::LoadingState()
{
}

void LoadingState::init(GameStateManager* gsm) {

	if (text1 == nullptr) {
		text1 = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_bar_grey.png").c_str());
	}

	if (text2 == nullptr) {
		text2 = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_bar_green.png").c_str());
	}

	if (textBackground == nullptr) {
		textBackground = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\campfire.jpg").c_str());
	}

	if (textTime == nullptr) {
		textTime = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\frameTEMP.png").c_str());
		textCircle = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\circleTEMP.png").c_str());

		textTimeSec = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\frameTEMP.png").c_str());
		textCircleSec = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\circleTEMP.png").c_str());
	}

	this->degrees = 0;

	rectTime.x = 100;
	rectTime.y = 100;
	rectTime.w = 160;
	rectTime.h = 160;
	rectCircle.x = 105;
	rectCircle.y = 105;
	rectCircle.w = 150;
	rectCircle.h = 150;

	
	rectTimeSec.x = 100;
	rectTimeSec.y = 300;
	rectTimeSec.w = 160;
	rectTimeSec.h = 160;
	rectCircleSec.x = 105;
	rectCircleSec.y = 305;
	rectCircleSec.w = 150;
	rectCircleSec.h = 150;

	if(textAdvertisement == nullptr) {

		char* filenames[]={"basicfit.png", "bosch.png", "dolcegusto.png", "electroworld.png", "exact.png", "kijk.png", "mediamarkt.png", "mediamarkt_2.png", "mediamarkt_3.png", "nissan.png", "postnl.png", "t_mobile_2.png", "t_mobile_3.png", "t-mobile.png", "tele2.png", "ziggo.png"};

		srand(time(NULL));
		int random = rand() % 16;

		std::cout << (RESOURCEPATH + "Advertisement\\" + filenames[random]).c_str() << std::endl;

		textAdvertisement = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Advertisement\\" + filenames[random]).c_str());
	}

	rect1.x = ScreenWidth / 3;
	rect1.y = ScreenHeight / 2 - ScreenHeight / 40;
	rect1.h = ScreenHeight / 20;
	rect1.w = ScreenWidth / 3;


	rect2.x = ScreenWidth / 3;
	rect2.y = ScreenHeight / 2 - ScreenHeight / 40;
	rect2.h = ScreenHeight / 20;
	rect2.w = 0;

	rectBackground.x = 0;
	rectBackground.y = 0;
	rectBackground.w = ScreenWidth;
	rectBackground.h = ScreenHeight;

	int advWidth = 0;
	int advHeight = 0;
	SDL_QueryTexture(textAdvertisement, nullptr, nullptr, &advWidth, &advHeight);

	rectAdvertisement.x = (ScreenWidth - advWidth) / 2;
	rectAdvertisement.y = ScreenHeight - advHeight - 20;
	rectAdvertisement.w = advWidth;
	rectAdvertisement.h = advHeight;
}

void LoadingState::setPercentage(int percentage)
{
	this->percentage = percentage;
}

void LoadingState::cleanup() 
{
	SDL_DestroyTexture(textBackground);
	SDL_DestroyTexture(textAdvertisement);
	SDL_DestroyTexture(text1);
	SDL_DestroyTexture(text2);

	textBackground = nullptr;
	textAdvertisement = nullptr;
	text1 = nullptr;
	text2 = nullptr;
}

void LoadingState::pause() 
{
}

void LoadingState::resume() 
{
}

void LoadingState::handleEvents(SDL_Event mainEvent) 
{	
}

void LoadingState::update(double dt) 
{
}

void LoadingState::draw() 
{	
	GameStateManager::Instance()->sdlInitializer->clearScreen();
	rect2.w = ((ScreenWidth / 3) / 100) * this->percentage;



	//Background
	GameStateManager::Instance()->sdlInitializer->drawTexture(textBackground, &rectBackground, NULL);

	//Loadingbar
	GameStateManager::Instance()->sdlInitializer->drawTexture(text1, &rect1, NULL);
	GameStateManager::Instance()->sdlInitializer->drawTexture(text2, &rect2, NULL);
	
	GameStateManager::Instance()->sdlInitializer->drawTexture(textCircle, &rectCircle, NULL);
	SDL_RenderCopyEx(	GameStateManager::Instance()->sdlInitializer->getRenderer(),
		textTime,
		NULL,
		&rectTime,
		this->degrees,
		NULL,
		SDL_FLIP_NONE);

	SDL_RenderCopyEx(	GameStateManager::Instance()->sdlInitializer->getRenderer(),
		textCircleSec,
		NULL,
		&rectCircleSec,
		this->degrees,
		NULL,
		SDL_FLIP_NONE);
	GameStateManager::Instance()->sdlInitializer->drawTexture(textTimeSec, &rectTimeSec, NULL);

	this->degrees += 5;

	//Advertisement	
	GameStateManager::Instance()->sdlInitializer->drawTexture(textAdvertisement, &rectAdvertisement, NULL);

	//Loading text
	GameStateManager::Instance()->sdlInitializer->drawText(std::string("Loading game"), ScreenWidth / 2 - 100, (ScreenHeight / 2) - (ScreenHeight / 30) - 100, 200, 50);

	//Procent text
	GameStateManager::Instance()->sdlInitializer->drawText(std::string(std::to_string(this->percentage) + " %"), ScreenWidth / 2 - 25, ScreenHeight / 2 - ScreenHeight / 35, 50, ScreenHeight / 20);

	GameStateManager::Instance()->sdlInitializer->drawScreen();
}

LoadingState::~LoadingState(void)
{
	this->cleanup();


	//delete camera;
	//delete mec;
	//delete mapLoader;
	//delete text1/ text2

}