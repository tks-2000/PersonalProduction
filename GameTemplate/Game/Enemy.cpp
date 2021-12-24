#include "stdafx.h"
#include "Enemy.h"

namespace mainGame {
	namespace enemy {

		/// @brief 敵モデルのファイルパス
		/*const char* ENEMY_MODEL_TKM_FILEPATH[enEnemyTypeNum] = {
			"Assets/modelData/unityChan/utc_green.tkm",
			"Assets/modelData/unityChan/utc_red.tkm",
			"Assets/modelData/unityChan/utc_blue.tkm"
		};*/

		//const char* ENEMY_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";


		/// @brief 敵モデルのスケルトンファイルパス
		//const char* ENEMY_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief 敵の最大体力
		//const int MAX_HP = 3;

		/// @brief アニメーション補完率
		//const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
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


			InitData(initData);

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

			if (m_defeatFlag == true) {
				DeleteEnemy();
				return;
			}

			ExecuteBehavior();
		
			//アニメーションを進める
			//m_enemyAnimation.AnimationUpdate();

			//モデルに更新された情報を伝える
			m_enemyModel->SetPosition(m_position);

			m_enemyMapModel->SetPosition(m_position);

			m_enemyModel->SetRotation(m_qRot);

			m_enemyMapModel->SetRotation(m_qRot);

			//m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_enemyModel->Execution();

			m_enemyMapModel->Execution();


			if (m_position.y < -1000.0f) {
				//生成器に削除を伝える
				m_generator->DeleteEnemy(this);
				m_player->DeleteEnemyData(this);
				//自身を削除
				DeleteGO(this);
			}
		}

		void Enemy::SetMoveSpeed(const Vector3& speed)
		{
			//m_enemyRouteMove.SetMoveSpeed(speed);
		}
		

		void Enemy::ReceiveDamage(const int damage)
		{
			//ダメージを受ける
			m_hp -= damage;

			//m_enemyRotation.StartSeeTheSituation();

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
			m_generator->DeleteEnemy(this);
			m_player->DeleteEnemyData(this);
			//自身を削除
			DeleteGO(this);
		}

		void Enemy::InitData(const EnemyInitData& initData)
		{
			//体力
			m_hp = 0;

			//削除時間
			m_deleteTime = DELETE_TIME;

			//メンバクラスを初期化
			//m_enemyMove.Init(this);
			//m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			//m_enemyAttack.Init(this);
			//m_enemyAnimation.Init(this);

			//モデルを初期化
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				"Assets/modelData/unityChan/utc_green.tkm",
				render::model::enMainRenderTarget
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init("Assets/modelData/miniMap/enemyMapModel.tkm", render::model::enExpandModelGroup1);
		}

		void Enemy::ExecuteBehavior()
		{
			switch (m_game->GetGameState())
			{
			case enGameStart: {

			}break;
			case enGameInProgress: {
				//m_enemyRouteMove.Execution();
				//m_qRot = m_enemyRotation.RotationExecute(m_enemyRouteMove.GetMoveSpeed());
				//m_enemyAttack.Execution();
				if (m_state == enEnemyDown) {
					DownExecution();
				}

			}break;
			case enGameClear: {

			}break;
			case enGameOver: {

			}break;
			default:
				break;
			}

		}

		void Enemy::DownExecution()
		{
			//削除までの時間を進める
			m_deleteTimer += g_gameTime->GetFrameDeltaTime();

			//削除時間に達したら…
			if (m_deleteTimer >= m_deleteTime) {
				m_defeatFlag = true;
			}
		}

		
	}
}