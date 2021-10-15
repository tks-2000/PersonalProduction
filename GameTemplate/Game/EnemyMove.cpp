#include "stdafx.h"
#include "EnemyMove.h"

namespace {
	/// @brief 通常の移動速度
	const float NORMAL_MOVE_VEROCITY = 5.0f;
	/// @brief 速い移動速度
	const float FAST_MOVE_VEROCITY = 7.5f;
	/// @brief 遅い移動速度
	const float SLOW_MOVE_VEROCITY = 2.5f;
	/// @brief 停止距離
	const float MOVE_STOP_DISTANCE = 200.0f;
	/// @brief 停止時間
	const float MOVE_START_TIME = 3.0f;
	/// @brief 摩擦力
	const float FRICTION = 0.03f;
	/// @brief 重力
	const float ENEMY_GRAVITY = 30.0f;
	/// @brief 敵の衝突判定の半径
	const float ENEMY_COLLISION_RADIUS = 50.0f;
	/// @brief 敵の衝突判定の高さ
	const float ENEMY_COLLISION_HEIGHT = 100.0f;
}

namespace mainGame {
	namespace enemy {
		Move::Move()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Move::~Move()
		{

		}

		void Move::Init(const EnEnemyType& type, const Vector3& pos)
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			switch(type)
			{
			case enEnemyTypeNormal: {
				m_moveVerocity = NORMAL_MOVE_VEROCITY;
			}break;
			case enEnemyTypePowerful: {
				m_moveVerocity = SLOW_MOVE_VEROCITY;
			}break;
			case enEnemyTypeFast: {
				m_moveVerocity = FAST_MOVE_VEROCITY;
			}break;
			default:
				return;
				break;
			}

			//情報を取得
			m_enemy = FindGO<Enemy>(ENEMY_NAME);
			//キャラクターコントローラーを初期化
			m_charaCon.Init(ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_HEIGHT,pos);

			//初期化完了
			m_isInitd = true;
		}

		const Vector3& Move::MoveExecute(Vector3& pos)
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return pos;
			}

			//座標と移動目標から目標へのベクトルを取得
			m_moveDirection = m_toTarget = m_moveTarget - pos;

			//目標との距離を測る 
			m_targetDistance = m_toTarget.Length();

			//縦方向の移動成分を消す
			m_moveDirection.y = 0.0f;

			//正規化
			m_moveDirection.Normalize();

			//目標への移動方向がない・目標との距離が停止距離まで達したら…
			if (m_moveDirection.Length() == 0.0f ||
				m_targetDistance <= MOVE_STOP_DISTANCE) {
				//攻撃を開始する
				m_enemy->SetState(enEnemyAttack);
				//座標をそのまま返す
				return pos;
			}

			//移動方向から移動速度を決める
			m_moveSpeed += m_moveDirection * m_moveVerocity;

			//移動速度に応じた摩擦力を加える
			m_moveSpeed -= m_moveSpeed * FRICTION;

			//重力を加える
			m_moveSpeed.y -= ENEMY_GRAVITY;

			//キャラクターコントローラーを使って座標を決める
			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//決まった座標を返す
			return pos;
		}

		const Vector3& Move::IdleExecute(Vector3& pos)
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return pos;
			}

			//現在の移動速度に摩擦力を加える
			m_moveSpeed -= m_moveSpeed * FRICTION;

			//重力を加える
			m_moveSpeed.y -= ENEMY_GRAVITY;

			//キャラクターコントローラーで移動させる
			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//移動し始めるまでのタイマーを進める
			m_moveStartTimer += g_gameTime->GetFrameDeltaTime();

			//タイマーが移動開始時間まで進んだら…
			if (m_moveStartTimer >= MOVE_START_TIME) {

				//タイマーを元に戻す
				m_moveStartTimer = 0.0f;

				//ステータスを移動中に変更
				m_enemy->SetState(enEnemyMove);

				//移動を実行
				pos = MoveExecute(pos);
			}

			//待機した結果を返す
			return pos;
		}

		const Vector3& Move::MoveStop(Vector3& pos)
		{
			//移動目標を自分の座標に設定
			m_moveTarget = pos;

			//現在の移動速度に摩擦力を加える
			m_moveSpeed -= m_moveSpeed * FRICTION;

			//重力を加える
			m_moveSpeed.y -= ENEMY_GRAVITY;

			//キャラクターコントローラーで座標を決める
			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//停止した結果を返す
			return pos;
		}
	}
}