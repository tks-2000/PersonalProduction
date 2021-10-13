#include "stdafx.h"
#include "EnemyAttack.h"


namespace {

	const int NORMAL_ATTACK_POWER = 1;

	const float ATTACK_INTERVAL = 1.0f;
}

namespace mainGame {
	namespace enemy {
		Attack::Attack()
		{
			m_isInitd = false;
		}

		Attack::~Attack()
		{

		}

		void Attack::Init()
		{
			m_attackPower = NORMAL_ATTACK_POWER;
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
			m_isInitd = true;
		}

		void Attack::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			m_attackTimer += g_gameTime->GetFrameDeltaTime();

			if (m_attackTimer >= ATTACK_INTERVAL) {
				ExecuteAttack();
				m_attackTimer = 0.0f;
			}

		}

		void Attack::ExecuteAttack()
		{
			m_defensiveTarget->ReceiveDamage(m_attackPower);
		}

	}
}