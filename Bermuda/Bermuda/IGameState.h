#pragma once
class IGameState
{
public:
	virtual void init() = 0;;
	virtual void update(double dt) = 0;
	virtual void draw() = 0;
	virtual void handleInput() = 0;
	virtual ~IGameState(void);
};

