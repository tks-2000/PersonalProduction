#pragma once

namespace mainGame {
	namespace ui {

		static const int NUM_SPRITE_NUM = 3;

		class TimeLimit
		{
		public:
			TimeLimit();
			~TimeLimit();
			void Init();
			void Execution();

			void HideUI();
		private:

			void CountDown();

			bool m_isInitd = false;

			bool m_isCountDown = false;

			render::sprite::SpriteRender* m_count[NUM_SPRITE_NUM] = { nullptr };

			

			render::sprite::SpriteRender* m_go = nullptr;

			float m_goSpriteDisplayTimer = 0.0f;

			render::sprite::SpriteRender* m_timerBaseSprite = nullptr;

			render::sprite::SpriteRender* m_timerBaseFrame = nullptr;

			render::font::FontRender* m_timeFont = nullptr;

			render::font::FontRender* m_timerNumFont = nullptr;

			timer::Timer* m_timer = nullptr;

			GameScene* m_gameScene = nullptr;

			sound::SoundPlayer* m_soundPlayer = nullptr;

			int m_countSoundID = 0;

			int m_goSoundID = 0;

			bool m_isPlayCountSE[NUM_SPRITE_NUM] = { false };

			
		};

	}
}