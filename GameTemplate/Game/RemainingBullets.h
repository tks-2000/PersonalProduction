#pragma once

namespace mainGame {
	namespace player {
		class Player;
	}
	namespace ui {
		/// @brief 残弾の表示を行うクラス
		class RemainingBullets
		{
		public:
			RemainingBullets();
			~RemainingBullets();
			/// @brief 初期化
			void Init();
			/// @brief 実行
			void Execution();
			/// @brief UIを非表示
			void HideUI();
		private:
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 残弾数のフォント
			render::font::FontRender* m_remainingBulletsNumFont = nullptr;
			/// @brief 残弾表示の画像
			render::sprite::SpriteRender* m_remainingBulletsSprite = nullptr;
			/// @brief プレイヤー
			player::Player* m_player = nullptr;
		};
	}
}
