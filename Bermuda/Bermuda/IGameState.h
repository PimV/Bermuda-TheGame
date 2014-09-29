#pragma once
class GameStateManager;

class IGameState
{
protected:
	IGameState() { }
public:


	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(GameStateManager* gsm) = 0;
	virtual void update(GameStateManager* gsm, double dt) = 0;
	virtual void draw(GameStateManager* gsm) = 0;

	virtual ~IGameState(void);
};

