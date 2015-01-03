#pragma once
#include "State.h"
#include <assert.h>

template <class entity_type>
class StateMachine
{
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;
public:
	StateMachine(entity_type* owner) :m_pOwner(owner),
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_pGlobalState(nullptr){}
	virtual ~StateMachine(){};

	void setCurrentState(State<entity_type>* s){ m_pCurrentState = s; }
	void setGlobalState(State<entity_type>* s) { m_pGlobalState = s; }
	void setPreviousState(State<entity_type>* s){ m_pPreviousState = s; }

	entity_type* getOwner(){ return m_pOwner; }
	
	void update(double dt)const
	{
		if (m_pGlobalState) m_pGlobalState->execute(m_pOwner, dt);
		if (m_pCurrentState) m_pCurrentState->execute(m_pOwner, dt);
	}
	
	void changeState(State<entity_type>* pNewState)
	{
		assert(pNewState && "<StateMachine::ChangeState>: trying to change to a null state");

		if (m_pCurrentState != nullptr)
		{
			m_pPreviousState = m_pCurrentState;
			m_pCurrentState->exit(m_pOwner);
		}

		m_pCurrentState = pNewState;
		m_pCurrentState->enter(m_pOwner);
	}

	void revertToPreviousState()
	{
		changeState(m_pPreviousState);
	}

	State<entity_type>* getCurrentState() const{ return m_pCurrentState; }
	State<entity_type>* getGlobalState() const{ return m_pGlobalState; }
	State<entity_type>* getPreviousState() const{ return m_pPreviousState; }
	
	//bool isInState(const State<entity_type>& st)const;
};
