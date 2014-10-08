#pragma once
class IAction
{
public:
	virtual void execute(double dt) = 0;
	virtual ~IAction(void);
};

