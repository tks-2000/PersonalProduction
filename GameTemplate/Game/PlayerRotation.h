#pragma once

namespace mainGame {

	class GameCamera;

	namespace player {

		class Player;

		/// @brief �v���C���[�̉�]�𐧌䂷��N���X
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			/// @brief ������
			/// @param pl ������K�p����v���C���[�̃A�h���X
			void Init(Player* pl);

			/// @brief ��]�N�H�[�^�j�I�����擾
			/// @param moveSpeed ��]�����邽�߂̈ړ����x
			/// @return ���x�ɂ���Č��܂�����]�N�H�[�^�j�I��
			const Quaternion& RotationExecution(const Vector3& moveSpeed);

			const Quaternion& GetRotation() { return m_qRot; }

			const Vector3& GetDirection() { return m_direction; }

			const float GetAngle() { return m_angle; }

			/// @brief ��]�p�x�̕ω��ʂ��擾
			/// @return �p�x�̕ω���
			const float GetAngleAmount() { return m_angleAmount; }

			/// @brief �p�x�̕ω��ʂ����ɖ߂�
			void AngleReset() { m_angleAmount = 0.0f; }
		private:
			/// @brief Tps�J�����̎��̉�]���擾
			/// @param moveSpeed �ړ����x
			/// @return �ړ����x�ɉ�������]�N�H�[�^�j�I��
			const Quaternion& TpsRotationExecution(const Vector3& moveSpeed);

			/// @brief Fps�J�����̎��̉�]���擾
			/// @return �J�����̌����ɉ�������]�N�H�[�^�j�I��
			const Quaternion& FpsRotationExecution();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �v���C���[�̌����Ă������
			Vector3 m_direction = g_vec3Zero;
			/// @brief ��]�N�H�[�^�j�I��
			Quaternion m_qRot = g_quatIdentity;
			/// @brief �p�x
			float m_angle = 0.0f;
			/// @brief �ω�����O�̊p�x
			float m_oldAngle = 0.0f;
			/// @brief �p�x�̕ω���
			float m_angleAmount = 0.0f;
			/// @brief �v���C���[�N���X
			Player* m_player = nullptr;
			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
		};
	}
}