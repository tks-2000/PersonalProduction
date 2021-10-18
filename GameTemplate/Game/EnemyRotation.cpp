#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {
		Rotation::Rotation()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Rotation::~Rotation()
		{

		}

		void Rotation::Init(Enemy* enemy)
		{
			//受け取った番号の敵クラス情報を入手
			m_enemy = enemy;//FindGO<Enemy>(ENEMY_NAMES[num]);

			//初期化完了
			m_isInitd = true;
		}

		const Quaternion& Rotation::RotationExecute(const Vector3& speed)
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return m_qRot;
			}

			//移動速度から方向を決める
			Vector3 direction = speed;
			//Y方向の移動成分を打ち消す
			direction.y = 0.0f;
			//正規化して方向ベクトルにする
			direction.Normalize();

			//移動していない場合…
			if (direction.Length() == 0.0f || m_enemy->GetState() != enEnemyMove) {
				//実行せずに返す
				return m_qRot;
			}

			//移動方向から回転を求める
			m_angle = atan2(direction.x, direction.z);

			//Y軸方向で回転させる
			m_qRot.SetRotationY(m_angle);

			//回転を返す
			return m_qRot;
		}
	}
}