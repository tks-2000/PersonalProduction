#pragma once

namespace mainGame {
	namespace ui {
		class TimeLimit
		{
		public:
			TimeLimit();
			~TimeLimit();
			void Init();
			void Execution();
		private:

			void CountDown();

			bool m_isInitd = false;

			bool m_isCountDown = false;

			render::sprite::SpriteRender* m_count[3] = { nullptr };

			

			render::sprite::SpriteRender* m_go = nullptr;

			float m_goSpriteDisplayTimer = 0.0f;

			render::sprite::SpriteRender* m_timerBaseSprite = nullptr;

			render::sprite::SpriteRender* m_timerBaseFrame = nullptr;

			render::font::FontRender* m_timeFont = nullptr;

			render::font::FontRender* m_timerNumFont = nullptr;

			timer::Timer* m_timer = nullptr;

			GameScene* m_gameScene = nullptr;
		};

	}
}