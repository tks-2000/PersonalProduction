#include "stdafx.h"
#include "Walker.h"

namespace mainGame {
	namespace enemy {

		const char* WALKER_MODEL_TKM_FILEPATH = "Assets/modelData/unityChan/utc_red.tkm";

		const char* WALKER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";
		/// @brief 敵モデルのスケルトンファイルパス
		const char* WALKER_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief 敵の最大体力
		const int WALKER_MAX_HP = 3;
		/// @brief アニメーション補完率
		const float WALKER_ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief 削除されるまでの時間
		const float WALKER_DELETE_TIME = 5.0f;

		void Walker::InitData(const EnemyInitData& enemyInitData)
		{
			//体力
			m_hp = WALKER_MAX_HP;

			//削除時間
			m_deleteTime = WALKER_DELETE_TIME;

			//メンバクラスを初期化
			//m_enemyMove.Init(this);
			m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);

			//モデルをアニメーション有りで初期化
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				WALKER_MODEL_TKM_FILEPATH,
				render::model::enMainRenderTarget,
				WALKER_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init(WALKER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);
		}

		void Walker::ExecuteBehavior()
		{
			switch (m_game->GetGameState())
			{
			case enGameStart: {

			}break;
			case enGameInProgress: {
				m_enemyRouteMove.Execution();
				m_enemyRotation.RotationExecute();
				m_enemyAttack.Execution();
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

			//アニメーションを進める
			m_enemyAnimation.AnimationUpdate();

			m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), WALKER_ANIMATION_COMPLEMENTARY_RATE);
		}
	}
}