#pragma once

namespace mainGame {
	namespace player {
		class Player;
	}
	namespace ui {
		class RemainingBullets
		{
		public:
			RemainingBullets();
			~RemainingBullets();
			void Init();
			void Execution();
		private:
			bool m_isInitd = false;

			render::font::FontRender* m_bulletsFont = nullptr;

			render::font::FontRender* m_remainingBulletsNumFont = nullptr;

			player::Player* m_player = nullptr;
		};
	}
}
