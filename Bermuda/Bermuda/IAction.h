#pragma once
class IAction
{
public:
	virtual void execute() = 0;
	virtual ~IAction(void);
};

