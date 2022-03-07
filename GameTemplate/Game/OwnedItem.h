#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace ui {

		/// @brief 所有アイテムを表示するクラス
		class OwnedItem
		{
		public:
			OwnedItem();
			~OwnedItem();
			void Init();
			void Execution();

		private:
			/// @brief アイテム画像を作成
			/// @param slotNum 作成するスロット番号
			void CreateItemSprite(const int slotNum);

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief アイテムスロットの下地の画像
			render::sprite::SpriteRender* m_itemSlotBaseSprite = nullptr;

			render::sprite::SpriteRender* m_itemSlotBaseFrame = nullptr;
			/// @brief アイテムスロットの画像
			render::sprite::SpriteRender* m_itemSlotSprite[3] = { nullptr };
			/// @brief アイテムの画像
			render::sprite::SpriteRender* m_itemSprite[3] = { nullptr };
			/// @brief アイテムの画像の表示フラグ
			bool m_itemSpriteFlag[3] = { false };
			/// @brief プレイヤーが選択しているアイテムを示す画像
			render::sprite::SpriteRender* m_selectSprite = nullptr;

			

			

			player::Player* m_player = nullptr;
			

			Vector3 m_selectSpritePos = g_vec3Zero;
		};
	}
}
