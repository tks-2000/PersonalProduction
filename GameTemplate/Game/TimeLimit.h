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

			render::font::FontRender* m_timerFont = nullptr;

			timer::Timer* m_timer = nullptr;
		};

	}
}