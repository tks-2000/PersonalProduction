#include "stdafx.h"
#include "Enemy.h"

namespace {
	
	
}

namespace mainGame {
	namespace enemy {

		/// @brief 敵モデルのファイルパス
		const char* ENEMY_MODEL_TKM_FILEPATH[enEnemyTypeNum] = {
			"Assets/modelData/unityChan/utc_green.tkm",
			"Assets/modelData/unityChan/utc_red.tkm",
			"Assets/modelData/unityChan/utc_blue.tkm"
		};


		/// @brief 敵モデルのスケルトンファイルパス
		const char* ENEMY_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief 敵の最大体力
		const int MAX_HP = 3;
		/// @brief アニメーション補完率
		const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;

		const float DELETE_TIME = 5.0f;

		Enemy::Enemy()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Enemy::~Enemy()
		{
			m_player->DeleteEnemyData(this);
			DeleteGO(m_enemyModel);
		}

		void Enemy::Init(const int num, const EnEnemyType& type,const Vector3& pos)
		{
			if (m_isInitd == true || type == enEnemyTypeNum) {
				return;
			}

			m_enemyNum = num;

			m_enemyType = type;

			//初期座標を設定
			m_position = pos;
			//体力
			m_hp = MAX_HP;
			//メンバクラスを初期化
			m_enemyMove.Init(num,type,m_position);
			m_enemyRotation.Init(num);
			m_enemyAttack.Init(type);
			m_enemyAnimation.Init(num);

			//モデルをアニメーション有りで初期化
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				ENEMY_MODEL_TKM_FILEPATH[type],
				ENEMY_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);

			m_generator = FindGO<Generator>(ENEMY_GENERATOR_NAME);

			//プレイヤーの情報を入手
			m_player = FindGO<player::Player>(player::PLAYER_NAME);
			//プレイヤーに自分の情報を追加
			m_player->SetEnemyData(this);
			//待機中で開始
			m_state = enEnemyIdle;
			//初期化完了
			m_isInitd = true;
		}

		void Enemy::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//自分のステートによって処理を分ける
			switch (m_state)
			{
				//待機
			case enEnemyIdle: {
				m_position = m_enemyMove.IdleExecute(m_position);
			}break;
				//移動
			case enEnemyMove: {
				m_position = m_enemyMove.MoveExecute(m_position);
			}break;
				//攻撃
			case enEnemyAttack: {
				m_position = m_enemyMove.MoveStop(m_position);
				m_enemyAttack.Execution();
			}break;
				//ダメージ
			case enEnemyDamage: {
				m_position = m_enemyMove.IdleExecute(m_position);
			}break;
				//ダウン
			case enEnemyDown: {
				m_position = m_enemyMove.MoveStop(m_position);
				DownExecution();
			}break;
			default:
				break;
			}

			//回転を適用
			m_qRot = m_enemyRotation.RotationExecute(m_enemyMove.GetMoveSpeed());

			//アニメーションを進める
			m_enemyAnimation.AnimationUpdate();
			
			//モデルに更新された情報を伝える
			m_enemyModel->SetPosition(m_position);

			m_enemyModel->SetRotation(m_qRot);

			m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_enemyModel->Execution();
		}

		void Enemy::ReceiveDamage(const int damage)
		{
			//ダメージを受ける
			m_hp -= damage;

			//体力が0以下になったら
			if (m_hp <= 0) {
				//ダウン状態に移行
				m_state = enEnemyDown;
				m_hp = 0;
			}
		}

		void Enemy::DownExecution()
		{
			m_deleteTimer += g_gameTime->GetFrameDeltaTime();

			if (m_deleteTimer > DELETE_TIME) {
				m_generator->DeleteEnemy(this,m_enemyNum);
				DeleteGO(this);
			}
		}
	}
}