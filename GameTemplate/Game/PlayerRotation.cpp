#include "stdafx.h"
#include "PlayerRotation.h"

namespace mainGame {
	namespace player {
		Rotation::Rotation()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}
		Rotation::~Rotation()
		{

		}
		const Quaternion& Rotation::RotationUpdate(const Vector3& moveSpeed)
		{
			

			//��]����O�̊p�x���L�����Ă���
			m_oldAngle = m_angle;

			//�ړ����x������������߂�
			Vector3 direction = moveSpeed;
			//Y�����̈ړ��ʂ�ł�����
			direction.y = 0.0f;
			//�ړ����x�̑傫����0�̂Ƃ��c
			if (direction.Length() == 0.0f) {
				//��]�����s���Ȃ�
				return m_qRot;
			}
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