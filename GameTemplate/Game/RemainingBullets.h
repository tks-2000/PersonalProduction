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
			/// @brief �������t���O
			bool m_isInitd = false;

			/// @brief �e�ۂ̃t�H���g
			render::font::FontRender* m_bulletsFont = nullptr;
			/// @brief �c�e���̃t�H���g
			render::font::FontRender* m_remainingBulletsNumFont = nullptr;
			/// @brief �v���C���[
			player::Player* m_player = nullptr;
		};
	}
}
