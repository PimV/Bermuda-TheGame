#pragma once
#include "IAction.h"
#include <vector>
class ActionContainer
{
public:
	ActionContainer(void);

	void init();
	void cleanup();

	void addAction(IAction* action);
	void executeAction(IAction* action);
	void deleteAction(IAction* action);
	void executeAllActions(double dt);

	std::vector<IAction*>* getVector();



	virtual ~ActionContainer(void);

private:
	std::vector<IAction*>* m_actionContainer;
};

