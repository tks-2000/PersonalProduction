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
			/// @brief Œø‰Ê”­“®‚Ìˆ—
			void Activation();

		private:
			/// @brief ŒÂ•Ê‚Ìî•ñ‚Ì‰Šú‰»
			void InitData();

			/// @brief Œø‰Ê”­“®’†‚Ìˆ—
			void Efficacy();

			/// @brief “G‚Æ‚ÌÚG‚ğ”»’è
			void EnemyCollision();

			/// @brief “G‚Ì”z—ñ‚Ìƒ|ƒCƒ“ƒ^
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief “G¶¬Ší
			enemy::Generator* m_enemyGenerator = nullptr;
		};
	}
}
