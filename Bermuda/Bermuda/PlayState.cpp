#include "PlayState.h"
#include "MenuState.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "PauseState.h"
#include <iostream>
#include <algorithm>
#include "Windows.h"
#include <thread>
#include "Items.h"
#include "NPCFactory.h"
#include "ItemFactory.h"
#include "ObjectFactory.h"
#include "GameOverState.h"
#include <stdio.h>


PlayState PlayState::m_PlayState;

bool PlayState::drawableSortFunction(DrawableEntity* one, DrawableEntity* two) { return (one->getY() + one->getHeight() < two->getY() + two->getHeight()); }

PlayState::PlayState()
{
}

void PlayState::init(GameStateManager *gsm) {
	this->gsm = gsm;

	this->gameOver = false;
	this->showCol = false;
	this->showInter = false;
	this->showSpawnArea = false;
	this->showDayLight = true;
	this->timesUpdate = 0;

	GameStateManager::Instance()->setSpeedMultiplier(1);
	GameTimer::Instance()->init();
	imgLoader = new ImageLoader(GameStateManager::Instance()->sdlInitializer->getRenderer());
	NPCFactory::Instance()->loadNPCTileSets(imgLoader);
	ItemFactory::Instance()->loadItemTileSets(imgLoader);
	ObjectFactory::Instance()->loadObjectTileSets(imgLoader);

	mec = new MainEntityContainer();
	mapLoader = new MapLoader();
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());

	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), camera);

	SoundLoader::Instance()->playGameMusic();

	nightLayer = new NightLayer();
	gameSaver = new GameSaver();

	GameStateManager::Instance()->flushEvents();
}


void PlayState::loadGame()
{
	gameSaver->loadGame(this->fileToLoad);
}

void PlayState::setFileToLoad(std::string fileName)
{
	this->fileToLoad = fileName;
}

MainEntityContainer* PlayState::getMainEntityContainer()
{
	return this->mec;
}

void PlayState::pause() {
	if (this->p != nullptr)
	{
		this->p->moveClick = true;
		this->p->resetMovement();
	}
}

void PlayState::resume() {

}


void PlayState::handleEvents(SDL_Event mainEvent) {

	//Retrieve input
	int x = 0;
	int y = 0;
	switch (mainEvent.type) {

	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		if (mainEvent.button.button == SDL_BUTTON_LEFT) {

			if (p->getInventory()->clicked(x, y, "select", p) || p->getCraftingSystem()->isOpen()) {
				//std::cout << "Clicked at: " << x << ":" << y << std::endl;
				p->getCraftingSystem()->clicked(x,y,"yolo", p);
			} else {
				p->destX = x + this->camera->getX();
				p->destY = y + this->camera->getY();
				p->resetMovement();
				p->moveClick = true;
			}
		}
		else if (mainEvent.button.button == SDL_BUTTON_RIGHT) {
			if (p->getInventory()->clicked(x, y, "use", p)) {

			}
		}
		break;
	case SDL_MOUSEWHEEL:
		if (mainEvent.wheel.y > 0) {
			p->getInventory()->decrementSelectedIndex();
		}
		else if (mainEvent.wheel.y < 0){
			p->getInventory()->incrementSelectedIndex();
		}
		//p->changeAnimationOnInventorySelection();
		break;
	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			//Arrow left key
			p->resetMovement();
			p->moveClick = false;
			p->movingRight = false;
			p->movingLeft = true;
			break;

		case SDLK_RIGHT:
		case SDLK_d:
			//Arrow right key
			p->resetMovement();
			p->moveClick = false;
			p->movingLeft = false;
			p->movingRight = true;
			break;
		case SDLK_UP:
		case SDLK_w:
			//Arrow up key
			p->resetMovement();
			p->moveClick = false;
			p->movingDown = false;
			p->movingUp = true;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			//Arrow down key
			p->resetMovement();
			p->moveClick = false;
			p->movingUp = false;
			p->movingDown = true;
			break;
		/*case SDLK_LSHIFT:
			//Sprint
			p->sprinting = true;
			break;*/
		case SDLK_e:
			p->getInventory()->interactCurrent(p);
			break;
		case SDLK_q:
			p->getInventory()->dropCurrent();
			break;
		case SDLK_z:
			p->getInventory()->decrementSelectedIndex();
			break;
		case SDLK_c:
			p->getInventory()->incrementSelectedIndex();
			break;
		case SDLK_t:
			p->getCraftingSystem()->toggleCraftMenu();
			break;
		case SDLK_0:
		case SDLK_KP_0:
			p->getInventory()->setSelectedIndex(9);
			break;
		case SDLK_1:
		case SDLK_2:
		case SDLK_3:
		case SDLK_4:
		case SDLK_5:
		case SDLK_6:
		case SDLK_7:
		case SDLK_8:
		case SDLK_9:
			p->getInventory()->setSelectedIndex(mainEvent.key.keysym.sym - 49);
			break;
		case SDLK_KP_1:
		case SDLK_KP_2:
		case SDLK_KP_3:
		case SDLK_KP_4:
		case SDLK_KP_5:
		case SDLK_KP_6:
		case SDLK_KP_7:
		case SDLK_KP_8:
		case SDLK_KP_9:
			p->getInventory()->setSelectedIndex(mainEvent.key.keysym.sym - 1073741913);
			break;
		/*case SDLK_F1:
			p->toggleGodMode();
			break;
		case SDLK_F2:
			this->showCol = !this->showCol;
			break;
		case SDLK_F3:
			this->showInter = !this->showInter;
			break;
		case SDLK_F4:
			this->showSpawnArea = !this->showSpawnArea;
			break;*/
		case SDLK_F9:
			GameStateManager::Instance()->toggleHelpEnabled();
			break;
		/*case SDLK_F7:
			this->showDayLight = !this->showDayLight;
			break;
		case SDLK_F11:
			//Enable collision
			p->setCollisionHeight(10);
			p->setCollisionWidth(24);
			p->setCollisionX(20);
			p->setCollisionY(52);
			break;
		case SDLK_F10:
			//Disable collision
			p->setCollisionHeight(0);
			p->setCollisionWidth(0);
			p->setCollisionX(-10000);
			p->setCollisionY(-10000);
			break;*/
		case SDLK_SPACE:
			p->interaction = true;
			//p->interact();
			break;
		default:
			break;

		case SDLK_ESCAPE:
			if (p->getCraftingSystem()->isOpen()) {
				p->getCraftingSystem()->toggleCraftMenu();
				break;
			}
			//Go to pause state on 'Escape'
			//TODO: methode voor deze escape klik aanmaken?
			gameSaver->saveGame();
			this->gsm->pushGameState(PauseState::Instance());
			break;
		case SDLK_i:
			//Open inventory
			this->p->getInventory()->toggleInventory();
			break;
		}
		break;

	case SDL_KEYUP:
		switch (mainEvent.key.keysym.sym) {
		case SDLK_LEFT:
		case SDLK_a:
			p->StopAnimation();
			p->moveClick = false;
			p->movingLeft = false;
			break;
		case SDLK_LSHIFT:
			p->sprinting = false;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			p->StopAnimation();
			p->moveClick = false;
			p->movingRight = false;
			break;

		case SDLK_UP:
		case SDLK_w:
			p->StopAnimation();
			p->moveClick = false;
			p->movingUp = false;
			break;

		case SDLK_DOWN:
		case SDLK_s:
			p->StopAnimation();
			p->moveClick = false;
			p->movingDown = false;
			break;

		case SDLK_SPACE:
			p->interaction = false;
			p->setCorrectToolSelected(false);
			p->StopAnimation();
			break;

		}
		break;
	}
}

void PlayState::update(double dt) {
	mec->getDestroyContainer()->destroyAllEntities();

	//.... eerste 3 keer doen we dit niet. probleem met loadingstate..
	//Update gametimer
	if (this->timesUpdate > 2)
	{
		GameTimer::Instance()->updateGameTime(GameStateManager::Instance()->getUpdateLength());
	}
	else
	{
		this->timesUpdate++;
	}

	//Update all respawnable entities
	for (size_t i = 0; i < mec->getRespawnContainer()->getContainer()->size(); i++) {
		mec->getRespawnContainer()->getContainer()->at(i)->update(dt);
	}

	this->updateVisibleEntities(dt);
	this->updateMediumAreaEntities(dt);

	this->updatePlayerDarkness();

	if (gameOver)
	{
		//Delete saved game
		remove((SAVEPATH + this->gameSaver->getCurrentSaveFile()).c_str());

		//Save stuff for graveyard
		Graveyard graveyard;
		GraveyardEntry* entry = new GraveyardEntry;
		entry->daysSurvived = GameTimer::Instance()->getDaysSurvived();	//get days player survived

		time_t time_create = time(NULL);
		struct tm time_info;
		localtime_s(&time_info, &time_create);

		entry->dayDied = time_info.tm_mday;
		entry->monthDied = (time_info.tm_mon + 1);
		entry->yearDied = (time_info.tm_year + 1900);

		graveyard.addToGraveyard(entry);

		//Switch to game over state
		GameStateManager::Instance()->changeGameState(GameOverState::Instance());
	}

}

void PlayState::updateVisibleEntities(double dt)
{
	//Update all animating entities
	//Calculate begin and end chunks for the camera (+1 and -1 to make it just a little bigger than the screen)
	int beginChunkX = floor(camera->getX() / mec->getChunkSize()) - 1;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mec->getChunkSize()) + 1;
	int beginChunkY = floor(camera->getY() / mec->getChunkSize()) - 1;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mec->getChunkSize()) + 1;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			//animating entities
			std::vector<AnimatingEntity*>* vec = this->mec->getAnimatingContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (AnimatingEntity* e : *vec)
				{
					e->animate(dt);
				}
			}
		}
	}
}

void PlayState::updateMediumAreaEntities(double dt)
{
	//Update all spawnpoints and moving entities
	//Calculate begin and end chunks for the camera (+5 and -5 to make it bigger than the screen)
	int beginChunkX = floor(camera->getX() / mec->getChunkSize()) - 5;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mec->getChunkSize()) + 5;
	int beginChunkY = floor(camera->getY() / mec->getChunkSize()) - 5;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mec->getChunkSize()) + 5;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			//Spawnpoints
			std::vector<Spawnpoint*>* spawnpoints = this->mec->getSpawnpointContainer()->getChunk(i, j);
			if (spawnpoints != nullptr)
			{
				for (Spawnpoint* e : *spawnpoints)
				{
					e->update();
				}
			}

			//Moving entities
			std::vector<MovableEntity*>* movingEntities = this->mec->getMovableContainer()->getChunk(i, j);
			if (movingEntities != nullptr && movingEntities->size() > 0)
			{
				//Copy of container so moving entities can change chunks while we loop through them.
				std::vector<MovableEntity*> copyMovingEntities = std::vector<MovableEntity*>(*movingEntities);
				for (MovableEntity* e : copyMovingEntities)
				{
					e->update(dt);
				}
			}
		}
	}
}

void PlayState::draw()
{
	//Calculate begin and end chunks for the interact check (+1 and -1 to make it a little bigger thent he current chunk)
	int beginChunkX = p->getChunkX() - 1;
	int endChunkX = p->getChunkX() + 1;
	int beginChunkY = p->getChunkY() - 1;
	int endChunkY = p->getChunkY() + 1;

	int playerOffsetX = p->getX() + (p->getWidth() / 2);
	//De -7 wordt gebruikt omdat het plaatje niet helemaal klopt. In de breedte staat de speler idd precies in het midden van het plaatje. In de hoogte niet...
	int playerOffsetY = p->getY() + (p->getHeight() / 2) +7;

	double diff = 1000;
	InteractableEntity* closestEntity = nullptr;

	//Loop through all chunks
	for(int i = beginChunkY; i <= endChunkY; i++) {
		for(int j = beginChunkX; j <= endChunkX; j++) {
			std::vector<InteractableEntity*>* vec = PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->getChunk(i, j);
			if(vec != nullptr) {
				for(InteractableEntity* e : *vec) {
					
					e->setHighlighted(false);
					if((playerOffsetX >= (e->getX() + e->getInteractStartX()) && (playerOffsetX <= (e->getX() + e->getInteractStartX() + e->getInteractWidth()))) && 
						(playerOffsetY >= (e->getY() + e->getInteractStartY()) && playerOffsetY <= (e->getY() + e->getInteractStartY() + e->getInteractHeight())))
					{
						double centerX = ((e->getX() + e->getInteractStartX()) + (e->getX() + e->getInteractStartX() + e->getInteractWidth())) /2;
						double centerY = ((e->getY() + e->getInteractStartY()) + (e->getY() + e->getInteractStartY() + e->getInteractHeight())) / 2;

						double diffX = centerX - playerOffsetX;
						double diffY = centerY - playerOffsetY;

						if (diffX < 0) {
							diffX = -diffX;
						}

						if (diffY < 0) {
							diffY = -diffY;
						}

						if (diffX + diffY < diff) {
							diff = diffX + diffY;
							closestEntity = e;
						}
					}
				}
				
			}
		}
	}

	if (closestEntity != nullptr) {
		closestEntity->canInteract(p);
		closestEntity->setHighlighted(true);
	}

	//Calculate begin and end chunks for the camera (+1 and -1 to make it a little bigger then the screen)
	beginChunkX = floor(camera->getX() / mec->getChunkSize()) - 1;
	endChunkX = floor((camera->getX() + camera->getWidth()) / mec->getChunkSize()) + 1;
	beginChunkY = floor(camera->getY() / mec->getChunkSize()) - 1;
	endChunkY = floor((camera->getY() + camera->getHeight()) / mec->getChunkSize()) + 1;

	std::vector<DrawableEntity*> drawableVector;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			//Background
			std::vector<DrawableEntity*>* vec = this->mec->getBackgroundContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (DrawableEntity* e : *vec)
				{
					e->draw(camera, this->gsm->sdlInitializer->getRenderer());

					//Draw collision area
					if (this->showCol)
					{
						//TEMP draw collision area
						CollidableEntity* ce = dynamic_cast<CollidableEntity*>(e);
						if (ce != NULL)
						{
							ce->drawCollidableArea();
						}
					}
				}
			}
			//Objecten
			vec = this->mec->getDrawableContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (DrawableEntity* e : *vec)
				{
					drawableVector.push_back(e);
				}
			}
		}
	}

	//Draw spawnpoint area
	if (this->showSpawnArea)
	{
		//Loop through all chunks
		for (int i = beginChunkY; i <= endChunkY; i++)
		{
			for (int j = beginChunkX; j <= endChunkX; j++)
			{
				std::vector<Spawnpoint*>* vec = this->mec->getSpawnpointContainer()->getChunk(i, j);
				if (vec != nullptr)
				{
					for (Spawnpoint* sp : *vec)
					{
						sp->drawSpawnpointArea();
					}
				}
			}
		}
	}

	//Sort drawable object vector
	std::sort(drawableVector.begin(), drawableVector.end(), PlayState::drawableSortFunction);

	//Draw sorted object vector
	for (DrawableEntity* e : drawableVector)
	{
		e->draw(camera, this->gsm->sdlInitializer->getRenderer());
		if (e->getHighlighted()) {
			dynamic_cast<InteractableEntity*>(e)->highlight();
		}
		//Draw interactable area
		if (this->showInter)
		{
			InteractableEntity* ie = dynamic_cast<InteractableEntity*>(e);
			if (ie != NULL)
			{
				ie->drawInteractableArea();
			}
		}

		//Draw collision area
		if (this->showCol)
		{
			//TEMP draw collision area
			CollidableEntity* ce = dynamic_cast<CollidableEntity*>(e);
			if (ce != NULL)
			{
				ce->drawCollidableArea();
			}
		}
	}


	if (showDayLight && GameTimer::Instance()->getPercentage() >= 65 || GameTimer::Instance()->getPercentage() <= 10)
	{
		nightLayer->draw(camera, mec);
	}

	if (this->p->getInventory()->isOpen()) {
		this->p->getInventory()->draw();
		this->p->drawStats();
	}

	//Draw timer
	GameTimer::Instance()->draw();

	p->getCraftingSystem()->draw();


}

void PlayState::updatePlayerDarkness()
{
	double dayP = GameTimer::Instance()->getPercentage();

	if (dayP >= 90)	p->setWithinDarkness(true);
	else p->setWithinDarkness(false);

	//Calculate begin and end chunks for the camera (+1 and -1 to make it a little bigger then the screen)
	int beginChunkX = floor(camera->getX() / mec->getChunkSize()) - 1;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mec->getChunkSize()) + 1;
	int beginChunkY = floor(camera->getY() / mec->getChunkSize()) - 1;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mec->getChunkSize()) + 1;

	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			// Light entities
			std::vector<LightEntity*>* lightEntities = this->mec->getLightContainer()->getChunk(i, j);
			if (lightEntities != nullptr && lightEntities->size() > 0)
			{
				//Copy of container so moving entities can change chunks while we loop through them.
				std::vector<LightEntity*> copyLightEntities = std::vector<LightEntity*>(*lightEntities);
				for (LightEntity* e : copyLightEntities)
				{
					if (dayP >= 90)
					{
						double diffX = p->getX() - e->getX();
						double diffY = p->getY() - e->getY();

						double distanceFromLight = sqrt((diffX * diffX) + (diffY * diffY));
						//std::cout << "distance: " << distanceFromLight << std::endl;

						if (distanceFromLight <= (e->getDiameter() / 2))
						{
							if (e->getShining() == true) p->setWithinDarkness(false);
						}
					}
				}
			}
		}
	}
}

void PlayState::setGameOver(bool gameOver)
{
	this->gameOver = gameOver;
}

Player* PlayState::getPlayer()
{
	return this->p;
}

Camera* PlayState::getCamera()
{
	return this->camera;
}

ImageLoader* PlayState::getImageLoader()
{
	return imgLoader;
}

void PlayState::cleanup() {
	std::cout << "deleting playstate" << endl;
	GameTimer::Instance()->cleanUp();
	delete nightLayer;
	delete gameSaver;
	delete p;
	delete camera;
	delete mapLoader;
	delete mec;
	delete imgLoader;

	nightLayer = nullptr;
	gameSaver = nullptr;
	p = nullptr;
	camera = nullptr;
	mapLoader = nullptr;
	mec = nullptr;
	imgLoader = nullptr;
}

PlayState::~PlayState()
{
	this->cleanup();
}
