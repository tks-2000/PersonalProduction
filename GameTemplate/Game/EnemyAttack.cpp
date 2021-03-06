#include "stdafx.h"
#include "EnemyAttack.h"


namespace {
	/// @brief 通常の攻撃力
	const int NORMAL_IMPACT_FORCE = 2;
	/// @brief 強い攻撃力
	const int POWERFUL_ATTACK_POWER = 3;
	/// @brief 弱い攻撃力
	const int WEAK_ATTTACK_POWER = 1;
	/// @brief 攻撃間隔
	const float ATTACK_INTERVAL = 2.0f;
	/// @brief 攻撃範囲
	const float ATTACK_RANGE = 150.0f;
}

namespace mainGame {
	namespace enemy {
		Attack::Attack()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Attack::~Attack()
		{

		}

		void Attack::Init(Enemy* enemy)
		{
			//初期化済みなら実行しない
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

			//攻撃目標の情報を決定
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Attack::Execution()
		{
			//未初期化なら実行しない
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

			//攻撃するまでのタイマーを加算
			m_attackTimer += g_gameTime->GetFrameDeltaTime();

			//攻撃間隔までタイマーが進んだら…
			if (m_attackTimer >= ATTACK_INTERVAL) {
				//攻撃を実行
				ExecuteAttack();
				//タイマーを0に戻す
				m_attackTimer = 0.0f;
				m_isAttack = true;
				m_isHit = true;
			}

		}

		void Attack::ExecuteAttack()
		{
			

			//防衛対象に攻撃を加える
			m_defensiveTarget->ReceiveDamage(m_attackPower);

			
		}

	}
}