#pragma once
#include "ItemResource.h"


namespace mainGame {
	namespace item {
		class Item;
	}

	namespace player {

		/// @brief プレイヤーの持つアイテムを管理するクラス
		class ItemSlot
		{
		public:
			ItemSlot();
			~ItemSlot();

			/// @brief 初期化
			void Init(Player* player);

			/// @brief 実行
			void Execution();

			/// @brief スロットにアイテムを設定
			/// @param item 設定するアイテムのアドレス
			/// @return trueでスロットに設定できた falseでスロットに設定できなかった
			bool SetItem(item::Item* item);

			/// @brief 持っているアイテムを使う
			/// @param slotNo 使用するアイテムスロット番号
			void UseItem(const int slotNo);

			/// @brief 現在選択しているスロット番号を取得
			/// @return 選択しているアイテムスロット番号
			const int GetSelectSlotNum()const { return m_selectNo; }

			/// @brief アイテムを持っているか？
			/// @param slotNum 持っているか調べるスロット番号
			/// @return trueなら持っている falseならもっていない
			bool IsOwnedItem(const int slotNum)const;
			
			/// @brief スロットにあるアイテムの種類を取得
			/// @param slotNum 調べるスロット番号
			/// @return アイテムの種類
			const item::EnItemType& GetItemType(const int slotNum);

		private:

			/// @brief 使用するアイテムスロット選択を行う関数
			void ItemSelect();

			/// @brief 初期化フラグ
			bool m_isInitd = false;

			enum {
				/// @brief アイテムの最小所持数
				MIN_ITEM_NUM = 0,
				/// @brief アイテムの最大所持数
				MAX_ITEM_NUM = 3 
			};
			
			/// @brief 選択しているアイテム番号
			int m_selectNo = 0;
			/// @brief アイテム
			item::Item* m_items[MAX_ITEM_NUM] = { nullptr };
			/// @brief プレイヤー
			Player* m_player = nullptr;
		};

	}
}
