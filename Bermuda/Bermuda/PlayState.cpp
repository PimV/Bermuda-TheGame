#include "PlayState.h"
#include "MenuState.h"
#include "GameStateManager.h"
#include "ActionContainer.h"
#include "PauseState.h"
#include <iostream>
#include <algorithm>
#include "Windows.h" 
#include "Item.h"
#include <thread>
#include "ToolAxe.h"
#include "ItemCarrot.h"
#include "DAYPART.h"
#include "Items.h"
#include "Consumable.h"
#include "Equipable.h"

#include "PARTICLETYPES.h"

//TEMPORARY AXE SPAWN:
#include "Axe.h"
#include "Pickaxe.h"

PlayState PlayState::m_PlayState;

//Needed for vector sort
bool PlayState::drawableSortFunction(DrawableEntity* one, DrawableEntity* two) { return (one->getY() + one->getHeight() < two->getY() + two->getHeight()); }

PlayState::PlayState(void)
{
}

void PlayState::init(GameStateManager *gsm) {
	this->gsm = gsm;
	GameStateManager::Instance()->setSpeedMultiplier(1);
	this->ready = false;
	this->showCol = false;
	this->showInter = false;
	this->showSpawnArea = false;
	this->timesUpdate = 0;


	mec = new MainEntityContainer();
	mapLoader = new MapLoader(this->gsm, mec);
	mapLoader->loadMap();
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());
	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera);
	this->p->getInventory()->toggleInventory();
	//TEMPORARY AXE SPAWN:
	new Axe(9001, p->getX() - 50, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Items\\ToolAxe.png", 22, 27)));
	new Pickaxe(9002, p->getX()  + 90, p->getY(), mapLoader->getChunkSize(), mec, gsm->getImageLoader()->getMapImage(gsm->getImageLoader()->loadTileset("Items\\ToolPickaxe.png",32, 32)));

	GameTimer::Instance()->init();
	SoundLoader::Instance()->playGameMusic();
	this->ready = true;

	
	//pEngine = new ParticleEngine(ScreenWidth / 2, ScreenHeight / 2, PARTICLETYPES::SMOKE);
	pEngine = new ParticleEngine(400,400, PARTICLETYPES::SMOKE);
}

MainEntityContainer* PlayState::getMainEntityContainer()
{
	return this->mec;
}

void PlayState::cleanup() {
	GameTimer::Instance()->cleanUp();
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
	if (!ready) {
		return;
	}
	//p->handleEvents();
	//Process Input

	//Retrieve input
	int x, y;
	switch (mainEvent.type) {

	case SDL_MOUSEBUTTONDOWN:
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (mainEvent.button.button == SDL_BUTTON_LEFT) {
			if (p->getInventory()->clicked(x,y, "select", p)) {
			} else {
			p->destX = x + this->camera->getX();
			p->destY = y + this->camera->getY();
			p->resetMovement();
			p->moveClick = true;
		}
		} else if (mainEvent.button.button == SDL_BUTTON_RIGHT) {
			if (p->getInventory()->clicked(x, y, "use", p)) {

			}
		}
		break;
	case SDL_MOUSEWHEEL: 
		if (mainEvent.wheel.y > 0) {
			p->getInventory()->incrementSelectedIndex();
		} else if (mainEvent.wheel.y < 0){
			p->getInventory()->decrementSelectedIndex();
		}

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
		case SDLK_LSHIFT:
			//Sprint
			p->sprinting = true;
			break;
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

		case SDLK_F1:
			//Print player location
			std::cout << "Current Location of player: " << p->getX() << ":" << p->getY() << std::endl;
			break;
		case SDLK_F2:
			this->showCol = !this->showCol;
			break;
		case SDLK_F3:
			this->showInter = !this->showInter;
			break;
		case SDLK_F4:
			this->showSpawnArea = !this->showSpawnArea;
			break;
		case SDLK_F5: 
			{
				//Consume Carrot (Same method as 9)
				Item* i = p->getInventory()->getItemById(1, true);
				if (i != nullptr) {
					std::cout << "Item found!" << std::endl;
					if (i->isConsumable()) {
						Consumable* c = (Consumable*)i;
						c->consume(p);
					} else if (i->isEquipable()) {
						Equipable* e = (Equipable*)i;
						e->equip(p);
					}
				}
				break;
			}
		case SDLK_F6: 
			{
				//Equip Axe (Same method as 0)
				Item* i = p->getInventory()->getItemById(3, true);
				if (i != nullptr) {
					std::cout << "Item found!" << std::endl;
					if (i->isConsumable()) {
						Consumable* c = (Consumable*)i;
						c->consume(p);
					} else if (i->isEquipable()) {
						Equipable* e = (Equipable*)i;
						e->equip(p);
					}
				}
				break;
			}
		case SDLK_F8:
			p->getCraftingSystem()->craftItem(Items::Axe);
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
			break;
		case SDLK_SPACE:
			//Current interact button (= space)
			//TIJDELIJK ROELS INTERACTION UITGESCHAKELT
			p->interaction = true;
			p->interact();
			break;


		case SDLK_ESCAPE:
			//Go to pause state on 'Escape'
			//TODO: methode voor deze escape klik aanmaken?
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
			p->StopAnimation();
			break;

		}
		break;
	}
}

void PlayState::update(double dt) {
	// check if player died
	if (!ready) {
		return;
	}

	if(this->timesUpdate > 2)
	{
		this->updateGameTimers(dt);
	}
	else
	{
		this->timesUpdate++;
	}

	//TODO: moet dit nog?
	//this->gsm->getActionContainer()->executeAllActions(dt);

	//Update all respawnable entities
	for (size_t i = 0; i < mec->getRespawnContainer()->getContainer()->size(); i++) {
		mec->getRespawnContainer()->getContainer()->at(i)->update(dt);
	}

	//Update all spawnpoints and moving entities
	//Calculate begin and end chunks for the camera (+5 and -5 to make it bigger than the screen)
	int beginChunkX = floor(camera->getX() / mapLoader->getChunkSize()) - 5;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mapLoader->getChunkSize()) + 5;
	int beginChunkY = floor(camera->getY() / mapLoader->getChunkSize()) - 5;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mapLoader->getChunkSize()) + 5;

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

			//Oude manier! LATEN STAAN
			////Moving entities
			//std::vector<MovableEntity*>* movingEntities = this->mec->getMovableContainer()->getChunk(i, j);
			//if (movingEntities != nullptr)
			//{
			//	for (MovableEntity* e : *movingEntities)
			//	{
			//		//TODO: enable when movableEntities get an 'update' method. 
			//		e->update(dt);
			//	}
			//}

			//NIEUWE MANIER! is dit de juiste manier?
			////Moving entities
			std::vector<MovableEntity*>* movingEntities = this->mec->getMovableContainer()->getChunk(i, j);
			if(movingEntities != nullptr && movingEntities->size() > 0)
			{
				std::vector<MovableEntity*> copyMovingEntities = std::vector<MovableEntity*>(*movingEntities);
				for (MovableEntity* e : copyMovingEntities)
				{
					e->update(dt);
				}
			}
		}
	}

	
	this->pEngine->updateParticles(dt);
}

void PlayState::updateGameTimers(double dt) {

	GameTimer::Instance()->updateGameTime(GameStateManager::Instance()->getUpdateLength() * dt);
}

void PlayState::draw() 
{
	if (!ready) {
		return;
	}
	//Calculate begin and end chunks for the camera (+1 and -1 to make it a little bigger then the screen)
	int beginChunkX = floor(camera->getX() / mapLoader->getChunkSize()) - 1;
	int endChunkX = floor((camera->getX() + camera->getWidth()) / mapLoader->getChunkSize()) + 1;
	int beginChunkY = floor(camera->getY() / mapLoader->getChunkSize()) - 1;
	int endChunkY = floor((camera->getY() + camera->getHeight()) / mapLoader->getChunkSize()) + 1;

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
					if(this->showCol)
					{
						//TEMP draw collision area
						CollidableEntity* ce = dynamic_cast<CollidableEntity*>(e);
						if(ce != NULL)
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
	if(this->showSpawnArea)
	{
		//Loop through all chunks
		for (int i = beginChunkY; i <= endChunkY; i++)
		{
			for (int j = beginChunkX; j <= endChunkX; j++)
			{
				std::vector<Spawnpoint*>* vec = this->mec->getSpawnpointContainer()->getChunk(i, j);
				if(vec != nullptr)
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

		//Draw interactable area
		if(this->showInter)
		{
			InteractableEntity* ie = dynamic_cast<InteractableEntity*>(e);
			if(ie != NULL)
			{
				ie->drawInteractableArea();
			}	
		}

		//Draw collision area
		if(this->showCol)
		{
			//TEMP draw collision area
			CollidableEntity* ce = dynamic_cast<CollidableEntity*>(e);
			if(ce != NULL)
			{
				ce->drawCollidableArea();
			}
		}
	}

	if (this->p->getInventory()->isOpen()) {
		this->p->getInventory()->draw();
	}

	//Draw timer
	GameTimer::Instance()->draw();

	//TODO : WEG ALS PIMS BALKEN ER IN ZITTEN
	this->gsm->sdlInitializer->drawText(std::string("Health: " + to_string(p->getHealth())), ScreenWidth - 120, ScreenHeight - 100, 100, 25);
 	this->gsm->sdlInitializer->drawText(std::string("Hunger: " + to_string(100-p->getHunger())), ScreenWidth - 120, ScreenHeight - 70, 100, 25);
 	this->gsm->sdlInitializer->drawText(std::string("Thirst: " + to_string(100-p->getThirst())), ScreenWidth - 120, ScreenHeight - 40, 100, 25);

	
	this->pEngine->drawParticles();

	blackSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, ScreenWidth, ScreenHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_Rect screenRect = {0, 0, ScreenWidth, ScreenHeight};
	SDL_FillRect(blackSurface, &screenRect, 0xFF00D9FF);

	SDL_Surface* image = IMG_Load((RESOURCEPATH + "hole.png").c_str());

	const int halfWidth = image->w / 2;
	const int halfHeight = image->h / 2;

	SDL_Rect sourceRect = { 0, 0, image->w, image->h };
	SDL_Rect destRect = { 300 - halfWidth, 300 - halfHeight, image->w, image->h };

	// Make sure our rects stays within bounds
	if (destRect.x < 0)
	{
		sourceRect.x -= destRect.x; // remove the pixels outside of the surface
		sourceRect.w -= sourceRect.x; // shrink to the surface, not to offset fog
		destRect.x = 0;
		destRect.w -= sourceRect.x; // shrink the width to stay within bounds
	}
	if (destRect.y < 0)
	{
		sourceRect.y -= destRect.y; // remove the pixels outside
		sourceRect.h -= sourceRect.y; // shrink to the surface, not to offset fog
		destRect.y = 0;
		destRect.h -= sourceRect.y; // shrink the height to stay within bounds
	}

	int xDistanceFromEdge = (destRect.x + destRect.w) - blackSurface->w;
	if (xDistanceFromEdge > 0) // we're busting
	{
		sourceRect.w -= xDistanceFromEdge;
		destRect.w -= xDistanceFromEdge;
	}
	int yDistanceFromEdge = (destRect.y + destRect.h) - blackSurface->h;
	if (yDistanceFromEdge > 0) // we're busting
	{
		sourceRect.h -= yDistanceFromEdge;
		destRect.h -= yDistanceFromEdge;
	}

	SDL_LockSurface(blackSurface);

	Uint32* destPixels = (Uint32*)blackSurface->pixels;
	Uint32* srcPixels = (Uint32*)image->pixels;

	static bool keepFogRemoved = false;

	for (int x = 0; x < destRect.w; ++x)
	{
		for (int y = 0; y < destRect.h; ++y)
		{
			Uint32* destPixel = destPixels + (y + destRect.y) * blackSurface->w + destRect.x + x;
			Uint32* srcPixel = srcPixels + (y + sourceRect.y) * image->w + sourceRect.x + x;

			unsigned char* destAlpha = (unsigned char*)destPixel + 3; // fetch alpha channel
			unsigned char* srcAlpha = (unsigned char*)srcPixel + 3; // fetch alpha channel
			if (keepFogRemoved == true && *srcAlpha > 0)
			{
				continue; // skip this pixel
			}

			*destAlpha = *srcAlpha;
		}
	}

	SDL_UnlockSurface(blackSurface);

	SDL_Texture* text2 = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), blackSurface);
	//SDL_Texture* text = SDL_CreateTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, ScreenWidth, ScreenHeight);
	//SDL_UpdateTexture(text, NULL, blackSurface->pixels, blackSurface->pitch);
	 
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), text2, NULL, &screenRect);

	SDL_DestroyTexture(text2);
	SDL_FreeSurface(blackSurface);
	
	/*SDL_Rect Dest = { 0, 0, 0, 0 };
	SDL_BlitSurface(blackSurface, NULL, SDL_GetWindowSurface(GameStateManager::Instance()->sdlInitializer->window), &Dest);
	
    SDL_UpdateWindowSurface(GameStateManager::Instance()->sdlInitializer->window);*/
	//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

Player* PlayState::getPlayer()
{
	return this->p;
}

Camera* PlayState::getCamera()
{
	return this->camera;
}

//ERROR Deze methode word nooit aangeroepen volgens mij.
//Betekend dus dat de playstate nooit verwijderd wordt
PlayState::~PlayState(void)
{
	delete camera;
	delete mec;
	delete mapLoader;
	std::cout << "deleting playstate" << endl; 
}
