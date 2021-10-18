#include "stdafx.h"
#include "PlayerAttack.h"

namespace {
	/// @brief 敵に与えるダメージ
	const int NORMAL_ATTACK_DAMAGE = 1;
	/// @brief 敵に与える衝撃力
	const float NORMAL_ATTACK_POWER = 5000.0f;
	/// @brief 攻撃範囲
	const float ATTACK_RANGE = 200.0f;

}

namespace mainGame {
	namespace player {
		Attack::Attack()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Attack::~Attack()
		{

		}

		void Attack::Init(Player* pl)
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//情報を入手
			m_player = pl;
			m_attackPower = NORMAL_ATTACK_POWER;
			m_attackRange = ATTACK_RANGE;

			//初期化完了
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//敵との距離を測る
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//攻撃可能な距離だった場合…
				if (toEnemyPos.Length() < m_attackRange) {

					//敵へのベクトルで衝撃を与える
					toEnemyPos.Normalize();
					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);

					//敵にダメージを与える
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::DeleteEnemyData(enemy::Enemy* enemy)
		{
			std::vector<enemy::Enemy*>::iterator it;
			it = std::find(
				m_enemys.begin(),
				m_enemys.end(),
				enemy
			);
			if (it != m_enemys.end()) {
				m_enemys.erase(it);
			}
		}
	}
}