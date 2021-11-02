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

		void Rotation::Init(Player* pl)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�v���C���[�̃A�h���X�����
			m_player = pl;

			m_direction = { 0.0f,0.0f,1.0f };

			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			//����������
			m_isInitd = true;
		}

		const Quaternion& Rotation::RotationExecution(const Vector3& moveSpeed)
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return m_qRot;
			}

			//�Q�[���J�����̏�Ԃɂ���ď����𕪂���
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
			m_direction = direction;

			//��]�����p�x�Ɖ�]����O�̊p�x�̍��ŕω��ʂ����߂�
			m_angleAmount += m_angle - m_oldAngle;

			//�p�x����N�H�[�^�j�I�������߂�
			m_qRot.SetRotationY(m_angle);

			return m_qRot;
		}

		const Quaternion& Rotation::FpsRotationExecution()
		{
			//��]����O�̊p�x���L�����Ă���
			m_oldAngle = m_angle;

			//�Q�[���J�����̌����Ă�������ŉ�]���������߂�
			Vector3 direction = m_gameCamera->GetCameraToTargetPos();
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