#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief �G�̉�]�𐧌䂷��N���X
		class Rotation
		{
		public:
			Rotation();
			~Rotation();

			/// @brief ������
			/// @param enemy ������K�p����G�̃A�h���X
			void Init(Enemy* enemy);

			/// @brief �ړ����x�����]��ݒ�
			/// @param speed ��]���������G�̈ړ����x
			/// @return �ړ����x������o������]�N�H�[�^�j�I��
			const Quaternion& RotationExecute(const Vector3& speed);
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
			/// @brief �G�N���X
			Enemy* m_enemy = nullptr;
		};
	}
}
