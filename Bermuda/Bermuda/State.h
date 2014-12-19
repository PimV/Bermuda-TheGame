#pragma once
class State
{
public:
	State();
	virtual ~State();

	virtual void execute(double dt) = 0;
};

