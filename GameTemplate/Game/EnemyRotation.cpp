#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {
		Rotation::Rotation()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Rotation::~Rotation()
		{

		}

		void Rotation::Init(Enemy* enemy)
		{
			//�󂯎�����ԍ��̓G�N���X�������
			m_enemy = enemy;//FindGO<Enemy>(ENEMY_NAMES[num]);

			//����������
			m_isInitd = true;
		}

		const Quaternion& Rotation::RotationExecute(const Vector3& speed)
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return m_qRot;
			}

			//�ړ����x������������߂�
			Vector3 direction = speed;
			//Y�����̈ړ�������ł�����
			direction.y = 0.0f;
			//���K�����ĕ����x�N�g���ɂ���
			direction.Normalize();

			//�ړ����Ă��Ȃ��ꍇ�c
			if (direction.Length() == 0.0f || m_enemy->GetState() != enEnemyMove) {
				//���s�����ɕԂ�
				return m_qRot;
			}

			//�ړ����������]�����߂�
			m_angle = atan2(direction.x, direction.z);

			//Y�������ŉ�]������
			m_qRot.SetRotationY(m_angle);

			//��]��Ԃ�
			return m_qRot;
		}
	}
}