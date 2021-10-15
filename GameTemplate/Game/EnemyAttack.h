#pragma once
#include "Enemy.h"


namespace mainGame {

	namespace defensiveTarget{

		class DefensiveTarget;
	}

	namespace enemy {

		/// @brief �G�̍U���𐧌䂷��N���X
		class Attack
		{
		public:
			Attack();
			~Attack();
			/// @brief ������
			void Init(const EnEnemyType& type);
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

			/// @brief �h�q�Ώۂ̃N���X
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
