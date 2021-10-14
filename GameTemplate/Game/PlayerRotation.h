#pragma once

namespace mainGame {
	namespace player {
		/// @brief �v���C���[�̉�]�𐧌䂷��N���X
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			/// @brief ��]�N�H�[�^�j�I�����擾
			/// @param moveSpeed ��]�����邽�߂̈ړ����x
			/// @return ���x�ɂ���Č��܂�����]�N�H�[�^�j�I��
			const Quaternion& RotationUpdate(const Vector3& moveSpeed);

			/// @brief ��]�p�x�̕ω��ʂ��擾
			/// @return �p�x�̕ω���
			const float GetAngleAmount() { return m_angleAmount; }

			/// @brief �p�x�̕ω��ʂ����ɖ߂�
			void AngleReset() { m_angleAmount = 0.0f; }
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ��]�N�H�[�^�j�I��
			Quaternion m_qRot = g_quatIdentity;
			/// @brief �p�x
			float m_angle = 0.0f;
			/// @brief �ω�����O�̊p�x
			float m_oldAngle = 0.0f;
			/// @brief �p�x�̕ω���
			float m_angleAmount = 0.0f;
		};
	}
}