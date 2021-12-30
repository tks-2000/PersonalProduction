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
			bool m_isInitd = false;

			render::sprite::SpriteRender* m_timerBaseSprite = nullptr;

			render::font::FontRender* m_timeFont = nullptr;

			render::font::FontRender* m_timerNumFont = nullptr;

			timer::Timer* m_timer = nullptr;
		};

	}
}