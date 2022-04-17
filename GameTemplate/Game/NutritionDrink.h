#pragma once
#include "Item.h"

namespace mainGame {

	namespace enemy {
		class Enemy;
		class Generator;
	}

	namespace item {

		/// @brief プレイヤーを強化する栄養ドリンク
		class NutritionDrink : public Item
		{
		public:

			~NutritionDrink();
			/// @brief 効果発動時の処理
			void Activation() override;

		private:
			/// @brief 個別の情報の初期化
			void InitData() override;

			/// @brief 出現時の処理
			void Spawn() override;

			/// @brief 効果発動中の処理
			void Efficacy() override;

			/// @brief 敵との接触を判定
			void EnemyCollision();

			/// @brief 効果終了時の処理
			void DeleteEfficacy();

			/// @brief 敵の配列のポインタ
			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			/// @brief 敵生成器
			enemy::Generator* m_enemyGenerator = nullptr;

			/// @brief エフェクト
			render::effect::EffectRender* m_powerUpEffect = nullptr;
		};
	}
}
