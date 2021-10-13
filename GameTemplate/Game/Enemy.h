#pragma once
#include "EnemyMove.h"
#include "EnemyAttack.h"

namespace mainGame {
	namespace enemy {

		/// @brief �G�̏�Ԃ�\���X�e�[�g
		enum EnEnemyState {
			/// @brief �ҋ@
			enEnemyIdle,
			/// @brief �ړ�
			enEnemyMove,
			/// @brief �U��
			enEnemyAttack,
			/// @brief ��~
			enEnemyStop,
			/// @brief �X�e�[�^�X�̍��v��
			enEnemyStateNum
		};

		/// @brief �G�̏������܂Ƃ߂��N���X
		class Enemy : public IGameObject
		{
		public:
			Enemy();
			~Enemy();

			/// @brief ������
			void Init();

			/// @brief ���s
			void Execution();

			/// @brief �G�̏�Ԃ�ݒ�
			/// @param state �ݒ肷��X�e�[�g
			void SetState(const EnEnemyState& state) { m_state = state; }

		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief �G�L�����N�^�[���f��
			render::model::SkinModelRender* m_enemyModel = nullptr;
			/// @brief �G�̈ړ�
			Move m_enemyMove;
			/// @brief �G�̍U��
			Attack m_enemyAttack;
			/// @brief �X�e�[�g
			EnEnemyState m_state = enEnemyIdle;
		};
	}
}
