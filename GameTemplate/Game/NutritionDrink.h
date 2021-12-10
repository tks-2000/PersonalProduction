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
			/// @brief 効果発動時の処理
			void Activation();

		private:
			/// @brief 個別の情報の初期化
			void InitData();

			/// @brief 効果発動中の処理
			void Efficacy();

			/// @brief 敵との接触を判定
			void EnemyCollision();

			/// @brief 敵の配列のポインタ
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief 敵生成器
			enemy::Generator* m_enemyGenerator = nullptr;
		};
	}
}
