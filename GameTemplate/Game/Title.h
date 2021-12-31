#pragma once

namespace mainGame {

	class Game;

	namespace title {
		/// @brief タイトル画面での処理を行うクラス
		class Title : public IGameObject
		{
		public:
			Title();
			~Title();
			void Init();
			void Execution();

		private:
			bool m_isInitd = false;

			render::sprite::SpriteRender* m_titleSprite = nullptr;

			render::font::FontRender* m_font = nullptr;

			Game* m_game = nullptr;
		};
	}
}
