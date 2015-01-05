#include "ActionContainer.h"
#include "ClickAction.h"
#include <iostream>

ActionContainer::ActionContainer()
{
	this->init();
}

void ActionContainer::init() {
	m_actionContainer = new std::vector<IAction*>();
}

void ActionContainer::addAction(IAction* action) {
	m_actionContainer->push_back(action);
}

void ActionContainer::deleteAction(IAction* action) {
	//IAction a = m_actionContainer->pop_back();
}

void ActionContainer::executeAllActions(double dt) {
	while (m_actionContainer->size() > 0) {
		IAction* a = m_actionContainer->back();
		a->execute(dt);

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

void ActionContainer::cleanup() {
	while (!this->m_actionContainer->empty())
	{
		IAction* action = this->m_actionContainer->back();
		m_actionContainer->pop_back();
		delete action;
		action = nullptr;
	}
	delete this->m_actionContainer;
	this->m_actionContainer = nullptr;
}

ActionContainer::~ActionContainer()
{
	this->cleanup();
}
