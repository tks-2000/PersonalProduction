#pragma once

namespace mainGame {
	namespace item {
		class Item;
	}

	namespace player {
		class ItemSlot
		{
		public:
			ItemSlot();
			~ItemSlot();

			void Init();

			void Execution();

			/// @brief スロットにアイテムを設定
			/// @param item 設定するアイテムのアドレス
			/// @return trueでスロットに設定できた falseでスロットに設定できなかった
			bool SetItem(item::Item* item);

			/// @brief 持っているアイテムを使う
			/// @param slotNo 使用するアイテムスロット番号
			void UseItem(const int slotNo);
			
		private:

			void ItemSelect();

			bool m_isInitd = false;

			enum { 
				MIN_ITEM_NUM = 0,
				MAX_ITEM_NUM = 3 
			};
			
			/// @brief 選択しているアイテム番号
			int m_selectNo = 0;

			std::vector<item::Item*> m_items;
		};

	}
}
