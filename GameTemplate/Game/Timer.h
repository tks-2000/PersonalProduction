#pragma once

namespace mainGame {
	namespace timer {

		enum EnTimerState {
			enTimerStart,
			enTimerExecute,
			enTimerEnd,
			enTimerStateNum
		};

		class Timer : public IGameObject
		{
		public:
			Timer();
			~Timer();

			void Init();
			void Execution();

			const EnTimerState& GetTimerState() { return m_state; }
		private:
			void ExecuteStartTimer();
			void ExecuteInGameTimer();


			bool m_isInitd = false;

			float m_inGameTimer = 0.0f;

			float m_stastTimer = 0.0f;

			int m_timeNum = 0;

			EnTimerState m_state = enTimerStart;

			render::font::FontRender* m_timeFont = nullptr;

			Vector2 m_timeFontPos = g_vec2Zero;
		};
	}
}
