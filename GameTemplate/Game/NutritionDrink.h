#pragma once
#include "Item.h"

namespace mainGame {

	namespace enemy {
		class Enemy;
		class Generator;
	}

	namespace item {
		class NutritionDrink : public Item
		{
		public:

			~NutritionDrink();
			/// @brief ���ʔ������̏���
			void Activation();

		private:
			/// @brief �ʂ̏��̏�����
			void InitData();

			/// @brief ���ʔ������̏���
			void Efficacy();

			/// @brief �G�Ƃ̐ڐG�𔻒�
			void EnemyCollision();

			/// @brief �G�̔z��̃|�C���^
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief �G������
			enemy::Generator* m_enemyGenerator = nullptr;
		};
	}
}
