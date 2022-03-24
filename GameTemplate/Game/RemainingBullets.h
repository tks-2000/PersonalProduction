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
			void HideUI();
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;

		
			/// @brief 残弾数のフォント
			render::font::FontRender* m_remainingBulletsNumFont = nullptr;
			/// @brief 残弾表示の下地画像
			render::sprite::SpriteRender* m_remainingBulletsBaseSprite = nullptr;
			/// @brief 残弾表示の画像
			render::sprite::SpriteRender* m_remainingBulletsSprite = nullptr;
			/// @brief プレイヤー
			player::Player* m_player = nullptr;
		};
	}
}
