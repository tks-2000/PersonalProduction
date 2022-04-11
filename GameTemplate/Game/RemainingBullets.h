#pragma once

namespace mainGame {
	namespace player {
		class Player;
	}
	namespace ui {
		/// @brief �c�e�̕\�����s���N���X
		class RemainingBullets
		{
		public:
			RemainingBullets();
			~RemainingBullets();
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief UI���\��
			void HideUI();
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �c�e���̃t�H���g
			render::font::FontRender* m_remainingBulletsNumFont = nullptr;
			/// @brief �c�e�\���̉摜
			render::sprite::SpriteRender* m_remainingBulletsSprite = nullptr;
			/// @brief �v���C���[
			player::Player* m_player = nullptr;
		};
	}
}
