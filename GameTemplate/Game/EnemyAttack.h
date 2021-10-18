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

			/// @brief �G�N���X
			Enemy* m_enemy = nullptr;
			/// @brief �h�q�Ώۂ̃N���X
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
