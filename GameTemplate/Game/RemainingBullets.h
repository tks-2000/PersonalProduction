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
			/// @brief �������t���O
			bool m_isInitd = false;

		
			/// @brief �c�e���̃t�H���g
			render::font::FontRender* m_remainingBulletsNumFont = nullptr;
			/// @brief �c�e�\���̉��n�摜
			render::sprite::SpriteRender* m_remainingBulletsBaseSprite = nullptr;
			/// @brief �c�e�\���̉摜
			render::sprite::SpriteRender* m_remainingBulletsSprite = nullptr;
			/// @brief �v���C���[
			player::Player* m_player = nullptr;
		};
	}
}
