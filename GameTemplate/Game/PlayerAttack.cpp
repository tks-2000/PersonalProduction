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
	/// @brief 攻撃判定が始まるまでの時間
	const float ATTACK_JUDGEMENT_START_TIME = 0.5f;
	/// @brief 攻撃判定が終わるまでの時間
	const float ATTACK_JUDGEMENT_END_TIME = 1.0f;
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
			m_attackPossibleMatchRate = ATTACK_POSSIBLE_MATCH_RATE;

			m_attackEffect.Init(u"Assets/effect/kick.efk");


			//初期化完了
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			m_isAttackStart = false;

			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				m_isAttackJudgement = false;
				m_attackJudgementTimer = 0.0f;
				m_isFollCharge = false;
				return;
			}

			//プレイヤーが攻撃状態の場合…
			if (m_player->GetPlayerStatus() == enPlayerAttack) {
				if (m_attackJudgementTimer == 0.0f) {
					m_isAttackStart = true;
				}
				//当たり判定の時間を計るタイマーを進める
				m_attackJudgementTimer += g_gameTime->GetFrameDeltaTime();

				//当たり判定のタイマーが当たり判定の出始めの時間まで進んだら…
				if (m_attackJudgementTimer >= ATTACK_JUDGEMENT_START_TIME) {
					//フルチャージ状態なら…
					if (m_isFollCharge == true) {
						//フルチャージ近接攻撃を行う
						ChargeMeleeAttack();
					}
					//フルチャージ状態でないなら…
					else {
						//近接攻撃を行う
						MeleeAttack();

					}
					//当たり判定が出ていることにする
					m_isAttackJudgement = true;
				}
				//当たり判定のタイマーが当たり判定の出始めの時間まで進んでいないなら…
				else {
					//当たり判定が出ていないことにする
					m_isAttackJudgement = false;
				}

				//当たり判定のタイマーが当たり判定の終了時間まで進んだら…
				if (m_attackJudgementTimer >= ATTACK_JUDGEMENT_END_TIME) {
					//プレイヤーを待機状態に戻す
					m_player->SetPlayerState(enPlayerIdle);
					//当たり判定のタイマーを元に戻す
					m_attackJudgementTimer = 0.0f;
					//当たり判定が出ていないことにする
					m_isAttackJudgement = false;

					m_isFollCharge = false;
				}
			}
			else {
				//当たり判定のタイマーを元に戻す
				m_attackJudgementTimer = 0.0f;
				//当たり判定が出ていないことにする
				m_isAttackJudgement = false;

				m_isFollCharge = false;
			}

			//Aボタンが押されていたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA)) {
				

				//攻撃状態でなく攻撃ボタンが押されてなかったら…
				if (m_player->GetPlayerStatus() != enPlayerAttack && m_isMeleeAttackButtonHold == false) {
					//攻撃を実行
					m_player->SetPlayerState(enPlayerAttack);
				}

				//近接攻撃ボタンが押されていることにする
				m_isMeleeAttackButtonHold = true;
			}

			//近接攻撃ボタンが押されていたら…
			if (m_isMeleeAttackButtonHold == true) {
				//チャージ時間を進める
				m_chargeMeleeAttackTimer += g_gameTime->GetFrameDeltaTime();

				//チャージ時間がチャージ完了時間まで進んで攻撃中で無かったら…
				if (m_chargeMeleeAttackTimer >= m_chargeMeleeAttackTime && m_player->GetPlayerStatus() != enPlayerAttack) {
					//フルチャージ状態にする
					m_isFollCharge = true;
				}
				//近接攻撃ボタンが離されたら…
				if (g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA) == false) {
					//フルチャージ状態の場合…
					if (m_isFollCharge == true) {
						//プレイヤーを攻撃中に変更
						m_player->SetPlayerState(enPlayerAttack);
					}
					//近接攻撃ボタンが離されたことにする
					m_isMeleeAttackButtonHold = false;

					m_chargeMeleeAttackTimer = 0.0f;
				}
			}


			//RB1ボタンで弾丸を発射
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB1))
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
			m_effectPos = m_player->GetPlayerPosition();
			m_effectRotation.SetRotationY(m_player->GetPlayerAngle());
			m_attackEffect.SetPosition(m_effectPos);
			m_attackEffect.SetRotation(m_effectRotation);
			m_attackEffect.SetScale({ 2.0f,2.0f,2.0f });
			m_attackEffect.Update();
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

					

					//敵にダメージを与える
					if (m_enemys[enemyNum]->GetState() == enemy::enEnemyDown) {
						return;
					}

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);

					/*CSoundSource* attackSe = NewGO<CSoundSource>(PRIORITY_VERYLOW);
					attackSe->Init(L"Assets/sound/se/WeakCollide.wav");
					attackSe->SetVolume(1.0f);
					attackSe->Play(false);*/

					//m_attackEffect.Play();
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