#include "stdafx.h"
#include "GameCamera.h"

namespace {
	/// @brief �J�����̉�����
	const float CAMERA_FAR_PLANE = 10000.0f;
	/// @brief �J�����̋ߕ���
	const float CAMERA_NEAR_PLANE = 1.0f;
	/// @brief �J�����̑��x
	const float CAMERA_VELOCITY = 0.08f;
	/// @brief �J�����̉�]���x
	const float CAMERA_ROTATION_VELOCITY = 0.02f;
	/// @brief TPS�J�����̖��C��
	const float TPS_CAMERA_FRICTION = 20.0f;
	/// @brief FPS�J�����̖��C��
	const float FPS_CAMERA_FRICTION = 5.0f;
	/// @brief �J�����̈ړ����~�܂鋗��
	const float CAMERA_MOVE_STOP_DISTANCE = 0.01f;

	const Vector3 LIGHT_CAMERA_START_POS = { 0.0f,1000.0f,0.0f };

	const Vector3 LIGHT_CAMERA_START_TARGET = { 0.0f,0.0f,0.0f };
}

namespace mainGame {
	GameCamera::GameCamera()
	{
		m_isInitd = false;

		//�J�����̍��W�������_����ǂꂾ������Ă��邩���߂�
		m_targetToCameraPos = { 0.0f,200.0f,-500.0f };

		m_playerToCameraPos = { 50.0f,70.0f,-100.0f };

		m_cameraToTargetPos = { 0.0f,0.0f,600.0f };
	}

	GameCamera::~GameCamera()
	{

	}

	void GameCamera::Init()
	{
		//���������Ȃ���s���Ȃ�
		if (m_isInitd == true) {
			return;
		}
		//�������
		m_player = FindGO<player::Player>(player::PLAYER_NAME);

		m_miniMap = FindGO<map::MiniMap>(map::MINI_MAP_NAME);

		render::RenderingEngine* renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);

		m_shadow = renderingEngine->GetShadow();

		//m_shadow->SetLightCameraPos(LIGHT_CAMERA_START_POS);
		//m_shadow->SetLightCameraTarget(LIGHT_CAMERA_START_TARGET);

		m_oldPlayerAngle = m_player->GetPlayerAngle();

		m_cameraFriction = TPS_CAMERA_FRICTION;

		m_cameraMoveStopDistance = CAMERA_MOVE_STOP_DISTANCE;

		//�J�����̏����ݒ�
		g_camera3D->SetNear(CAMERA_NEAR_PLANE);
		g_camera3D->SetFar(CAMERA_FAR_PLANE);

		g_camera3D->Update();

		//����������
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
		//��������
		if (m_isInitd == false) {
			return;
		}
		
		//�X�e�[�^�X�ɉ����ď����𕪂���
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

		Vector3 plPos = m_player->GetPlayerPosition();

		m_shadow->SetLightCameraTarget(plPos);

		plPos.y += 1000.0f;
		plPos.z -= 1100.0f;

		m_shadow->SetLightCameraPos(plPos);

		
	}

	void GameCamera::TpsCameraUpdate()
	{
		//LB1�ŃJ�������Z�b�g
		if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonLB1)) {
			TpsCameraReset();
		}

		TpsCameraMove();
		TpsCameraRotation();

		//RB3�ŃJ�����`�F���W
		if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB3)) {


			//X���̋L�����Ă����ړ��ʂŉ�]������
			m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
			//�x�N�g���ɉ�]��K�p����
			m_cameraXRot.Apply(m_targetToCameraPos);
			//�L�����Ă����ړ��ʂ�0�ɂ���
			m_cameraXAngeAmount = 0.0f;

			//�J�����̈ړ��ʂ̔��΂ŉ�]�����ď����ʒu�ɖ߂�
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount);
			//�x�N�g���ɉ�]��K�p����
			m_cameraYRot.Apply(m_targetToCameraPos);

			//�L�����Ă�����]�ŃJ��������
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngeAmount);

			////�J�����̉�]��K�p����
			m_cameraYRot.Apply(m_cameraToTargetPos);
			m_cameraYRot.Apply(m_playerToCameraPos);

			m_cameraFriction = FPS_CAMERA_FRICTION;

			//���[�h��؂�ւ���
			m_mode = enCameraModeFps;
		}
	}

	void GameCamera::FpsCameraUpdate()
	{
		//LB1�ŃJ�������Z�b�g
		if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonLB1)) {
			
			FpsCameraReset();
		}

		FpsCameraMove();
		FpsCameraRotation();

		//RB3�ŃJ�������[�h�`�F���W
		if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB3)) {

			//�J�������Z�b�g����
			FpsCameraReset();

			//�J�����̈ړ��ʂ̔��΂ŉ�]�����ď����ʒu�ɖ߂�
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), -m_cameraYAngeAmount);

			//�J�����̉�]��K�p����
			m_cameraYRot.Apply(m_cameraToTargetPos);
			m_cameraYRot.Apply(m_playerToCameraPos);


			//Y���̋L�����Ă����ړ��ʂŉ�]������
			m_cameraYRot.SetRotation(g_camera3D->GetUp(), m_cameraYAngeAmount);
			//�x�N�g���ɉ�]��K�p����
			m_cameraYRot.Apply(m_targetToCameraPos);

			m_cameraFriction = TPS_CAMERA_FRICTION;

			Vector3 up = { 0.0f,0.0f,1.0f };

			m_miniMap->SetMapCameraUp(up);

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
		if (m_cameraTargetDistance.Length() < m_cameraMoveStopDistance) {
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
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / m_cameraFriction;
		}

		//�J�������W�ɖڕW�̍��W��n��
		m_cameraMovePos = m_cameraTarget;

		//�J�����̍��W��ڕW�����苗����������
		m_cameraMovePos += m_targetToCameraPos;


		//�J�����̍��W�ƃJ�����̈ړ��n�_�̋������v�Z����
		m_cameraMoveDistance = m_cameraMovePos - m_cameraPos;

		Vector3 ligCameraPos = m_shadow->GetLightCameraPos();
		Vector3 ligCameraTarget = m_shadow->GetLightCameraTarget();

		//��������~�����ȉ��Ȃ�c
		if (m_cameraMoveDistance.Length() < m_cameraMoveStopDistance) {
			//�J�����̍��W�ɃJ�����̈ړ��n�_�̍��W��n��
			m_cameraPos = m_cameraMovePos;
			ligCameraPos += m_cameraMoveDistance;
			ligCameraTarget += m_cameraMoveDistance;
		}
		else {
			//�J�����̍��W����J�����̈ړ��n�_�ւ̃x�N�g�����J�����̈ړ������ɂ���
			m_cameraMoveDirection = m_cameraMoveDistance;
			//���K�����ĕ����x�N�g���ɂ���
			m_cameraMoveDirection.Normalize();
			//�J�����̍��W�Ɍv�Z�����ړ��ʂ����Z����
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / m_cameraFriction;

			ligCameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / m_cameraFriction;
			
			ligCameraTarget += m_cameraMoveDirection * m_cameraMoveDistance.Length() / m_cameraFriction;
		}

		//m_shadow->SetLightCameraPos(ligCameraPos);
		//m_shadow->SetLightCameraTarget(ligCameraTarget);
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
			m_cameraGazePoint += m_cameraGazePointMoveDirection * m_cameraTargetDistance.Length() / m_cameraFriction;
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
			m_cameraPos += m_cameraMoveDirection * m_cameraMoveDistance.Length() / m_cameraFriction;
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
		m_cameraYAngle = g_pad[PLAYER1_CONTROLLER_NUM]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

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
		m_cameraXAngle = -g_pad[PLAYER1_CONTROLLER_NUM]->GetRStickYF() * CAMERA_ROTATION_VELOCITY;
		//�󂯎�����l�ŉ�]
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//��]���x�N�g���ɓK�p
		m_cameraXRot.Apply(m_targetToCameraPos);

		//��]�K�p��̃x�N�g�����󂯎��
		Vector3 toCameraPos = m_targetToCameraPos;

		//���K�����đ傫��1�̃x�N�g���ɂ���
		toCameraPos.Normalize();

		//Y�����ɑ傫���U�ꂷ���Ă�����c
		if (toCameraPos.y > 0.9f || toCameraPos.y < 0.1f) {
			//��]�K�p�O�̃x�N�g���ɖ߂�
			m_targetToCameraPos = oldPos;
			//�J�����A���O���̈ړ��ʂ�0�ɂ���
			m_cameraXAngle = 0.0f;
		}

		//�p�x�ω��ʂ��L�����Ă���
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
		m_cameraYAngle = g_pad[PLAYER1_CONTROLLER_NUM]->GetRStickXF() * CAMERA_ROTATION_VELOCITY;

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
		m_cameraXAngle = -g_pad[PLAYER1_CONTROLLER_NUM]->GetRStickYF() * CAMERA_ROTATION_VELOCITY;
		//�󂯎�����l�ŉ�]
		m_cameraXRot.SetRotation(m_AxisX, m_cameraXAngle);
		//��]���x�N�g���ɓK�p
		m_cameraXRot.Apply(m_cameraToTargetPos);

		//��]�K�p��̃x�N�g�����󂯎��
		Vector3 toCameraPos = m_cameraToTargetPos;

		//���K�����đ傫��1�̃x�N�g���ɂ���
		toCameraPos.Normalize();

		//Y�����ɑ傫���U�ꂷ���Ă�����c
		if (toCameraPos.y > 0.5f || toCameraPos.y < -0.5f) {
			//��]�K�p�O�̃x�N�g���ɖ߂�
			m_cameraToTargetPos = oldPos;
			//�J�����A���O���̈ړ��ʂ�0�ɂ���
			m_cameraXAngle = 0.0f;
		}

		//�p�x�ω��ʂ��L�����Ă���
		m_cameraXAngeAmount += m_cameraXAngle;
	}

	void GameCamera::TpsCameraReset()
	{
		//X���̋L�����Ă����ړ��ʂŉ�]������
		m_cameraXRot.SetRotation(m_AxisX, -m_cameraXAngeAmount);
		//�x�N�g���ɉ�]��K�p����
		m_cameraXRot.Apply(m_targetToCameraPos);
		//�L�����Ă����ω��ʂ�0�ɂ���
		m_cameraXAngeAmount = 0.0f;

		//�v���C���[�̊p�x�ω��ʂƌ��݂̊p�x�ω��ʂ��g���āA
		//�v���C���[�̌��ɉ�邽�߂ɕK�v�Ȋp�x�ω��ʂ����߂�
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