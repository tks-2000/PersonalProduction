#include "stdafx.h"
#include "Chaser.h"

namespace mainGame {
	namespace enemy {
		const char* CHASER_MODEL_TKM_FILEPATH = "Assets/modelData/unityChan/utc_green.tkm";

		const char* CHASER_MAP_MODEL_FILEPATH = "Assets/modelData/miniMap/enemyMapModel.tkm";
		/// @brief 敵モデルのスケルトンファイルパス
		const char* CHASER_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief 敵の最大体力
		const int CHASER_MAX_HP = 3;
		/// @brief アニメーション補完率
		const float CHASER_ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief 削除されるまでの時間
		const float CHASER_DELETE_TIME = 5.0f;

		const float SEARCH_DISTANCE = 500.0f;

		const float SEARCH_ANGLE_MATCH_RATE = 0.7f;

		const float CHASE_END_TIME = 5.0f;

		void Chaser::InitData(const EnemyInitData& enemyInitData)
		{
			//体力
			m_hp = CHASER_MAX_HP;

			//削除時間
			m_deleteTime = CHASER_DELETE_TIME;

			//メンバクラスを初期化
			//m_enemyMove.Init(this);
			m_enemyRouteMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttackThePlayer.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);
			m_enemyEffect.Init(this);

			//モデルをアニメーション有りで初期化
			/*m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				CHASER_MODEL_TKM_FILEPATH,
				render::model::enMainRenderTarget,
				CHASER_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);
			m_enemyModel->CreateShadow();

			m_enemyMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_enemyMapModel->Init(CHASER_MAP_MODEL_FILEPATH, render::model::enExpandModelGroup1);

			m_isModelDisplay = true;*/

			m_tkmFilepath = CHASER_MODEL_TKM_FILEPATH;
			m_tksFilepath = CHASER_MODEL_TKS_FILEPATH;
			m_animation = m_enemyAnimation.GetAnimationClip();
			m_animationNum = m_enemyAnimation.GetAnimationNum();
			m_mapModelFilepath = CHASER_MAP_MODEL_FILEPATH;

			//CreateModel();

			/*m_player = FindGO<player::Player>(player::PLAYER_NAME);
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);*/
		}

		const bool Chaser::IsHitAttack()
		{
			if (m_enemyAttack.IsHit() == true || m_enemyAttackThePlayer.IsHit() == true) {
				return true;
			}

			return false;
		}

		void Chaser::ExecuteBehavior()
		{
			switch (m_game->GetGameState())
			{
			case enGameStart: {

			}break;
			case enGameInProgress: {

				//プレイヤーを探す
				PlayerSearch();

				//動いているとき…
				if (m_state == enEnemyMove) {
					//追跡状態なら…
					if (m_chaseMode == true) {
						//移動目標をプレイヤーに設定
						m_enemyRouteMove.SetMoveTarget(m_player->GetPlayerPosition());
						
					}
					//追跡していない状態なら…
					else {
						//移動目標を防衛対象に設定
						m_enemyRouteMove.SetMoveTarget(m_defensiveTarget->GetPosition());
					}
				}
				//移動を実行
				m_enemyRouteMove.Execution();
				//回転を実行
				m_enemyRotation.RotationExecute();

				m_enemyEffect.Execution();

				//追跡状態なら…
				if (m_chaseMode == true) {
					//プレイヤーに対する攻撃を実行
					m_enemyAttackThePlayer.Execution();
				}
				//追跡状態でないなら…
				else {
					//防衛対象に対する攻撃を実行
					m_enemyAttack.Execution();
				}

				//ダウン状態のときはダウン状態の処理を行う
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

			if (m_isModelDisplay == true) {
				m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), CHASER_ANIMATION_COMPLEMENTARY_RATE);
			}
			
		}

		void Chaser::PlayerSearch()
		{
			//ダメージ中やダウン中は実行しない
			if (m_state == enEnemyDamage || m_state == enEnemyDown) {
				return;
			}

			//プレイヤーに向かうベクトルを求める
			Vector3 toPlayerPosition = m_player->GetPlayerPosition() - m_position;

			//プレイヤーとの距離が探す範囲内のとき…
			if (toPlayerPosition.Length() < SEARCH_DISTANCE) {

				//プレイヤーへ伸びるベクトルを正規化
				toPlayerPosition.Normalize();

				//自分の向きとプレイヤーへのベクトルの内積を求める
				float rate = Dot(toPlayerPosition, m_enemyRotation.GetDirection());

				//内積の結果が探す範囲内のとき…
				if (rate >= SEARCH_ANGLE_MATCH_RATE) {
					if (m_chaseMode == false) {
						//その場で少し跳ねる
						Vector3 speed = { 0.0f,2000.0f,0.0f };
						m_enemyRouteMove.SetMoveSpeed(speed);
						//移動を開始
						m_state = enEnemyMove;
						//追跡状態に移行
						m_chaseMode = true;
					}
				}
				//内積の結果が探す範囲外のとき…
				else {
					//追跡状態なら…
					if (m_chaseMode == true) {
						//追跡時間を増やす
						m_chaseTimer += g_gameTime->GetFrameDeltaTime();
					}
				}
			}
			//プレイヤーとの距離が探す範囲外のとき…
			else {
				//追跡状態なら…
				if (m_chaseMode == true) {
					//追跡時間を増やす
					m_chaseTimer += g_gameTime->GetFrameDeltaTime();
				}
			}

			//追跡時間が追跡終了時間まで達したら…
			if (m_chaseTimer >= CHASE_END_TIME) {
				//追跡時間を元に戻す
				m_chaseTimer = 0.0f;
				//追跡状態から戻る
				m_chaseMode = false;
				//その場で様子を見る
				m_enemyRotation.StartSeeTheSituation();
				m_state = enEnemySeeTheSituation;
				m_enemyRouteMove.SetMoveTarget(m_defensiveTarget->GetPosition());
			}
		}
	}
}