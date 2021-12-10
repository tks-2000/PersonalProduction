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
			/// @brief 初期化フラグ
			bool m_isInitd = false;

			/// @brief 弾丸のフォント
			render::font::FontRender* m_bulletsFont = nullptr;
			/// @brief 残弾数のフォント
			render::font::FontRender* m_remainingBulletsNumFont = nullptr;
			/// @brief プレイヤー
			player::Player* m_player = nullptr;
		};
	}
}
