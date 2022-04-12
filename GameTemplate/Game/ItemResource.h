#pragma once

namespace mainGame {
	namespace item {
		/// @brief アイテムの種類の列挙型
		enum EnItemType {
			/// @brief 爆弾
			enItemBomb,
			/// @brief 修理道具
			enItemRepairTools,
			/// @brief 栄養ドリンク
			enItemNutritionDrink,
			/// @brief アイテムの種類の数
			enItemTypeNum
		};
	}
}