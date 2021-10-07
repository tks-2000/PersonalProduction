#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief 速度
	const float MOVE_VEROCITY = 0.2f;
	/// @brief 摩擦力
	const float FRICTION = 0.03f;
	/// @brief 停止する移動速度の大きさ
	const float STOP_MOVE_LENGTH = 0.1f;
	/// @brief 待機状態になる移動速度の大きさ
	const float IDLE_MOVE_LENGTH = 0.6f;
}

namespace MainGame {
	namespace Player {
		Move::Move()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Move::~Move()
		{

		}

		void Move::Init()
		{
			//データを取得
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_player = FindGO<Player>(PLAYER_NAME);

			//初期化完了
			m_isInitd = true;
		}

		const Vector3& Move::MoveExecute()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return g_vec3Zero;
			}

			//左スティック入力を受け取る
			m_LStickX = g_pad[0]->GetLStickXF();
			m_LStickY = g_pad[0]->GetLStickYF();

			//スティック入力とカメラの方向で移動方向を決める
			m_moveDirection =  m_gameCamera->GetCameraRight() * m_LStickX;
			m_moveDirection += m_gameCamera->GetCameraForward() * m_LStickY;

			//垂直方向の移動成分を無くす
			m_moveDirection.y = 0.0f;

			//正規化
			m_moveDirection.Normalize();
			
			//移動方向に速度を乗算して移動速度を求める
			m_moveSpeed += m_moveDirection * MOVE_VEROCITY;
				
			//移動速度に応じた摩擦力を求める
			m_friction = m_moveSpeed * FRICTION;

			//移動速度から摩擦力を引く
			m_moveSpeed -= m_friction;
			
			//移動速度が停止速度以下になったら…
			if (m_moveSpeed.Length() < STOP_MOVE_LENGTH) {
				//移動速度を0にする
				m_moveSpeed = g_vec3Zero;
				//待機状態に移行
				m_player->SetPlayerState(enPlayerIdle);
				//現在の座標を渡す
				return m_position;
			}

			//座標に移動速度を渡す
			m_position += m_moveSpeed;

			//移動速度が待機速度に達したら…
			if (m_moveSpeed.Length() < IDLE_MOVE_LENGTH) {
				//待機状態に移行
				m_player->SetPlayerState(enPlayerIdle);
			}
			//そうでないなら…
			else {
				//歩き状態に移行
				m_player->SetPlayerState(enPlayerWark);
			}

			//移動後の座標を返す
			return m_position;
		}
	}
}