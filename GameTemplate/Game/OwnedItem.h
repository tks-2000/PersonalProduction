#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace ui {

		/// @brief アイテムスロットの数
		static const int ITEM_SLOT_NUM = 3;

		/// @brief 所有アイテムを表示するクラス
		class OwnedItem
		{
		public:
			OwnedItem();
			~OwnedItem();
			void Init();
			void Execution();
			void HideUI();

		private:
			/// @brief アイテム画像を作成
			/// @param slotNum 作成するスロット番号
			void CreateItemSprite(const int slotNum);

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief アイテムスロットの下地の画像
			render::sprite::SpriteRender* m_itemSlotBaseSprite = nullptr;
			/// @brief アイテムスロットの下地の枠の画像
			render::sprite::SpriteRender* m_itemSlotBaseFrame = nullptr;
			/// @brief アイテムスロットの画像
			render::sprite::SpriteRender* m_itemSlotSprite[ITEM_SLOT_NUM] = { nullptr };
			/// @brief アイテムの画像
			render::sprite::SpriteRender* m_itemSprite[ITEM_SLOT_NUM] = { nullptr };
			/// @brief アイテムスロット画像の表示フラグの配列
			bool m_itemSpriteFlag[ITEM_SLOT_NUM] = { false };
			/// @brief プレイヤーが選択しているアイテムを示す画像
			render::sprite::SpriteRender* m_selectSprite = nullptr;
			/// @brief プレイヤー
			player::Player* m_player = nullptr;
			/// @brief 選択画像の座標
			Vector3 m_selectSpritePos = g_vec3Zero;
		};
	}
}
