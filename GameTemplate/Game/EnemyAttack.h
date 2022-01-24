#pragma once
#include "Enemy.h"


namespace mainGame {

	namespace defensiveTarget{

		class DefensiveTarget;
	}

	namespace enemy {

		class Enemy;

		/// @brief �G�̍U���𐧌䂷��N���X
		class Attack
		{
		public:
			Attack();
			~Attack();

			/// @brief ������
			/// @param enemy ������K�p����G�̃A�h���X
			void Init(Enemy* enemy);

			/// @brief �U�����s���Ă��邩�H
			/// @return �s���Ă���� true �s���Ă��Ȃ���� false
			const bool IsAttack() { return m_isAttack; }

			/// @brief �U�����q�b�g���Ă��邩�H
			/// @return �q�b�g���Ă����true �����łȂ���� false
			const bool IsHit() { return m_isHit; }

			/// @brief ���s
			void Execution();
		private:
			/// @brief �U�������s
			void ExecuteAttack();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �U����
			int m_attackPower = 0;
			/// @brief �U������܂ł̃^�C�}�[
			float m_attackTimer = 0.0f;
			/// @brief �U�����s�������̔���
			bool m_isAttack = false;
			/// @brief �U�����������Ă��邩�̔���
			bool m_isHit = false;

			/// @brief �G�N���X
			Enemy* m_enemy = nullptr;
			/// @brief �h�q�Ώۂ̃N���X
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
