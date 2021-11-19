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

		const char* ENEMY_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";


		/// @brief 敵モデルのスケルトンファイルパス
		const char* ENEMY_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief 敵の最大体力
		const int MAX_HP = 3;
		/// @brief アニメーション補完率
		const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief 削除されるまでの時間
		const float DELETE_TIME = 5.0f;

		Enemy::Enemy()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Enemy::~Enemy()
		{
			
			DeleteGO(m_enemyModel);

			DeleteGO(m_enemyMapModel);
		}

		void Enemy::Init(const EnemyInitData& initData)
		{
			//初期化済み・初期化情報が正しくない場合実行しない
			if (m_isInitd == true || initData.enemyType == enEnemyTypeNum) {
				return;
			}

			//自身の番号を設定
			m_enemyNum = initData.enemyNum;
			
			//自身のタイプを設定
			m_enemyType = initData.enemyType;

			//初期座標を設定
			m_position = initData.enemyStartPos;

			//体力
			m_hp = MAX_HP;

			//メンバクラスを初期化
			//m_enemyMove.Init(this);
			m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);

			//モデルをアニメーション有りで初期化
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				ENEMY_MODEL_TKM_FILEPATH[initData.enemyType],
				render::model::enMainRenderTarget,
				ENEMY_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init(ENEMY_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);


			m_game = FindGO<Game>(GAME_NAME);
			//敵生成器の情報を入手
			m_generator = FindGO<Generator>(ENEMY_GENERATOR_NAME);
			//プレイヤーの情報を入手
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_defensiveTarget = FindGO < defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
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

			switch (m_game->GetGameState())
			{
			case enGameStart: {
				GameStartExecution();
			}break;
			case enGameInProgress: {
				GameInProgressExecution();
			}break;
			case enGameClear: {
				GameClearExecution();
			}break;
			case enGameOver: {
				GameOverExecution();
			}break;
			default:
				break;
			}

			//アニメーションを進める
			m_enemyAnimation.AnimationUpdate();

			//モデルに更新された情報を伝える
			m_enemyModel->SetPosition(m_position);

			m_enemyMapModel->SetPosition(m_position);

			m_enemyModel->SetRotation(m_qRot);

			m_enemyMapModel->SetRotation(m_qRot);

			m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_enemyModel->Execution();

			m_enemyMapModel->Execution();
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

		void Enemy::DeleteEnemy()
		{
			//生成器に削除を伝える
			//m_generator->DeleteEnemy(this);
			DeleteGO(this);
		}

		void Enemy::DownExecution()
		{
			//削除までの時間を進める
			m_deleteTimer += g_gameTime->GetFrameDeltaTime();

			//削除時間に達したら…
			if (m_deleteTimer > DELETE_TIME) {
				//生成器に削除を伝える
				m_generator->DeleteEnemy(this);
				m_player->DeleteEnemyData(this);
				//自身を削除
				DeleteGO(this);
			}
		}

		void Enemy::GameStartExecution()
		{
			
		}

		void Enemy::GameInProgressExecution()
		{
			//自分のステートによって処理を分ける
			switch (m_state)
			{
				//待機
			case enEnemyIdle: {
				//m_position = m_enemyMove.IdleExecute(m_position);
				m_position = m_enemyRouteMove.IdleExecution(m_position);
			}break;
				//移動
			case enEnemyMove: {
				//m_position = m_enemyMove.MoveExecute(m_position);

				m_position = m_enemyRouteMove.MoveExecution(m_position);
			}break;
				//攻撃
			case enEnemyAttack: {
				m_position = m_enemyRouteMove.StopExecution(m_position);
				m_enemyAttack.Execution();
			}break;
				//ダメージ
			case enEnemyDamage: {
				m_position = m_enemyRouteMove.IdleExecution(m_position);
			}break;
				//ダウン
			case enEnemyDown: {
				m_position = m_enemyRouteMove.StopExecution(m_position);
				DownExecution();
			}break;
			default:
				break;
			}

			//回転を適用
			m_qRot = m_enemyRotation.RotationExecute(m_enemyRouteMove.GetMoveSpeed());

			

			

			if (m_position.y < -1000.0f) {
				//生成器に削除を伝える
				m_generator->DeleteEnemy(this);
				m_player->DeleteEnemyData(this);
				//自身を削除
				DeleteGO(this);
			}
		}

		void Enemy::GameClearExecution()
		{
			
		}

		void Enemy::GameOverExecution()
		{
			
		}
	}
}