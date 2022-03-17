#include "stdafx.h"
#include "EnemyAttack.h"


namespace {
	/// @brief ’Êí‚ÌUŒ‚—Í
	const int NORMAL_IMPACT_FORCE = 2;
	/// @brief ‹­‚¢UŒ‚—Í
	const int POWERFUL_ATTACK_POWER = 3;
	/// @brief ã‚¢UŒ‚—Í
	const int WEAK_ATTTACK_POWER = 1;
	/// @brief UŒ‚ŠÔŠu
	const float ATTACK_INTERVAL = 1.0f;
	/// @brief UŒ‚”ÍˆÍ
	const float ATTACK_RANGE = 150.0f;
}

namespace mainGame {
	namespace enemy {
		Attack::Attack()
		{
			//–¢‰Šú‰»‚ÅŠJn
			m_isInitd = false;
		}

		Attack::~Attack()
		{

		}

		void Attack::Init(Enemy* enemy)
		{
			//‰Šú‰»Ï‚İ‚È‚çÀs‚µ‚È‚¢
			if (m_isInitd == true) {
				return;
			}

			m_enemy = enemy;

			switch (m_enemy->GetEnemyType())
			{
			case enEnemyTypeNormal: {
				m_attackPower = NORMAL_IMPACT_FORCE;
			}break;
			case enEnemyTypePowerful: {
				m_attackPower = POWERFUL_ATTACK_POWER;
			}break;
			case enEnemyTypeFast: {
				m_attackPower = WEAK_ATTTACK_POWER;
			}break;
			default:
				return;
				break;
			}

			//UŒ‚–Ú•W‚Ìî•ñ‚ğŒˆ’è
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			//‰Šú‰»Š®—¹
			m_isInitd = true;
		}

		void Attack::Execution()
		{
			//–¢‰Šú‰»‚È‚çÀs‚µ‚È‚¢
			if (m_isInitd == false) {
				return;
			}
			m_isAttack = false;
			m_isHit = false;

			if (m_enemy->GetState() != enEnemyAttack) {
				return;
			}

			Vector3 toDefensiveTargetPos = m_enemy->GetMoveTarget() - m_enemy->GetPosition();

			if (toDefensiveTargetPos.Length() > ATTACK_RANGE) {
				m_enemy->SetState(enEnemyMove);
				m_attackTimer = 0.0f;
				return;
			}

			//UŒ‚‚·‚é‚Ü‚Å‚Ìƒ^ƒCƒ}[‚ğ‰ÁZ
			m_attackTimer += g_gameTime->GetFrameDeltaTime();

			//UŒ‚ŠÔŠu‚Ü‚Åƒ^ƒCƒ}[‚ªi‚ñ‚¾‚çc
			if (m_attackTimer >= ATTACK_INTERVAL) {
				//UŒ‚‚ğÀs
				ExecuteAttack();
				//ƒ^ƒCƒ}[‚ğ0‚É–ß‚·
				m_attackTimer = 0.0f;
				m_isAttack = true;
				m_isHit = true;
			}

		}

		void Attack::ExecuteAttack()
		{
			

			//–h‰q‘ÎÛ‚ÉUŒ‚‚ğ‰Á‚¦‚é
			m_defensiveTarget->ReceiveDamage(m_attackPower);

			
		}

	}
}