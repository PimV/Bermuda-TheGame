#pragma once
#include "GameTimer.h"

class AttackingNPC
{
	private:
		//
	protected:
		long currentAttackTime;
		long attackTime;

	public:
		AttackingNPC(int attackTime);

		bool checkAttackTimes();
		virtual void attack() = 0;

		virtual ~AttackingNPC();
};
