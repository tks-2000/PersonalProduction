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
			//�ړ����x�̑傫����0�̂Ƃ��c
			if (moveSpeed.Length() == 0.0f) {
				//��]�����s���Ȃ�
				return m_qRot;
			}

			//��]����O�̊p�x���L�����Ă���
			m_oldAngle = m_angle;

			//�ړ����x������������߂�
			Vector3 direction = moveSpeed;
			//Y�����̈ړ��ʂ�ł�����
			direction.y = 0.0f;
			//���K�����ĕ����x�N�g���ɂ���
			direction.Normalize();

			//�����x�N�g������p�x���v�Z����
			m_angle = atan2(direction.x, direction.z);

			//��]�����p�x�Ɖ�]����O�̊p�x�̍��ŕω��ʂ����߂�
			m_angleAmount += m_angle - m_oldAngle;

			//�p�x����N�H�[�^�j�I�������߂�
			m_qRot.SetRotationY(m_angle);

			return m_qRot;
		}
	}
}