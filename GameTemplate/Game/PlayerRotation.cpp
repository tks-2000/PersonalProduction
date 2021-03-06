#include "stdafx.h"
#include "PlayerRotation.h"

namespace mainGame {
	namespace player {
		/// @brief 開始時の方向
		const Vector3 START_DIRECTION = { 0.0f,0.0f,1.0f };

		Rotation::Rotation()
		{
			//未初期化で開始
			m_isInitd = false;
		}
		Rotation::~Rotation()
		{

		}

		void Rotation::Init(Player* pl)
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//使用する情報を入手
			m_player = pl;
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);

			//変数を初期化
			m_direction = START_DIRECTION;
			m_direction.Normalize();

			
			//初期化完了
			m_isInitd = true;
		}

		const Quaternion& Rotation::RotationExecution(const Vector3& moveSpeed)
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return m_qRot;
			}

			//ゲームカメラの状態によって処理を分ける
			switch (m_gameCamera->GetCameraMode())
			{
			case enCameraModeTps: {
				return TpsRotationExecution(moveSpeed);
			}break;
			case enCameraModeFps: {
				return FpsRotationExecution();
			}break;
			default:
				break;
			}

		}

		const Quaternion& Rotation::TpsRotationExecution(const Vector3& moveSpeed)
		{
			//回転する前の角度を記憶しておく
			m_oldAngle = m_angle;

			//移動速度から方向を求める
			Vector3 direction = moveSpeed;
			//Y方向の移動量を打ち消す
			direction.y = 0.0f;
			//移動速度の大きさが0のとき…
			if (direction.Length() == 0.0f) {
				//回転を実行しない
				return m_qRot;
			}
			//正規化して方向ベクトルにする
			direction.Normalize();

			//方向ベクトルから角度を計算する
			m_angle = atan2(direction.x, direction.z);
			m_direction = direction;

			//回転した角度と回転する前の角度の差で変化量を求める
			m_angleAmount += m_angle - m_oldAngle;

			//角度からクォータニオンを求める
			m_qRot.SetRotationY(m_angle);

			return m_qRot;
		}

		const Quaternion& Rotation::FpsRotationExecution()
		{
			//回転する前の角度を記憶しておく
			m_oldAngle = m_angle;

			//ゲームカメラの向いている方向で回転方向を決める
			Vector3 direction = m_gameCamera->GetCameraToTargetPos();
			//Y方向の移動量を打ち消す
			direction.y = 0.0f;
			//移動速度の大きさが0のとき…
			if (direction.Length() == 0.0f) {
				//回転を実行しない
				return m_qRot;
			}
			//正規化して方向ベクトルにする
			direction.Normalize();

			//方向ベクトルから角度を計算する
			m_angle = atan2(direction.x, direction.z);

			//回転した角度と回転する前の角度の差で変化量を求める
			m_angleAmount += m_angle - m_oldAngle;

			//角度からクォータニオンを求める
			m_qRot.SetRotationY(m_angle);

			return m_qRot;
		}
	}
}