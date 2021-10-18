#pragma once
#include "Enemy.h"
#include "EnemyResource.h"

namespace mainGame{
	namespace enemy {

		class Enemy;

		


		/// @brief �G�̈ړ��𐧌䂷��N���X
		class Move
		{
		public:
			Move();
			~Move();

			/// @brief ������
			/// @param enemy ������K�p����G�̃A�h���X
			void Init(Enemy* enemy);

			/// @brief �ړ������s
			/// @param pos �ړ�����G�̍��W
			/// @return �ړ��������ʂ̍��W
			const Vector3& MoveExecute(Vector3& pos);

			/// @brief �ҋ@���̏��������s
			/// @param pos �ҋ@���̍��W
			/// @return �ҋ@���̌��ʂ̍��W
			const Vector3& IdleExecute(Vector3& pos);

			/// @brief �ړ��ڕW��ݒ�
			/// @param target �ړ�����ڕW�̍��W
			void SetMoveTarget(const Vector3& target) { m_moveTarget = target; }

			/// @brief �ړ����x��ݒ�
			/// @param speed �ݒ肷��ړ����x
			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

			/// @brief �ړ����x���擾
			/// @return �ړ����x��const�Q��
			const Vector3& GetMoveSpeed() { return m_moveSpeed; }

			/// @brief �ړ����~
			/// @param pos ��~���̍��W
			const Vector3& MoveStop(Vector3& pos);

		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �ړ����x
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief ���x
			float m_moveVerocity = 0.0f;
			/// @brief �ړ��ڕW
			Vector3 m_moveTarget = g_vec3Zero;
			/// @brief �ړ��ڕW�ւ̃x�N�g��
			Vector3 m_toTarget = g_vec3Zero;
			/// @brief �ړ�����
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief �ړ��ڕW�Ƃ̋���
			float m_targetDistance = 0.0f;
			/// @brief �ړ��J�n����܂ł̎���
			float m_moveStartTimer = 0.0f;
			/// @brief �L�����N�^�[�R���g���[���[
			CharacterController m_charaCon;
			/// @brief �G�N���X
			Enemy* m_enemy = nullptr;
		};
	}
}
