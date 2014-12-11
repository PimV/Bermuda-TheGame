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
	virtual ~Player();

	void update(double dt);
	void directionsAndMove(double dt);
	void changeAnimationOnInventorySelection();

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

	#pragma region animation
	int animationPickUp;
	int animationPickStartColumn;
	int animationPickEndColumn;

	int animationChopUp;
	int animationChopStartColumn;
	int animationChopEndColumn;

	int animationChopGoldUp;
	int animationChopGoldStartColumn;
	int animationChopGoldEndColumn;

	int animationMineUp;
	int animationMineStartColumn;
	int animationMineEndColumn;

	int animationMineGoldUp;
	int animationMineGoldStartColumn;
	int animationMineGoldEndColumn;

	int animationSpearAttackUp;
	int animationSpearAttackStartColumn;
	int animationSpearAttackEndColumn;

	int animationSpearWalkUp;
	int animationSpearWalkLeft;
	int animationSpearWalkDown;
	int animationSpearWalkRight;
	int animationSpearWalkStartColumn;
	int animationSpearWalkEndColumn;
	#pragma endregion animation

	bool correctToolSelected;

	double getDistance(int currentX, int currentY, int destX, int destY);

	Inventory* inventory;
	Crafting* crafting;
	StatusTracker* statusTracker;

	void updatePlayerStatuses(double dt);

	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();

	bool checkCollision(double newX, double newY);

	void setAnimationType(AnimationEnumType type);
};
