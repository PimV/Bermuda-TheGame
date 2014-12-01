#pragma once
#include "MovableEntity.h"
#include "CollidableEntity.h"
#include "DrawableEntity.h"
#include "Camera.h"
#include "StatusTracker.h"
#include "GameTimer.h"
#include "MovementDirectionEnum.h"
#include "Inventory.h"
#include "Crafting.h"
#include "AnimationEnum.h"

class Inventory;

class Player :
	public MovableEntity,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Player(int id, double moveSpeed, double x, double y, Camera* camera);
	~Player(void);

	void update(double dt);
	void directionsAndMove(double dt);

	void setHealth(int value);
	void setHunger(int value);
	void setThirst(int value);

	void incrementHealth(int value);
	void incrementHunger(int value);
	void incrementThirst(int value);

	int getHealth();
	int getHunger();
	int getThirst();

	void drawHealthBar(int x, int y);
	void drawHungerBar(int x, int y);
	void drawThirstBar(int x, int y);

	//void clickMove();
	void clickMove();
	void setPosition(double newX, double newY);
	void interact(double dt);
	void resetMovement();

	void drawStats();

	bool moveClick;
	bool interaction;
	int destX;
	int destY;

	Inventory* getInventory();
	Crafting* getCraftingSystem();
	StatusTracker* getStatusTracker();

	bool getCorrectToolSelected();
	void setCorrectToolSelected(bool tool);

private:
	Camera* camera;
	SDL_Texture* healthBar;
	SDL_Texture* hungerBar;
	SDL_Texture* thirstBar;
	SDL_Texture* healthBarContainer;
	SDL_Texture* thirstBarContainer;
	SDL_Texture* hungerBarContainer;

	bool healthAlphaFade;
	bool hungerAlphaFade;
	bool thirstAlphaFade;

	int healthAlpha;
	int hungerAlpha;
	int thirstAlpha;

	//PlayerUpdateTimer* playerTimer;
	int health, hunger, thirst;
	long hungerUpdate, hungerUpdateTime;
	long thirstUpdate, thirstUpdateTime;
	long healthUpdate, healthUpdateTime;

	int animationPickUp, animationPickLeft;
	int animationPickDown, animationPickRight;
	int animationPickStartColumn, animationPickEndColumn;

	int animationChopUp, animationChopLeft;
	int animationChopDown, animationChopRight;
	int animationChopStartColumn, animationChopEndColumn;

	int animationMineUp, animationMineLeft;
	int animationMineDown, animationMineRight;
	int animationMineStartColumn, animationMineEndColumn;

	bool correctToolSelected;

	double getDistence(int currentX, int currentY, int destX, int destY);

	Inventory* inventory;
	Crafting* crafting;
	StatusTracker* statusTracker;

	void updatePlayerStatuses(double dt);

	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();

	bool checkCollision(double newX, double newY);

	void setAnimationType(AnimationEnumType type);
};
