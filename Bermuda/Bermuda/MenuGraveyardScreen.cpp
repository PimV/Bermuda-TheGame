#include "MenuGraveyardScreen.h"
#include "MenuState.h"
#include <ctime> // moet verplaatst worden naar player gameover

MenuGraveyardScreen::MenuGraveyardScreen()
{
	init();
}

void MenuGraveyardScreen::init()
{
	setBackground();
	graveyard = new Graveyard;
	createTable();
	createButton();
}

void MenuGraveyardScreen::createTable()
{
	TTF_Font* font = TTF_OpenFont((RESOURCEPATH + "fonts\\segoeuib.ttf").c_str(), 24);
	SDL_Color white = { 255, 255, 255 };
	std::string daysSurvivedText = "Days survived";
	std::string dayDiedText = "Date of death";

	SDL_Surface* daysSurvivedTextSurface = TTF_RenderText_Blended(font, daysSurvivedText.c_str(), white);
	SDL_Surface* dayDiedTextSurface = TTF_RenderText_Blended(font, dayDiedText.c_str(), white);

	SDL_Texture* daysSurvivedTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), daysSurvivedTextSurface);
	SDL_Texture* dateDiedTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), dayDiedTextSurface);
	SDL_Rect daysSurvivedRect;
	SDL_Rect dateDiedRect;

	daysSurvivedRect.h = daysSurvivedTextSurface->h;
	daysSurvivedRect.w = daysSurvivedTextSurface->w;
	dateDiedRect.h = dayDiedTextSurface->h;
	dateDiedRect.w = dayDiedTextSurface->w;

	int offset = 15;
	daysSurvivedRect.x = ScreenWidth / 2 - daysSurvivedRect.w - offset;
	daysSurvivedRect.y = startTable;
	dateDiedRect.x = ScreenWidth / 2 + offset;
	dateDiedRect.y = startTable;

	vector<GraveyardEntry*> allEntries = graveyard->getAllEntries();
	int locationNextEntry = daysSurvivedRect.y + daysSurvivedRect.h;
	for (GraveyardEntry* var : allEntries)
	{
		std::string s = std::to_string(var->daysSurvived);
		SDL_Surface* daysSurvivedEntryTextSurface = TTF_RenderText_Blended(font, s.c_str(), white);
		SDL_Texture* daysSurvivedEntryTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), daysSurvivedEntryTextSurface);
		SDL_Rect daysSurvivedEntryRect;
		daysSurvivedEntryRect.h = daysSurvivedEntryTextSurface->h;
		daysSurvivedEntryRect.w = daysSurvivedEntryTextSurface->w;
		daysSurvivedEntryRect.x = daysSurvivedRect.x;
		daysSurvivedEntryRect.y = locationNextEntry + 20;

		std::string d = std::to_string(var->dayDied);
		std::string m = std::to_string(var->monthDied);
		std::string j = std::to_string(var->yearDied);
		std::string t = d + " - " + m + " - " + j;
		SDL_Surface* dayDeadEntryTextSurface = TTF_RenderText_Blended(font, t.c_str(), white);
		SDL_Texture* dayDeadEntryTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), dayDeadEntryTextSurface);
		SDL_Rect dayDeadEntryRect;
		dayDeadEntryRect.h = dayDeadEntryTextSurface->h;
		dayDeadEntryRect.w = dayDeadEntryTextSurface->w;
		dayDeadEntryRect.x = dateDiedRect.x;
		dayDeadEntryRect.y = locationNextEntry + 20;

		textures.push_back(daysSurvivedEntryTexture);
		rectangles.push_back(daysSurvivedEntryRect);
		textures.push_back(dayDeadEntryTexture);
		rectangles.push_back(dayDeadEntryRect);
		SDL_FreeSurface(daysSurvivedEntryTextSurface);
		SDL_FreeSurface(dayDeadEntryTextSurface);
		locationNextEntry = locationNextEntry + 20;
	}

	textures.push_back(daysSurvivedTexture);
	textures.push_back(dateDiedTexture);
	rectangles.push_back(daysSurvivedRect);
	rectangles.push_back(dateDiedRect);

	SDL_FreeSurface(daysSurvivedTextSurface);
	SDL_FreeSurface(dayDiedTextSurface);
	TTF_CloseFont(font);
}

void MenuGraveyardScreen::createButton()
{
	BaseButton* returnButton = new BaseButton();
	returnButton->action = &BaseButton::menuMainScreenAction;
	returnButton->createButton("Return to main menu", 40, 0);
	returnButton->placeMidUnder((ScreenWidth / 2), ScreenHeight - ScreenHeight / 10);
	buttons.push_back(returnButton);
}

void MenuGraveyardScreen::setBackground()
{
	SDL_Texture* backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/campfire.jpg").c_str());
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}
	SDL_Rect backgroundRect;
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = ScreenWidth;
	backgroundRect.h = ScreenHeight;

	//Bermuda text
	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 60);
	SDL_Color white = { 255, 255, 255 };
	std::string graveyardMessage = "Graveyard";
	SDL_Surface* graveyardMessageSurface = TTF_RenderText_Blended(staryDarzyLarge, graveyardMessage.c_str(), white);
	SDL_Texture* graveyardTextTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), graveyardMessageSurface);

	SDL_Rect graveyardTextRect;
	graveyardTextRect.x = ((int)ScreenWidth - graveyardMessageSurface->w) / 2;
	graveyardTextRect.y = 50;
	graveyardTextRect.h = graveyardMessageSurface->h;
	graveyardTextRect.w = graveyardMessageSurface->w;

	startTable = graveyardTextRect.h + graveyardTextRect.y + 40;
	textures.push_back(backgroundTexture);
	rectangles.push_back(backgroundRect);
	textures.push_back(graveyardTextTexture);
	rectangles.push_back(graveyardTextRect);

	//clearing surfaces
	SDL_FreeSurface(graveyardMessageSurface);
	TTF_CloseFont(staryDarzyLarge);
}

void MenuGraveyardScreen::resetButtons()
{
	for (BaseButton* var : buttons)
	{
		var->reset();
	}
}

void MenuGraveyardScreen::handleEvents(SDL_Event mainEvent)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (mainEvent.type) {
	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym) {
		case SDLK_ESCAPE:
			MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuMainScreen());
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		for (BaseButton* var : buttons)
		{
			var->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			for (BaseButton* var : buttons)
			{
				if (var->clicked(x, y))
				{
					break;
				}
			}
		}
		break;
	}
}

void MenuGraveyardScreen::draw()
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), textures[i], NULL, &rectangles[i]);
	}
	for (BaseButton* var : buttons)
	{
		var->draw();
	}
}

void MenuGraveyardScreen::cleanup()
{
	for (SDL_Texture* var : textures)
	{
		SDL_DestroyTexture(var);
	}
	for (BaseButton* var : buttons)
	{
		delete var;
	}
	buttons.clear();
	delete graveyard;
}

MenuGraveyardScreen::~MenuGraveyardScreen()
{
	cleanup();
}
