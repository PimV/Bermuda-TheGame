#include "MenuHelpScreen.h"
#include "MenuState.h"

MenuHelpScreen::MenuHelpScreen()
{
	init();
}

void tempFunction()
{
	cout << "tempFunction" << endl; 
}


void MenuHelpScreen::init()
{
	firstRect.h = ScreenHeight +80;
	firstRect.w = (ScreenWidth / 5) * 1;
	firstRect.x = 0;
	firstRect.y = 0-40;
	secRect.h = ScreenHeight;
	secRect.w = (ScreenWidth / 5) * 4;
	secRect.x = firstRect.w;
	secRect.y = 0;

	//nieuwe scherm toevoegen is button maken, inclusief commando. toevoegen aan buttons vector, scherm maken, get helpscherm maken(aanroepen in button)
	//ja, het kan en zou anders moeten

	movementScreen = new BaseHelpScreen(firstRect.w);
	movementScreen->setPicture("HelpScreens/movement.bmp");
	movementScreen->setText("Use the arrow keys to walk around or click anywhere on the screen to move to that area.");

	cutTreeScreen = new BaseHelpScreen(firstRect.w);
	cutTreeScreen->setPicture("HelpScreens/cutTree.bmp");
	cutTreeScreen->setText("Stand near a tree, select the axe in your inventory and hold down space bar to cut down the tree to obtain wood. Wood can be used to craft various items.");

	cutCactusScreen = new BaseHelpScreen(firstRect.w);
	cutCactusScreen->setPicture("HelpScreens/cutCactus.bmp");
	cutCactusScreen->setText("Stand near a cactus, select the axe in your inventory and hold down space bar to obtain some water. You can drink water to quench your thirst.");

	fishScreen = new BaseHelpScreen(firstRect.w);
	fishScreen->setPicture("HelpScreens/fish.bmp");
	fishScreen->setText("Stand near a school of fish, select your spear in your inventory and hold down space bar to catch the fish. Fish can be consumed to satisfy your hunger.");

	pickAppleScreen = new BaseHelpScreen(firstRect.w);
	pickAppleScreen->setPicture("HelpScreens/pickAppel.bmp");
	pickAppleScreen->setText("Stand near a tree with apples, and hold down space bar to obtain the apples. Apples can be consumed to quench your thirst and satisfy your hunger.");

	pickCarrotScreen = new BaseHelpScreen(firstRect.w);
	pickCarrotScreen->setPicture("HelpScreens/pickCarrot.bmp");
	pickCarrotScreen->setText("Stand near a carrot, and hold down space bar to pull the carrot out of the ground. Carrots can be consumed to satisfy your hunger. But look out, carrots will not grow back.");

	mineGoldScreen = new BaseHelpScreen(firstRect.w);
	mineGoldScreen->setPicture("HelpScreens/mineGold.bmp");
	mineGoldScreen->setText("Stand near a gold rock, select the pickaxe in your inventory and hold down space bar to mine the gold rock. Gold can be used to craft golden tools that are more durable than stone tools.");

	mineIceScreen = new BaseHelpScreen(firstRect.w);
	mineIceScreen->setPicture("HelpScreens/mineIce.bmp");
	mineIceScreen->setText("Stand near some ice, select the pickaxe in your inventory and hold down space bar to obtain some water. You can drink water to quench your thirst.");

	mineRockScreen = new BaseHelpScreen(firstRect.w);
	mineRockScreen->setPicture("HelpScreens/mineRock.bmp");
	mineRockScreen->setText("Stand near a rock, select the pickaxe in your inventory and hold down space bar to mine the rock. Rocks can be used to craft various items.");

	foodAndWaterScreen = new BaseHelpScreen(firstRect.w);
	foodAndWaterScreen->setPicture("HelpScreens/hungerThirst.bmp");
	foodAndWaterScreen->setText("The blue bar is your water bar and the brown bar is your food bar. The red bar is your health bar which will slowly decrease when one of the other bars is empty. You will die when your healthbar is empty.");

	timeScreen = new BaseHelpScreen(firstRect.w);
	timeScreen->setPicture("HelpScreens/time.bmp");
	timeScreen->setText("The time indicator shows when the sun rises and sets. Your health will quickly decrease when you are standing in complete darkness. Use a campfire to prevent this from happening.");

	craftingScreen = new BaseHelpScreen(firstRect.w);
	craftingScreen->setPicture("HelpScreens/crafting.png");
	craftingScreen->setText("Press 'T' or the icon on the bottom right to open the crafting screen. Click on an item and press 'craft' to craft the item. If you don't have enough resources, the button will be grey and the missing resources are shown in red.");

	fightingScreen = new BaseHelpScreen(firstRect.w);
	fightingScreen->setPicture("HelpScreens/fighting.png");
	fightingScreen->setText("Select the spear in your inventory and stand near an animal. Hold down space bar to attack. Most animals will give you food. But be carefull: certain animals can fight back.");

	BaseButton* movementButton = new BaseButton;
	movementButton->createButton("Movement", 24, 0);
	movementButton->action = &BaseButton::helpMovementScreenAction;
	movementButton->setHoverAction(true);

	BaseButton* cutTreeButton = new BaseButton;
	cutTreeButton->createButton("Woodcutting", 24, 0);
	cutTreeButton->action = &BaseButton::helpCutTreeScreenAction;
	cutTreeButton->setHoverAction(true);

	BaseButton* cutCactusButton = new BaseButton;
	cutCactusButton->createButton("Harvesting cacti", 24, 0);
	cutCactusButton->action = &BaseButton::helpCutCactusScreenAction;
	cutCactusButton->setHoverAction(true);

	BaseButton* fishButton = new BaseButton;
	fishButton->createButton("Fishing", 24, 0);
	fishButton->action = &BaseButton::helpFishScreenAction;
	fishButton->setHoverAction(true);

	BaseButton* pickAppleButton = new BaseButton;
	pickAppleButton->createButton("Picking apples", 24, 0);
	pickAppleButton->action = &BaseButton::helpPickAppleScreenAction;
	pickAppleButton->setHoverAction(true);

	BaseButton* pickCarrotButton = new BaseButton;
	pickCarrotButton->createButton("Picking carrots", 24, 0);
	pickCarrotButton->action = &BaseButton::helpPickCarrotScreenAction;
	pickCarrotButton->setHoverAction(true);

	BaseButton* mineGoldButton = new BaseButton;
	mineGoldButton->createButton("Mining gold", 24, 0);
	mineGoldButton->action = &BaseButton::helpMineGoldScreenAction;
	mineGoldButton->setHoverAction(true);

	BaseButton* mineIceButton = new BaseButton;
	mineIceButton->createButton("Mining ice", 24, 0);
	mineIceButton->action = &BaseButton::helpMineIceScreenAction;
	mineIceButton->setHoverAction(true);

	BaseButton* mineRockButton = new BaseButton;
	mineRockButton->createButton("Mining rock", 24, 0);
	mineRockButton->action = &BaseButton::helpMineRockScreenAction;
	mineRockButton->setHoverAction(true);

	BaseButton* hungerThirstButton = new BaseButton;
	hungerThirstButton->createButton("Status bars", 24, 0);
	hungerThirstButton->action = &BaseButton::helpFoodAndWaterScreenAction;
	hungerThirstButton->setHoverAction(true);

	BaseButton* timeButton= new BaseButton;
	timeButton->createButton("Time indicator", 24, 0);
	timeButton->action = &BaseButton::helptimeScreenAction;
	timeButton->setHoverAction(true);

	BaseButton* craftingButton = new BaseButton;
	craftingButton->createButton("Crafting", 24, 0);
	craftingButton->action = &BaseButton::helpCraftingScreenAction;
	craftingButton->setHoverAction(true);

	BaseButton* fightingButton = new BaseButton;
	fightingButton->createButton("Combat", 24, 0);
	fightingButton->action = &BaseButton::helpFightingScreenAction;
	fightingButton->setHoverAction(true);

	BaseButton* returnButton = new BaseButton;
	returnButton->createButton("Back to menu", 24, 0);
	returnButton->action = &BaseButton::menuMainScreenAction;
	
	movementButton->placeExactAt(15, 10);
	cutTreeButton->placeLeftUnderButton(movementButton);
	cutCactusButton->placeLeftUnderButton(cutTreeButton);
	fishButton->placeLeftUnderButton(cutCactusButton);
	pickCarrotButton->placeLeftUnderButton(fishButton);
	pickAppleButton->placeLeftUnderButton(pickCarrotButton);
	mineGoldButton->placeLeftUnderButton(pickAppleButton);
	mineIceButton->placeLeftUnderButton(mineGoldButton);
	mineRockButton->placeLeftUnderButton(mineIceButton);
	hungerThirstButton->placeLeftUnderButton(mineRockButton);
	timeButton->placeLeftUnderButton(hungerThirstButton);
	craftingButton->placeLeftUnderButton(timeButton);
	fightingButton->placeLeftUnderButton(craftingButton);
	returnButton->placeLeftUnder(15, 10);

	buttons.push_back(movementButton);
	buttons.push_back(cutTreeButton);
	buttons.push_back(cutCactusButton);
	buttons.push_back(fishButton);
	buttons.push_back(pickCarrotButton);
	buttons.push_back(pickAppleButton);
	buttons.push_back(mineGoldButton);
	buttons.push_back(mineIceButton);
	buttons.push_back(mineRockButton);
	buttons.push_back(hungerThirstButton);
	buttons.push_back(timeButton);
	buttons.push_back(craftingButton);
	buttons.push_back(fightingButton);
	buttons.push_back(returnButton);

	for(BaseButton* var : buttons)
	{
		var->setHelpScr(this);
	}

	setCurWindow(movementScreen);
	setBackground();
}

void MenuHelpScreen::setCurWindow(BaseHelpScreen* curwindow)
{
	curWindow = curwindow;
}

BaseHelpScreen* MenuHelpScreen::getMovementScr()
{
	return movementScreen;
}

BaseHelpScreen* MenuHelpScreen::getCutTreeScr()
{
	return cutTreeScreen;
}

BaseHelpScreen* MenuHelpScreen::getCutCactusScr()
{
	return cutCactusScreen;
}

BaseHelpScreen* MenuHelpScreen::getFishScr()
{
	return fishScreen;
}

BaseHelpScreen* MenuHelpScreen::getPickAppleScr()
{
	return pickAppleScreen;
}

BaseHelpScreen* MenuHelpScreen::getPickCarrotScr()
{
	return pickCarrotScreen;
}

BaseHelpScreen* MenuHelpScreen::getMineGoldScr()
{
	return mineGoldScreen;
}

BaseHelpScreen* MenuHelpScreen::getMineIceScr()
{
	return mineIceScreen;
}

BaseHelpScreen* MenuHelpScreen::getMineRockScr()
{
	return mineRockScreen;
}

BaseHelpScreen* MenuHelpScreen::getFoodAndWaterScr()
{
	return foodAndWaterScreen;
}

BaseHelpScreen* MenuHelpScreen::getTimeScr()
{
	return timeScreen;
}

BaseHelpScreen* MenuHelpScreen::getCraftingScr()
{
	return craftingScreen;
}

BaseHelpScreen* MenuHelpScreen::getFightingScr()
{
	return fightingScreen;
}

void MenuHelpScreen::setBackground()
{
	firstTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "single-inv-item.png").c_str());
	secTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\UltraJungle9.jpg").c_str());
}

void MenuHelpScreen::resetButtons()
{
	for(BaseButton* var : buttons)
	{
		var->reset();
	}
}

void MenuHelpScreen::handleEvents(SDL_Event mainEvent)
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
		for (size_t i = 0; i < buttons.size(); i++) {
			buttons.at(i)->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
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

void MenuHelpScreen::draw()
{
	SDL_Renderer* renderer = GameStateManager::Instance()->sdlInitializer->getRenderer();
	SDL_RenderCopy(renderer, firstTexture, NULL, &firstRect);
	SDL_RenderCopy(renderer, secTexture, NULL, &secRect);
	for(BaseButton* var : buttons)
	{
		var->draw();
	}
	curWindow->draw();
}

void MenuHelpScreen::cleanup()
{
	SDL_DestroyTexture(firstTexture);
	SDL_DestroyTexture(secTexture);
	delete movementScreen;
	delete cutTreeScreen;
	delete cutCactusScreen;
	delete fishScreen;
	delete pickAppleScreen;
	delete pickCarrotScreen;
	delete mineGoldScreen;
	delete mineIceScreen;
	delete mineRockScreen;
	delete foodAndWaterScreen;
	delete timeScreen;
	delete craftingScreen;
	delete fightingScreen;
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

MenuHelpScreen::~MenuHelpScreen()
{
	cleanup();
}
