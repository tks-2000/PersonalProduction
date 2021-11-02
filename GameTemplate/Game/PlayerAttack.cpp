#include "stdafx.h"
#include "PlayerAttack.h"

namespace {

	const float CHARGE_MELEE_ATTACK_TIME = 1.0f;
	/// @brief 敵に与えるダメージ
	const int NORMAL_ATTACK_DAMAGE = 3;
	/// @brief 敵に与える衝撃力
	const float NORMAL_IMPACT_FORCE = 3000.0f;
	/// @brief 敵に与える強力な衝撃力
	const float STRONG_IMPACT_FORCE = 6000.0f;
	/// @brief 攻撃範囲
	const float ATTACK_RANGE = 200.0f;
	/// @brief 攻撃可能な方向一致率
	const float ATTACK_POSSIBLE_MATCH_RATE = 0.0f;
	/// @brief 通常の弾丸の最大所持数
	const int NORMAL_MAX_BULLET_NUM = 10;
	/// @brief 通常の弾丸の再装填時間
	const float NORMAL_BULLET_RELOAD_TIME = 3.0f;
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
			m_enemys.clear();

			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				DeleteGO(m_bullets[bulletNum]);
			}

			m_bullets.clear();
		}

		void Attack::Init(Player* pl)
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//情報を入手
			m_player = pl;
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_attackPower = NORMAL_IMPACT_FORCE;
			m_attackRange = ATTACK_RANGE;
			m_chargeMeleeAttackTime = CHARGE_MELEE_ATTACK_TIME;

			m_bulletReloadTimer = 0.0f;
			m_bulletReloadTime = NORMAL_BULLET_RELOAD_TIME;
			m_maxBulletNum = NORMAL_MAX_BULLET_NUM;
			m_remainingBullets = m_maxBulletNum;


			//初期化完了
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//Aボタンで近接攻撃
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA)) {
				m_isMeleeAttackButtonHold = true;
			}

			if (m_isMeleeAttackButtonHold == true) {
				m_chargeMeleeAttackTimer += g_gameTime->GetFrameDeltaTime();

				if (m_chargeMeleeAttackTimer >= m_chargeMeleeAttackTime) {
					m_isFollCharge = true;
				}

				if (!g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA)) {
					if (m_isFollCharge == true) {
						ChargeMeleeAttack();
					}
					else {
						MeleeAttack();
						
					}
					m_isMeleeAttackButtonHold = false;
					m_chargeMeleeAttackTimer = 0.0f;
					m_isFollCharge = false;
				}
			}
			
			//RB1ボタンで弾丸を発射
			else if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB1))
			{
				//残弾があれば発射
				if (m_remainingBullets > 0) {
					BulletFiring();
				}
			}
			//残弾がない場合…
			if (m_remainingBullets <= 0) {
				//リロード時間を進める
				m_bulletReloadTimer += g_gameTime->GetFrameDeltaTime();
				//リロード完了時間に達したら…
				if (m_bulletReloadTimer >= m_bulletReloadTime) {
					//残弾を最大値まで回復
					m_remainingBullets = m_maxBulletNum;
					m_bulletReloadTimer = 0.0f;
				}
			}

			BulletExecution();
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

		void Attack::DeleteBullet(Bullet* bullet)
		{
			std::vector<Bullet*>::iterator it;
			it = std::find(
				m_bullets.begin(),
				m_bullets.end(),
				bullet
			);
			if (it != m_bullets.end()) {
				m_bullets.erase(it);
			}
		}

		void Attack::MeleeAttack()
		{
			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//敵との距離を測る
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//攻撃可能な距離だった場合…
				if (toEnemyPos.Length() < m_attackRange) {

					//敵へのベクトルで衝撃を与える
					toEnemyPos.Normalize();

					float matchRate = Dot(toEnemyPos, m_player->GetPlayerDirection());

					if (matchRate < ATTACK_POSSIBLE_MATCH_RATE) {
						return;
					}

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);

					//敵にダメージを与える
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::ChargeMeleeAttack()
		{
			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//敵との距離を測る
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//攻撃可能な距離だった場合…
				if (toEnemyPos.Length() < m_attackRange) {

					//敵へのベクトルで衝撃を与える
					toEnemyPos.Normalize();

					

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * STRONG_IMPACT_FORCE);

					//敵にダメージを与える
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::BulletFiring()
		{
			m_bullets.push_back(NewGO<Bullet>(PRIORITY_VERYLOW));
			Vector3 startPos = m_player->GetPlayerPosition();
			startPos.y += 50.0f;
			Vector3 targetPos;
			if (m_gameCamera->GetCameraMode() == enCameraModeFps) {
				targetPos = m_gameCamera->GetCameraGazePointPos();
			}
			else {
				targetPos = m_player->GetPlayerPosition() + m_player->GetPlayerDirection();
				targetPos.y = startPos.y;
			}
			m_bullets[m_bullets.size() - 1]->Init(this, &m_enemys, startPos, targetPos);
			m_remainingBullets--;
		}

		void Attack::BulletExecution()
		{
			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				m_bullets[bulletNum]->Execution();
			}

		}
	}
}