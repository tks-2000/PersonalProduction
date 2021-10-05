#pragma once

class Game;

namespace MainGame {

	/// @brief �Q�[�����̃J�����𐧌䂷��N���X
	class GameCamera : public IGameObject
	{
	public:
		GameCamera();
		~GameCamera();
		bool Start();
		void Update();

		

		void SetCameraTarget(const Vector3& target) { m_cameraTarget = target; }
	private:
		/// @brief �J�����̉�]
		void CameraRotation();
		/// @brief �J�����̍X�V
		void CameraUpdate();
		/// @brief �J�������Z�b�g
		void CameraReset();

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

		/// @brief �J�����̒����_����̋���
		Vector3 m_toCameraPos = g_vec3Zero;

		Vector3 m_oldToCameraPos = g_vec3Zero;
		
		/// @brief �J������Y����]
		Quaternion m_cameraYRot = g_quatIdentity;
		/// @brief �J������Y����]�̊p�x
		float m_cameraYAngle = 0.0f;
		/// @brief �J������Y����]�p�x�̗�
		float m_cameraYAngeAmount = 0.0f;

		/// @brief �J������X����]
		Quaternion m_cameraXRot = g_quatIdentity;

		Vector3 m_AxisX = g_vec3Zero;
		/// @brief �J������X����]�̊p�x
		float m_cameraXAngle = 0.0f;
		/// @brief �J������X����]�p�x�̗�
		float m_cameraXAngeAmount = 0.0f;

		/// @brief �J�����̑��x
		float m_cameraVerocity = 0.0f;

	};

}