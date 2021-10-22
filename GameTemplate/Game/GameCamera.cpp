#include "stdafx.h"
#include "GameCamera.h"

namespace {
	/// @brief �J�����̑��x
	const float CAMERA_VELOCITY = 0.08f;
	/// @brief �J�����̉�]���x
	const float CAMERA_ROTATION_VELOCITY = 0.02f;
	/// @brief �J�����̖��C��
	const float TPS_CAMERA_FRICTION = 20.0f;

	const float FPS_CAMERA_FRICTION = 5.0f;
	/// @brief �J�����̈ړ����~�܂鋗��
	const float CAMERA_MOVE_STOP_DISTANCE = 0.01f;
}

namespace mainGame {
	GameCamera::GameCamera()
	{
		m_isInitd = false;

		//�J�����̍��W�������_����ǂꂾ������Ă��邩���߂�
		m_targetToCameraPos = { 0.0f,300.0f,-600.0f };

		m_playerToCameraPos = { 50.0f,70.0f,-100.0f };

		m_cameraToTargetPos = { 0.0f,0.0f,600.0f };
	}

	GameCamera::~GameCamera()
	{

	}

	void GameCamera::Init()
	{
		if (m_isInitd == true) {
			return;
		}
		m_player = FindGO<player::Player>(player::PLAYER_NAME);

		m_oldPlayerAngle = m_player->GetPlayerAngle();

		m_isInitd = true;
	}

	bool GameCamera::Start()
	{
		
		return true;
	}

	void GameCamera::Update()
	{
		
	}

	void GameCamera::Execution()
	{
		if (m_isInitd == false) {
			return;
		}
		
		switch (m_mode)
		{
		case enCameraModeTps: {
			TpsCameraUpdate();
		}break;
		case enCameraModeFps: {
			FpsCameraUpdate();
		}break;
		case enCameraModeNum: {

		}break;
		default:
			break;
		}

		//�J�����̒����_�ƍ��W��n��
		g_camera3D->SetTarget(m_cameraGazePoint);
		g_camera3D->SetPosition(m_cameraPos);
	}

	

	void GameCamera::TpsCameraUpdate()
	{
		//LB1�ŃJ�������Z�b�g
		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			TpsCameraReset();
		}

		TpsCameraMove();
		TpsCameraRotation();

		if (g_pad[0]->IsTrigger(enButtonRB3)) {


			//X���̋L�����Ă����ړ��ʂŉ�]������
			m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
			//�x�N�g���ɉ�]��K�p����
			m_cameraXRot.Apply(m_targetToCameraPos);
			//�L�����Ă����ړ��ʂ�0�ɂ���
			m_cameraXAngeAmount = 0.0f;

			//Y���̋L�����Ă����ړ��ʂŉ�]������
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount);
			//�x�N�g���ɉ�]��K�p����
			m_cameraYRot.Apply(m_targetToCameraPos);

			m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngeAmount);

			////�J�����̉�]��K�p����
			m_cameraYRot.Apply(m_cameraToTargetPos);
			m_cameraYRot.Apply(m_playerToCameraPos);

			//���[�h��؂�ւ���
			m_mode = enCameraModeFps;
		}
	}

	void GameCamera::FpsCameraUpdate()
	{
		//LB1�ŃJ�������Z�b�g
		if (g_pad[0]->IsTrigger(enButtonLB1)) {
			
			FpsCameraReset();
		}

		FpsCameraMove();
		FpsCameraRotation();

		if (g_pad[0]->IsTrigger(enButtonRB3)) {

			FpsCameraReset();

			m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount);

			////�J�����̉�]��K�p����
			m_cameraYRot.Apply(m_cameraToTargetPos);
			m_cameraYRot.Apply(m_playerToCameraPos);


			//Y���̋L�����Ă����ړ��ʂŉ�]������
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngeAmount);
			//�x�N�g���ɉ�]��K�p����
			m_cameraYRot.Apply(m_targetToCameraPos);
			//���[�h��؂�ւ���
			m_mode = enCameraModeTps;
		}
	}

	void GameCamera::TpsCameraMove()
	{
		//�J�����̖ڕW���v���C���[�̍��W�ɂ���
		m_cameraTarget = m_player->GetPlayerPosition();

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
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / TPS_CAMERA_FRICTION;
		}

		//�J�������W�ɖڕW�̍��W��n��
		m_cameraMovePos = m_cameraTarget;

		//�J�����̍��W��ڕW�����苗����������
		m_cameraMovePos += m_targetToCameraPos;


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
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / TPS_CAMERA_FRICTION;
		}
	}

	void GameCamera::FpsCameraMove()
	{
		//�J�����̈ړ��ڕW���v���C���[�̏������ɂ���
		m_cameraMovePos = m_player->GetPlayerPosition() + m_playerToCameraPos;

		//�J�����̖ڕW���J�����̈ړ��ڕW����O�̍��W�ɂ���
		m_cameraTarget = m_cameraMovePos + m_cameraToTargetPos;

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
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / FPS_CAMERA_FRICTION;
		}

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
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / FPS_CAMERA_FRICTION;
		}
	}

	void GameCamera::TpsCameraRotation()
	{
		//�J�����̏�����ƃJ�����̌����̊O�ς�X�����̉�]�������߂�
		m_AxisX.Cross(g_camera3D->GetUp(), m_targetToCameraPos * -1.0f);
		//���K��
		m_AxisX.Normalize();

		//Y����]
		//�E�X�e�B�b�N���͂��󂯎��
		m_cameraYAngle = g_pad[0]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

		//�p�x����J�����̉�]���쐬
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngle);

		//�J�����̉�]��K�p����
		m_cameraYRot.Apply(m_targetToCameraPos);

		//��]�p�x���L�����Ă���
		m_cameraYAngeAmount += m_cameraYAngle;

		//X����]
		//��]�K�p�O�̃x�N�g�����L������
		Vector3 oldPos = m_targetToCameraPos;
		//�E�X�e�B�b�N���͂��󂯎��
		m_cameraXAngle = -g_pad[0]->GetRStickYF() * CAMERA_ROTATION_VELOCITY;
		//�󂯎�����l�ŉ�]
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//��]���x�N�g���ɓK�p
		m_cameraXRot.Apply(m_targetToCameraPos);

		//��]�K�p��̃x�N�g�����󂯎��
		Vector3 toCameraPos = m_targetToCameraPos;

		//���K�����đ傫��1�̃x�N�g���ɂ���
		toCameraPos.Normalize();

		//Y���ɑ傫���U�ꂷ���Ă�����c
		if (toCameraPos.y > 0.9f || toCameraPos.y < 0.0f) {
			//��]�K�p�O�̃x�N�g���ɖ߂�
			m_targetToCameraPos = oldPos;
			//�J�����A���O���̈ړ��ʂ�0�ɂ���
			m_cameraXAngle = 0.0f;
		}

		//��]���L�����Ă���
		m_cameraXAngeAmount += m_cameraXAngle;

	}

	void GameCamera::FpsCameraRotation()
	{

		//�J�����̏�����ƃJ����X�����̉�]�������߂�
		m_AxisX.Cross(g_camera3D->GetUp(), m_cameraToTargetPos);
		//���K��
		m_AxisX.Normalize();

		//Y����]
		//�E�X�e�B�b�N���͂��󂯎��
		m_cameraYAngle = g_pad[0]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

		//�p�x����J�����̉�]���쐬
		m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngle);

		//�J�����̉�]��K�p����
		m_cameraYRot.Apply(m_playerToCameraPos);

		m_cameraYRot.Apply(m_cameraToTargetPos);

		//��]�p�x���L�����Ă���
		m_cameraYAngeAmount += m_cameraYAngle;

		//X����]
		//��]�K�p�O�̃x�N�g�����L������
		Vector3 oldPos = m_cameraToTargetPos;
		//�E�X�e�B�b�N���͂��󂯎��
		m_cameraXAngle = -g_pad[0]->GetRStickYF() * CAMERA_ROTATION_VELOCITY;
		//�󂯎�����l�ŉ�]
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//��]���x�N�g���ɓK�p
		m_cameraXRot.Apply(m_cameraToTargetPos);

		//��]�K�p��̃x�N�g�����󂯎��
		Vector3 toCameraPos = m_cameraToTargetPos;

		//���K�����đ傫��1�̃x�N�g���ɂ���
		toCameraPos.Normalize();

		//Y���ɑ傫���U�ꂷ���Ă�����c
		if (toCameraPos.y > 0.5f || toCameraPos.y < -0.5f) {
			//��]�K�p�O�̃x�N�g���ɖ߂�
			m_cameraToTargetPos = oldPos;
			//�J�����A���O���̈ړ��ʂ�0�ɂ���
			m_cameraXAngle = 0.0f;
		}

		//��]���L�����Ă���
		m_cameraXAngeAmount += m_cameraXAngle;
	}

	void GameCamera::TpsCameraReset()
	{
		//X���̋L�����Ă����ړ��ʂŉ�]������
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//�x�N�g���ɉ�]��K�p����
		m_cameraXRot.Apply(m_targetToCameraPos);
		//�L�����Ă����ړ��ʂ�0�ɂ���
		m_cameraXAngeAmount = 0.0f;

		//�v���C���[�̊p�x�ω��ʂƌ��݂̊p�x�ω��ʂ��g���ĕK�v�Ȋp�x�ω��ʂ����߂�
		float angleAmount = m_player->GetAngleAmount() - m_cameraYAngeAmount;

		//�v�Z�����p�x�ω��ʂŉ�]������
		m_cameraYRot.SetRotation(g_camera3D->GetUp(),angleAmount);
		//�x�N�g���ɉ�]��K�p����
		m_cameraYRot.Apply(m_targetToCameraPos);
		//���݂̊p�x�ω��ʂɌv�Z�����p�x�ω��ʂ����Z����
		m_cameraYAngeAmount += angleAmount;

		
		//���݂̃v���C���[�̊p�x���L�����Ă���
		m_oldPlayerAngle = m_player->GetPlayerAngle();

	}

	void GameCamera::FpsCameraReset()
	{
		//X���̋L�����Ă����ړ��ʂŉ�]������
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//�x�N�g���ɉ�]��K�p����
		m_cameraXRot.Apply(m_cameraToTargetPos);
		//�L�����Ă����ړ��ʂ�0�ɂ���
		m_cameraXAngeAmount = 0.0f;
	}
}