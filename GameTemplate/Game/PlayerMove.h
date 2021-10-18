#pragma once

class Player;

namespace mainGame {
	class GameCamera;
	namespace player {
		/// @brief �v���C���[�̈ړ��𐧌䂷��N���X
		class Move
		{
		public:
			Move();
			~Move();

			/// @brief ������
			/// @param pl ������K�p����v���C���[�̃A�h���X
			void Init(Player* pl);

			/// @brief �ҋ@���̏��������s
			const Vector3& IdleExecute(Vector3& pos);

			/// @brief �ړ����������s
			/// @param pos �ړ��O�̍��W
			/// @return �ړ���̍��W
			const Vector3& MoveExecute(Vector3& pos);

			/// @brief �ړ��������擾
			/// @return �ړ�������const�Q��
			const Vector3& GetMoveDirection() { return m_moveDirection; }

			/// @brief �ړ����x���擾
			/// @return �ړ����x��const�Q��
			const Vector3& GetMoveSpssd() { return m_moveSpeed; }
		private:

			const Vector3& ApplyFriction(Vector3& speed);

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
			/// @brief �d��
			float m_gravity = 0.0f;
			/// @brief �L�����N�^�[�R���g���[���[
			CharacterController m_charaCon;
			/// @brief �Q�[���J����
			GameCamera* m_gameCamera = nullptr;
			/// @brief �v���C���[
			Player* m_player = nullptr;
		};
	}
}