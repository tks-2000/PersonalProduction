#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace ui {

		class OwnedItem
		{
		public:
			OwnedItem();
			~OwnedItem();
			void Init();
			void Execution();

		private:

			bool m_isInitd = false;

			render::font::FontRender* m_itemSlotFont[3] = { nullptr };

			Vector2 m_itemSlotFontPos[3];

			Vector4 m_itemSlotFontColor[3];

			player::Player* m_player = nullptr;

			render::sprite::SpriteRender* m_selectSprite = nullptr;

			Vector3 m_selectSpritePos = g_vec3Zero;
		};
	}
}
