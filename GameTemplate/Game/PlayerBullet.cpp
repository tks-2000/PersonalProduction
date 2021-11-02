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

		Bullet::Bullet()
		{
			m_isInitd = false;
		}

		Bullet::~Bullet()
		{
			DeleteGO(m_bulletModel);
		}

		void Bullet::Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos, const Vector3& target)
		{
			if (m_isInitd == true) {
				return;
			}

			//データを受け取る
			m_playerAttack = plAttack;
			m_enemys = enemys;

			//弾丸のモデルを初期化
			m_bulletModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bulletModel->Init("Assets/modelData/sphere/sphere.tkm");
			m_bulletModel->SetScale({ 0.7f,0.7f,0.7f });

			//受け取った座標から移動方向を決める
			m_startPos = pos;
			m_position = m_startPos;
			m_target = target;
			m_moveDirection = m_target - m_startPos;
			m_moveDirection.Normalize();

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

			//モデルに更新したデータを適用
			m_bulletModel->SetPosition(m_position);
			m_bulletModel->Execution();
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

				//敵との距離を測る
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				float matchRate = Dot(toEnemyVec, m_moveDirection);

				//敵との距離が一定以下なら…
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && matchRate > BULLET_COLLISION_MATCH_RATE) {

					//敵に衝撃を加える
					toEnemyVec.Normalize();
					enemyData->SetMoveSpeed(toEnemyVec * BULLET_IMPACT_FORCE);

					//敵にダメージを与える
					enemyData->SetState(enemy::enEnemyDamage);
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