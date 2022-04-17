#pragma once

namespace mainGame {
	namespace enemy {

		class Enemy;

		/// @brief �G�l�~�[�̂̉�]�𐧌䂷��N���X
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
			void RotationExecute();

			/// @brief �����Ă�����������
			/// @return �����x�N�g����const�Q��
			const Vector3& GetDirection() const { return m_direction; }

			/// @brief �l�q�����n�߂�
			void StartSeeTheSituation();

			/// @brief �l�q�����I���
			void EndSeeTheSituation();

			/// @brief ��]�N�H�[�^�j�I�������
			/// @return ��]�N�H�[�^�j�I����const�Q��
			const Quaternion& GetRotation() const { return m_qRot; }

		private:
			/// @brief �l�q�����鏈���̎��s
			void ExecuteSeeTheSituation();
			
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ����
			Vector3 m_direction = g_vec3Zero;
			/// @brief �ȑO�̕���
			Vector3 m_oldDirection = g_vec3Zero;
			/// @brief �l�q���������
			Vector3 m_seeTheSituationDir = g_vec3Zero;
			/// @brief ���΂̗l�q���������
			Vector3 m_reverseSeeTheSituationDir = g_vec3Zero;
			/// @brief �l�q�����鎞�Ԃ̃^�C�}�[
			float m_seeTheSituationTimer = 0.0f;
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
