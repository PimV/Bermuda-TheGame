#pragma once
#include "PlayState.h"
#include "GameTimer.h"

class AttackingNPC
{
	protected:
		int attackPoints, attackRange;
		long currentAttackTime, attackTime;

	public:
		AttackingNPC(int attackPoints, int attackRange, long attackTime);

		int getAttackPoints();
		int getAttackRange();

		void setAttackPoints(int attackPoints);
		void setAttackRange(int attackRange);

		bool checkAttackTimes();
		virtual void attack();

		virtual ~AttackingNPC();
};
