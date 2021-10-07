#pragma once

class Player;

namespace MainGame {
	class GameCamera;
	namespace Player {
		
		class Move
		{
		public:
			Move();
			~Move();

			/// @brief ������
			void Init();

			/// @brief �ړ������s����
			/// @return �ړ���̍��W
			const Vector3& MoveExecute();

			/// @brief �ړ��������擾
			/// @return �ړ�������const�Q��
			const Vector3& GetMoveDirection() { return m_moveDirection; }

			/// @brief �ړ����x���擾
			/// @return �ړ����x��const�Q��
			const Vector3& GetMoveSpssd() { return m_moveSpeed; }
		private:
			/// @brief ���������Ă��邩�ǂ����̃t���O
			bool m_isInitd = false;

			/// @brief ���X�e�B�b�N�̉�����
			float m_LStickX = 0.0f;
			/// @brief ���X�e�B�b�N�̏c����
			float m_LStickY = 0.0f;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �ړ����x
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief �ړ�����
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief ���C��
			Vector3 m_friction = g_vec3Zero;

			CharacterController m_charaCon;

			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
			/// @brief �v���C���[
			Player* m_player = nullptr;
		};
	}
}