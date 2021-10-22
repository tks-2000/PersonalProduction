#pragma once

class Game;
class Player;

namespace mainGame {

	enum EnCameraMode {
		enCameraModeTps,
		enCameraModeFps,
		enCameraModeNum
	};

	/// @brief �Q�[�����̃J�����𐧌䂷��N���X
	class GameCamera : public IGameObject
	{
	public:
		GameCamera();
		~GameCamera();

		void Init();
		bool Start();
		void Update();

		
		/// @brief �Q�[���J�����̒Ǐ]�ڕW��ݒ�
		/// @param target �Q�[���J�����ɐݒ肷��Ǐ]�ڕW�̍��W
		void SetCameraTarget(const Vector3& target) { m_cameraTarget = target; }

		/// @brief �Q�[���J�����̏���������
		/// @return �Q�[���J�����̏������const�Q��
		const Vector3& GetCameraUp() { return g_camera3D->GetUp(); }

		/// @brief �Q�[���J�����̑O���������
		/// @return �Q�[���J�����̑O������const�Q��
		const Vector3& GetCameraForward() { return g_camera3D->GetForward(); }

		/// @brief �Q�[���J�����̉E���������
		/// @return �Q�[���J�����̉E������const�Q��
		const Vector3& GetCameraRight() { return g_camera3D->GetRight(); }

		/// @brief �Q�[���J�����̍��W�����
		/// @return �Q�[���J�����̍��W��const�Q��
		const Vector3& GetCameraPos() { return m_cameraPos; }

		const EnCameraMode& GetCameraMode() { return m_mode; }

		const float GetCameraYAngleAmount() { return m_cameraYAngeAmount; }

		const Vector3& GetCameraAxisX() { return m_AxisX; }

		const float GetCameraXAngleAmount() { return m_cameraXAngeAmount; }

		const Vector3& GetCameraToTargetPos() { return m_cameraToTargetPos; }

		/// @brief ���s
		void Execution();

	private:
		

		void FpsCameraRotation();
		/// @brief �J�����̍X�V
		void TpsCameraUpdate();

		void FpsCameraUpdate();

		void TpsCameraMove();

		void FpsCameraMove();

		/// @brief �J�����̉�]
		void TpsCameraRotation();

		/// @brief �J�������Z�b�g
		void TpsCameraReset();

		void FpsCameraReset();

		bool m_isInitd = false;

		/// @brief �J�����̍��W
		Vector3 m_cameraPos = g_vec3Zero;
		/// @brief �J�����̈ړ����W
		Vector3 m_cameraMovePos = g_vec3Zero;
		/// @brief �J�����̍��W�ƈړ����W�Ƃ̋���
		Vector3 m_cameraMoveDistance = g_vec3Zero;
		/// @brief �J�����̈ړ�����
		Vector3 m_cameraMoveDirection = g_vec3Zero;


		/// @brief �J�����̒����_
		Vector3 m_cameraGazePoint = g_vec3Zero;
		/// @brief �J�����̖ڕW
		Vector3 m_cameraTarget = g_vec3Zero;
		/// @brief �J�����̒����_�ƖڕW�̋���
		Vector3 m_cameraTargetDistance = g_vec3Zero;
		/// @brief �J�����̒����_�̈ړ�����
		Vector3 m_cameraGazePointMoveDirection;

		/// @brief �J�����̒����_����J�����̍��W�ւ̋���
		Vector3 m_targetToCameraPos = g_vec3Zero;
		/// @brief �J�������璍���_�ւ̋���
		Vector3 m_cameraToTargetPos = g_vec3Zero;
		/// @brief �v���C���[����J�����̍��W�ւ̋���
		Vector3 m_playerToCameraPos = g_vec3Zero;
		
		/// @brief �J������Y����]
		Quaternion m_cameraYRot = g_quatIdentity;
		/// @brief �J������Y����]�̊p�x
		float m_cameraYAngle = 0.0f;
		/// @brief �J������Y����]�p�x�̗�
		float m_cameraYAngeAmount = 0.0f;
		/// @brief �L������J������Y����]�p�x�̗�
		float m_oldCameraYAngleAmount = 0.0f;

		/// @brief �J������X����]
		Quaternion m_cameraXRot = g_quatIdentity;
		/// @brief �J������X��]�̎�
		Vector3 m_AxisX = g_vec3Zero;
		/// @brief �J������X����]�̊p�x
		float m_cameraXAngle = 0.0f;
		/// @brief �J������X����]�p�x�̗�
		float m_cameraXAngeAmount = 0.0f;

		float m_oldPlayerAngle = 0.0f;

		EnCameraMode m_mode = enCameraModeTps;

		/// @brief �v���C���[
		player::Player* m_player = nullptr;

	};

}