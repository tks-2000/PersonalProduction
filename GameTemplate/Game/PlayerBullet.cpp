#include "stdafx.h"
#include "PlayerBullet.h"

namespace mainGame {
	namespace player {
		/// @brief 弾丸の速度
		const float BULLET_VEROCITY = 3000.0f;
		/// @brief 敵と接触する距離
		const float ENEMY_COLLISION_DISTANCE = 200.0f;
		/// @brief 削除される移動距離
		const float DELETE_MOVE_DISTANCE = 3000.0f;
		/// @brief 敵に与える衝撃力
		const float BULLET_IMPACT_FORCE = 2000.0f;
		/// @brief 敵に与えるダメージ
		const int BULLET_DAMAGE = 1;
		/// @brief 弾丸の接触する方向一致率
		const float BULLET_COLLISION_MATCH_RATE = 0.0f;
		/// @brief 弾丸エフェクトの拡大率
		const Vector3 SHOT_EFFECT_SCALE = { 20.0f,20.0f,20.0f };
		/// @brief 弾丸エフェクトのファイルパス
		const wchar_t* BULLET_SE_FILEPATH = L"Assets/sound/se/bullet.wav";
		/// @brief 弾丸の音声の大きさ
		const float BULLET_SE_VOLUME = 0.1f;

		Bullet::Bullet()
		{
			m_isInitd = false;
		}

		Bullet::~Bullet()
		{
			//エフェクトを停止して削除
			m_shotEffect->Stop(true);
			DeleteGO(m_shotEffect);
		}

		void Bullet::Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos, const Vector3& target)
		{
			//未初期化なら実行しない
			if (m_isInitd == true) {
				return;
			}

			//データを受け取る
			m_playerAttack = plAttack;
			m_enemys = enemys;

			//受け取った座標から移動方向を決める
			m_startPos = pos;
			m_position = m_startPos;
			m_target = target;
			m_moveDirection = m_target - m_startPos;
			m_moveDirection.Normalize();

			//弾丸エフェクトを作成
			m_shotEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_shotEffect->Init(u"Assets/effect/shot_pl1.efk");
			m_shotEffect->SetScale(SHOT_EFFECT_SCALE);
			m_shotEffect->Play(true);

			//音声を設定
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_bulletSoundID = m_soundPlayer->SetSE(BULLET_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_bulletSoundID, BULLET_SE_VOLUME);
			m_soundPlayer->PlaySE(m_bulletSoundID);

			//初期化完了
			m_isInitd = true;
		}

		void Bullet::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//移動と接触判定を実行
			MoveExecution();
			EnemyCollision();

			Quaternion qRot = Quaternion::Identity;

			qRot.SetRotationY(atan2(m_moveDirection.x, m_moveDirection.z));

			//更新した情報をエフェクトに適用
			m_shotEffect->SetPosition(m_position);
			m_shotEffect->SetRotation(qRot);
			m_shotEffect->Execution();
		}

		void Bullet::MoveExecution()
		{
			//移動方向と速度で移動速度を決める
			m_moveSpeed = m_moveDirection * BULLET_VEROCITY * g_gameTime->GetFrameDeltaTime();

			//座標に移動速度を加える
			m_position += m_moveSpeed;

			//初期座標から自分の移動ベクトルを求める
			Vector3 moveVec = m_position - m_startPos;

			//移動ベクトルが一定以上なら…
			if (moveVec.Length() > DELETE_MOVE_DISTANCE) {
				//自身を削除
				DeleteThis();
			}
		}

		void Bullet::EnemyCollision()
		{
			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//敵のデータを取り出す
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				if (enemyData->GetState() == enemy::enEnemyDown) {
					continue;
				}

				//敵との距離を測る
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				float matchRate = Dot(toEnemyVec, m_moveDirection);

				//敵との距離が一定以下なら…
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && matchRate > BULLET_COLLISION_MATCH_RATE) {

					//敵に衝撃を加える
					toEnemyVec.Normalize();
					enemyData->SetMoveSpeed(toEnemyVec * BULLET_IMPACT_FORCE);

					//敵にダメージを与える
					enemyData->ReceiveDamage(BULLET_DAMAGE);

					//自身を削除
					DeleteThis();
				}
			}
		}

		void Bullet::DeleteThis()
		{
			//プレイヤーの攻撃を制御するクラスに自身の削除を伝える
			m_playerAttack->DeleteBullet(this);
			DeleteGO(this);
		}
	}
}