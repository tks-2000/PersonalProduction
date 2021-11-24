#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief 歩く速度
	const float WARK_VEROCITY = 10.0f;
	/// @brief 走る速度
	const float RUN_VEROCITY = 20.0f;
	/// @brief 摩擦力
	const float FRICTION = 0.03f;
	/// @brief 停止する移動速度の大きさ
	const float STOP_MOVE_LENGTH = 10.0f;
	/// @brief 待機状態になる移動速度の大きさ
	const float IDLE_MOVE_LENGTH = 30.0f;
	/// @brief プレイヤーの重力
	const float PLAYER_GRAVITY = 30.0f;
	/// @brief プレイヤーの衝突判定の半径
	const float PLAYER_COLLISION_RADIUS = 30.0f;
	/// @brief プレイヤーの衝突判定の高さ
	const float PLAYER_COLLISION_HEIGHT = 50.0f;
	/// @brief 走るボタン
	const EnButton RUN_BUTTON = enButtonRB2;
}

namespace mainGame {
	namespace player {
		Move::Move()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Move::~Move()
		{

		}

		void Move::Init(Player* pl)
		{
			//データを取得
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_player = pl;
			m_charaCon.Init(PLAYER_COLLISION_RADIUS, PLAYER_COLLISION_HEIGHT, m_player->GetPlayerPosition());
			m_gravity = PLAYER_GRAVITY;

			//初期化完了
			m_isInitd = true;
		}

		void Move::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//左スティック入力を受け取る
			m_LStickX = g_pad[PLAYER1_CONTROLLER_NUM]->GetLStickXF();
			m_LStickY = g_pad[PLAYER1_CONTROLLER_NUM]->GetLStickYF();

			//左スティック入力があれば…
			if (m_LStickX != 0.0f || m_LStickY != 0.0f) {
				if (g_pad[0]->IsPress(RUN_BUTTON)) {
					m_player->SetPlayerState(enPlayerRun);
				}
				else {
					//プレイヤーを歩き状態に変更 
					m_player->SetPlayerState(enPlayerWark);
				}
			}
			else {
				m_player->SetPlayerState(enPlayerIdle);
			}



			switch (m_player->GetPlayerStatus())
			{
			case enPlayerIdle: {
				IdleExecute();
			}break;
			case enPlayerWark: {
				MoveExecute(WARK_VEROCITY);
			}break;
			case enPlayerRun: {
				MoveExecute(RUN_VEROCITY);
			}break;
			case enPlayerDamage: {

			}break;
			default:
				break;
			}
		}

		void Move::IdleExecute()
		{

			//停止中でも摩擦は加える
			m_moveSpeed = ApplyFriction(m_moveSpeed);

			//Y方向の移動速度を抜いた速度を取得
			Vector3 moveSpeedXZ = m_moveSpeed;
			moveSpeedXZ.y = 0.0f;

			//Y方向抜きの移動速度が停止速度以下になったら…
			if (moveSpeedXZ.Length() < STOP_MOVE_LENGTH) {
				//Y方向以外の移動速度を0にする
				m_moveSpeed.x = 0.0f;
				m_moveSpeed.z = 0.0f;
			}

			m_moveSpeed.y -= m_gravity;

			//移動速度を加える
			m_player->SetPlayerPosition(m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime()));

			//座標を渡す
			return;
		}

		void Move::MoveExecute(const float moveVerocity)
		{
			
			//スティック入力とカメラの方向で移動方向を決める
			m_moveDirection =  m_gameCamera->GetCameraRight() * m_LStickX;
			m_moveDirection += m_gameCamera->GetCameraForward() * m_LStickY;

			//垂直方向の移動成分を無くす
			m_moveDirection.y = 0.0f;

			//正規化
			m_moveDirection.Normalize();
			
			//移動方向に速度を乗算して移動速度を求める
			m_moveSpeed += m_moveDirection * moveVerocity;
			
			//移動速度に摩擦力を加える
			m_moveSpeed = ApplyFriction(m_moveSpeed);

			//重力を加える
			m_moveSpeed.y -= m_gravity;

			//移動速度からプレイヤーの座標を設定
			m_player->SetPlayerPosition(m_charaCon.Execute(m_moveSpeed,g_gameTime->GetFrameDeltaTime()));

			return;
		}

		const Vector3& Move::ApplyFriction(Vector3& speed)
		{
			//移動速度に応じた摩擦力を求める
			m_friction = speed * FRICTION;

			//移動速度から摩擦力を引く
			speed -= m_friction;

			//摩擦力を加えた速度を返す
			return speed;
		}
	}
}