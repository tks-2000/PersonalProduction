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
			void Activation() override;

		private:
			/// @brief �ʂ̏��̏�����
			void InitData() override;

			void Spawn() override;

			/// @brief ���ʔ������̏���
			void Efficacy() override;

			/// @brief �G�Ƃ̐ڐG�𔻒�
			void EnemyCollision();

			/// @brief �G�̔z��̃|�C���^
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief �G������
			enemy::Generator* m_enemyGenerator = nullptr;
		};
	}
}
