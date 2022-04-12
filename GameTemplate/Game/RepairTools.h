#pragma once
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief 拠点の修理道具
		class RepairTools : public Item
		{
		public:
			/// @brief 効果発動
			void Activation() override;

		private:
			/// @brief データを初期化
			void InitData() override;
			/// @brief 出現
			void Spawn() override;
			/// @brief 効果発動中の処理
			void Efficacy() override;

			/// @brief 防衛対象
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		};
	}
}
