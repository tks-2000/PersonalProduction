#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {
		Rotation::Rotation()
		{
			m_isInitd = false;
		}

		Rotation::~Rotation()
		{

		}

		void Rotation::Init()
		{
			m_enemy = FindGO<Enemy>(ENEMY_NAME);

			m_isInitd = true;
		}

		const Quaternion& Rotation::RotationExecute(const Vector3& speed)
		{
			if (m_isInitd == false) {
				return m_qRot;
			}

			Vector3 direction = speed;

			direction.y = 0.0f;

			direction.Normalize();

			if (direction.Length() == 0.0f || m_enemy->GetState() != enEnemyMove) {
				return m_qRot;
			}

			m_angle = atan2(direction.x, direction.z);

			m_qRot.SetRotationY(m_angle);

			return m_qRot;
		}
	}
}