#pragma once

class Game;
class Player;
class MiniMap;

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

		/// @brief ������
		void Init();
		bool Start();
		void Update();

		/// @brief �J�����̒Ǐ]�ڕW���擾
		/// @return �J�����̒Ǐ]�ڕW��const�Q��
		const Vector3& GetCameraTarget() const { return m_cameraTarget; }
		
		/// @brief �Q�[���J�����̒Ǐ]�ڕW��ݒ�
		/// @param target �Q�[���J�����ɐݒ肷��Ǐ]�ڕW�̍��W
		void SetCameraTarget(const Vector3& target) { m_cameraTarget = target; }

		/// @brief �Q�[���J�����̏���������
		/// @return �Q�[���J�����̏������const�Q��
		const Vector3& GetCameraUp() const { return g_camera3D->GetUp(); }

		/// @brief �Q�[���J�����̑O���������
		/// @return �Q�[���J�����̑O������const�Q��
		const Vector3& GetCameraForward() const { return g_camera3D->GetForward(); }

		/// @brief �Q�[���J�����̉E���������
		/// @return �Q�[���J�����̉E������const�Q��
		const Vector3& GetCameraRight() const { return g_camera3D->GetRight(); }

		/// @brief �Q�[���J�����̍��W�����
		/// @return �Q�[���J�����̍��W��const�Q��
		const Vector3& GetCameraPos() const { return m_cameraPos; }

		/// @brief �J������Y����]�N�H�[�^�j�I�����擾
		/// @return Y����]�N�H�[�^�j�I����const�Q��
		const Quaternion& GetCameraYRot() const { return m_cameraYRot; }

		/// @brief �J�����̃��[�h���擾
		/// @return �J�������[�h�̃X�e�[�g
		const EnCameraMode& GetCameraMode() { return m_mode; }

		/// @brief �J������Y����]�p�x���擾
		/// @return �J������Y����]�p�x
		const float GetCameraYAngleAmount() const { return m_cameraYAngeAmount; }

		/// @brief �J������X�����擾
		/// @return �J������X���x�N�g��
		const Vector3& GetCameraAxisX() const { return m_AxisX; }

		/// @brief �J������X����]�p�x���擾
		/// @return �J������X����]�p�x
		const float GetCameraXAngleAmount() const { return m_cameraXAngeAmount; }

		/// @brief Fps�J�����̍��W���璍���_�ւ̍��W���擾
		/// @return Fps�J�����̍��W���璍���_�ւ̍��W��const�Q��
		const Vector3& GetCameraToTargetPos() { return m_cameraToTargetPos; }

		/// @brief �J�����̒����_�̍��W���擾
		/// @return �J�����̒����_�̍��W��const�Q��
		const Vector3& GetCameraGazePointPos() { return m_cameraGazePoint; }

		/// @brief �J�����̖��C�͂��擾
		/// @return �J�����̖��C��
		const float GetCameraFriction() const { return m_cameraFriction; }

		/// @brief �J�����̈ړ���~�������擾
		/// @return �J�����̈ړ���~����
		const float GetCameraMoveStopDistance() const { return m_cameraMoveStopDistance; }

		/// @brief ���s
		void Execution();

	private:
		

		/// @brief Tps�J�����̍X�V
		void TpsCameraUpdate();

		/// @brief Fps�J�����̍X�V
		void FpsCameraUpdate();

		/// @brief Tps�J�����̈ړ�
		void TpsCameraMove();

		/// @brief Fps�J�����̈ړ�
		void FpsCameraMove();

		/// @brief Tps�J�����̉�]
		void TpsCameraRotation();

		/// @brief Fps�J�����̉�]
		void FpsCameraRotation();

		/// @brief Tps�J�������Z�b�g
		void TpsCameraReset();

		/// @brief Fps�J�������Z�b�g
		void FpsCameraReset();

		/// @brief �������t���O
		bool m_isInitd = false;
		/// @brief �J�����̍��W
		Vector3 m_cameraPos = g_vec3Zero;
		/// @brief �J�����̈ړ����W
		Vector3 m_cameraMovePos = g_vec3Zero;
		/// @brief �J�����̍��W�ƈړ����W�Ƃ̋���
		Vector3 m_cameraMoveDistance = g_vec3Zero;
		/// @brief �J�����̈ړ�����
		Vector3 m_cameraMoveDirection = g_vec3Zero;
		/// @brief �J�����̖��C��
		float m_cameraFriction = 0.0f;
		/// @brief �J�����̈ړ���~����
		float m_cameraMoveStopDistance = 0.0f;

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
		/// @brief �J�����̍��W����J�����̒����_�ւ̋���
		Vector3 m_cameraToTargetPos = g_vec3Zero;
		/// @brief �v���C���[����J�����̍��W�ւ̋���
		Vector3 m_playerToCameraPos = g_vec3Zero;
		
		/// @brief �J������Y����]
		Quaternion m_cameraYRot = g_quatIdentity;
		/// @brief �J������Y����]�̊p�x
		float m_cameraYAngle = 0.0f;
		/// @brief �J������Y����]�p�x�̗�
		float m_cameraYAngeAmount = 0.0f;

		/// @brief �J������X����]
		Quaternion m_cameraXRot = g_quatIdentity;
		/// @brief �J������X��]�̎�
		Vector3 m_AxisX = g_vec3Zero;
		/// @brief �J������X����]�̊p�x
		float m_cameraXAngle = 0.0f;
		/// @brief �J������X����]�p�x�̗�
		float m_cameraXAngeAmount = 0.0f;

		/// @brief �L������̃v���C���[�̊p�x
		float m_oldPlayerAngle = 0.0f;

		/// @brief �J�����̃X�e�[�g
		EnCameraMode m_mode = enCameraModeTps;

		/// @brief �v���C���[
		player::Player* m_player = nullptr;

		/// @brief UI
		ui::GameUI* m_gameUI = nullptr;

		/// @brief �e
		render::shadow::Shadow* m_shadow = nullptr;
	};

}