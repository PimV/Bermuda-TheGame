#include "MenuMainScreen.h"
#include "MenuExitButton.h"
#include "MenuPlayButton.h"
#include "MenuCreditsButton.h"


MenuMainScreen::MenuMainScreen()
{
	init();
}

void MenuMainScreen::init()
{
	setBackground();

	//Create Buttons
	MenuPlayButton* playButton = new MenuPlayButton();
	MenuExitButton* exitButton = new MenuExitButton();
	MenuCreditsButton* creditsButton = new MenuCreditsButton();
	
	//place buttons
	exitButton->placeLeftMid();
	creditsButton->placeLeftAboveButton(exitButton);
	playButton->placeLeftAboveButton(creditsButton);
	
	//place in button vector
	buttons.push_back(playButton);
	buttons.push_back(exitButton);
	buttons.push_back(creditsButton);

}

void MenuMainScreen::setBackground()
{
	//Bermuda text
	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 80);
	SDL_Color white = { 255, 255, 255 };
	std::string bermudaMessage = "Bermuda";
	SDL_Surface* bermudaMessageSurface = TTF_RenderText_Blended(staryDarzyLarge, bermudaMessage.c_str(), white);
	bermudaTextTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), bermudaMessageSurface);

	bermudaTextRect.x = ((int)ScreenWidth - bermudaMessageSurface->w) / 2;
	bermudaTextRect.y = 50;
	bermudaTextRect.h = bermudaMessageSurface->h;
	bermudaTextRect.w = bermudaMessageSurface->w;

	//clearing surfaces
	SDL_FreeSurface(bermudaMessageSurface);
	TTF_CloseFont(staryDarzyLarge);

	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/campfire.jpg").c_str());
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}

	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = ScreenWidth;
	backgroundRect.h = ScreenHeight;
}

void MenuMainScreen::resetButtons()
{
	for each (BaseButton* var in buttons)
	{
		var->reset();
	}
}

void MenuMainScreen::handleEvents(SDL_Event mainEvent)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch(mainEvent.type) {
	case SDL_KEYDOWN:
		switch(mainEvent.key.keysym.sym) {
		case SDLK_SPACE:
			GameStateManager::Instance()->changeGameState(PlayState::Instance());
			break;
		}
		break;
	case SDL_MOUSEMOTION: 
		for (size_t i = 0; i < buttons.size(); i++) {
			buttons.at(i)->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT) {
			for (size_t i = 0; i < buttons.size(); i++) {
				if (buttons.at(i)->clicked(x, y))
				{
					break;
				}
			}
		}
		break;
	}
}

void MenuMainScreen::draw()
{
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), bermudaTextTexture, NULL, &bermudaTextRect);
	for (size_t i = 0; i < buttons.size(); i++) {
		buttons.at(i)->draw();
	}
}

void MenuMainScreen::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(bermudaTextTexture);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

MenuMainScreen::~MenuMainScreen()
{
	cleanup();
}