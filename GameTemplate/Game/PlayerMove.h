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

			/// @brief ���s
			void Execution();

			/// @brief �ҋ@���̏��������s
			void IdleExecute();

			/// @brief �ړ������s
			/// @param velocity �ړ����鑬�x
			void MoveExecute(const float velocity);

			/// @brief �ړ��������擾
			/// @return �ړ�������const�Q��
			const Vector3& GetMoveDirection() { return m_moveDirection; }

			/// @brief �ړ����x���擾
			/// @return �ړ����x��const�Q��
			const Vector3& GetMoveSpssd() { return m_moveSpeed; }

			/// @brief �ړ����x��ݒ�
			/// @param speed �ݒ肷��ړ����x
			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

			/// @brief ���Z���鑬�x��ݒ�
			/// @param addVerocity �ݒ肷����Z���x
			void SetAddVerocity(const float addVerocity) { m_addVerocity = addVerocity; }

			/// @brief ���W��ݒ�
			/// @param pos �ݒ肷����W
			void SetPosition(const Vector3& pos) { m_position = pos; m_charaCon.SetPosition(m_position); }
		private:

			/// @brief ���C�͂�K�p
			/// @param speed �ړ����x
			/// @return ���C�͂����������x
			const Vector3& ApplyFriction(Vector3& speed);

			/// @brief ���������Ă��邩�ǂ����̃t���O
			bool m_isInitd = false;
			/// @brief ���X�e�B�b�N�̉�����
			float m_LStickX = 0.0f;
			/// @brief ���X�e�B�b�N�̏c����
			float m_LStickY = 0.0f;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ���Z���x
			float m_addVerocity = 0.0f;
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