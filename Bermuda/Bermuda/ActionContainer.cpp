#include "ActionContainer.h"
#include "ClickAction.h"
#include <iostream>

ActionContainer::ActionContainer(void)
{
	this->init();
}

void ActionContainer::init() {
	m_actionContainer = new std::vector<IAction*>();
}

void ActionContainer::cleanup() {

}

void ActionContainer::addAction(IAction* action) {
	m_actionContainer->push_back(action);
	std::cout << m_actionContainer->size() << std::endl;
}

void ActionContainer::deleteAction(IAction* action) {
	//IAction a = m_actionContainer->pop_back();
}

void ActionContainer::executeAllActions() {
	while (m_actionContainer->size() > 0) {
		IAction* a = m_actionContainer->back();
		a->execute();

		m_actionContainer->pop_back();
		delete a;
	}
}

void ActionContainer::executeAction(IAction* action) {
	//action->execute();
}

std::vector<IAction*>* ActionContainer::getVector() {
	return m_actionContainer;
}

ActionContainer::~ActionContainer(void)
{
}