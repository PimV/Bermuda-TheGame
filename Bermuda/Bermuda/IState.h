#pragma once
class IState
{
public:
	IState();
	virtual ~IState();

	virtual void update(double dt) = 0;
};

