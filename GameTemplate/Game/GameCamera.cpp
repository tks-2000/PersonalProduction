#include "stdafx.h"
#include "GameCamera.h"

namespace {
	/// @brief �J�����̑��x
	const float CAMERA_VELOCITY = 0.04f;
	/// @brief �J�����̉�]���x
	const float CAMERA_ROTATION_VELOCITY = 0.02f;
	/// @brief �J�����̖��C��
	const float CAMERA_FRICTION = 20.0f;
	/// @brief �J�����̈ړ����~�܂鋗��
	const float CAMERA_MOVE_STOP_DISTANCE = 0.01f;
}

namespace MainGame {
	GameCamera::GameCamera()
	{
		//�J�����̍��W�������_����ǂꂾ������Ă��邩���߂�
		m_toCameraPos = { 0.0f,300.0f,-500.0f };
	}

	GameCamera::~GameCamera()
	{

	}

	bool GameCamera::Start()
	{
		m_player = FindGO<Player::Player>(Player::PLAYER_NAME);
		return true;
	}

	void GameCamera::Update()
	{
		
	}

	void GameCamera::Execution()
	{
		//�J�����̏�����ƃJ�����̌����̊O�ς�X�����̉�]�������߂�
		m_AxisX.Cross(g_camera3D->GetUp(), m_toCameraPos * -1.0f);
		//���K��
		m_AxisX.Normalize();

		//LB1�ŃJ�������Z�b�g
		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			CameraReset();
		}

		CameraUpdate();
	}

	void GameCamera::CameraRotation()
	{
		//Y����]
		//�E�X�e�B�b�N���͂��󂯎��
		m_cameraYAngle = g_pad[0]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

		//�p�x����J�����̉�]���쐬
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngle);

		//�J�����̉�]��K�p����
		m_cameraYRot.Apply(m_toCameraPos);

		//��]�p�x���L�����Ă���
		m_cameraYAngeAmount += m_cameraYAngle;
		
		//X����]
		//��]�K�p�O�̃x�N�g�����L������
		m_oldToCameraPos = m_toCameraPos;
		//�E�X�e�B�b�N���͂��󂯎��
		m_cameraXAngle = -g_pad[0]->GetRStickYF() * CAMERA_VELOCITY;
		//�󂯎�����l�ŉ�]
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//��]���x�N�g���ɓK�p
		m_cameraXRot.Apply(m_toCameraPos);

		//��]�K�p��̃x�N�g�����󂯎��
		Vector3 toCameraPos = m_toCameraPos;

		//���K�����đ傫��1�̃x�N�g���ɂ���
		toCameraPos.Normalize();

		//Y���ɑ傫���U�ꂷ���Ă�����c
		if (toCameraPos.y > 0.9f || toCameraPos.y < 0.0f) {
			//��]�K�p�O�̃x�N�g���ɖ߂�
			m_toCameraPos = m_oldToCameraPos;
			//�J�����A���O���̈ړ��ʂ�0�ɂ���
			m_cameraXAngle = 0.0f;
		}
		
		//��]���L�����Ă���
		m_cameraXAngeAmount += m_cameraXAngle;
		
	}

	void GameCamera::CameraUpdate()
	{
		//�J�����̒����_�ƖڕW�̋������v�Z����
		m_cameraTargetDistance = m_cameraTarget - m_cameraGazePoint;

		//��������~�����ȉ��Ȃ�c
		if (m_cameraTargetDistance.Length() < CAMERA_MOVE_STOP_DISTANCE) {
			//�����_��ڕW�̍��W�ɐݒ�
			m_cameraGazePoint = m_cameraTarget;
		}
		//�����łȂ��Ȃ�c
		else {
			//�J�����̒����_����J�����̖ڕW�ւ̃x�N�g�����ړ������ɐݒ�
			m_cameraGazePointMoveDirection = m_cameraTargetDistance;
			//���K�����ĕ����x�N�g���ɂ���
			m_cameraGazePointMoveDirection.Normalize();
			//�����_�Ɍv�Z�����ړ��ʂ����Z����
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / CAMERA_FRICTION;
		}

		//�J�������W�ɖڕW�̍��W��n��
		m_cameraMovePos = m_cameraTarget;

		//�J�����̍��W��ڕW�����苗����������
		m_cameraMovePos += m_toCameraPos;


		//�J�����̍��W�ƃJ�����̈ړ��n�_�̋������v�Z����
		m_cameraMoveDistance = m_cameraMovePos - m_cameraPos;

		//��������~�����ȉ��Ȃ�c
		if (m_cameraMoveDistance.Length() < CAMERA_MOVE_STOP_DISTANCE) {
			//�J�����̍��W�ɃJ�����̈ړ��n�_�̍��W��n��
			m_cameraPos = m_cameraMovePos;
		}
		else {
			//�J�����̍��W����J�����̈ړ��n�_�ւ̃x�N�g�����J�����̈ړ������ɂ���
			m_cameraMoveDirection = m_cameraMoveDistance;
			//���K�����ĕ����x�N�g���ɂ���
			m_cameraMoveDirection.Normalize();
			//�J�����̍��W�Ɍv�Z�����ړ��ʂ����Z����
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / CAMERA_FRICTION;
		}

		//�J��������]������
		CameraRotation();

		//�J�����̒����_�ƍ��W��n��
		g_camera3D->SetTarget(m_cameraGazePoint);
		g_camera3D->SetPosition(m_cameraPos);

		/*g_camera3D->SetTarget(m_cameraPos);
		g_camera3D->SetPosition(m_cameraGazePoint);*/
	}

	void GameCamera::CameraReset()
	{
		//X���̋L�����Ă����ړ��ʂŉ�]������
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//�x�N�g���ɉ�]��K�p����
		m_cameraXRot.Apply(m_toCameraPos);
		//�L�����Ă����ړ��ʂ�0�ɂ���
		m_cameraXAngeAmount = 0.0f;

		
		//Y���̋L�����Ă����ړ��ʂŉ�]������
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount + m_player->GetAngleAmount());
		//�x�N�g���ɉ�]��K�p����
		m_cameraYRot.Apply(m_toCameraPos);
		//�L�����Ă����ړ��ʂ�0�ɂ���
		m_cameraYAngeAmount = 0.0f;

		m_player->ResetAngle();
	}
}