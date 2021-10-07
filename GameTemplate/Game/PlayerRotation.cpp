#include "stdafx.h"
#include "PlayerRotation.h"

namespace MainGame {
	namespace Player {
		Rotation::Rotation()
		{

		}
		Rotation::~Rotation()
		{

		}
		const Quaternion& Rotation::RotationUpdate(const Vector3& moveSpeed)
		{
			//移動速度の大きさが0のとき…
			if (moveSpeed.Length() == 0.0f) {
				//回転を実行しない
				return m_qRot;
			}

			//回転する前の角度を記憶しておく
			m_oldAngle = m_angle;

			//移動速度から方向を求める
			Vector3 direction = moveSpeed;
			//Y方向の移動量を打ち消す
			direction.y = 0.0f;
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