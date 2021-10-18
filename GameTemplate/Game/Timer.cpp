#include "stdafx.h"
#include "Timer.h"

namespace mainGame {
	namespace timer {
		Timer::Timer()
		{
			m_isInitd = false;
			
		}

		Timer::~Timer()
		{
			
		}

		void Timer::Init()
		{
			if (m_isInitd == true) {
				return;
			}

			m_stastTimer = 3.0f;
			m_inGameTimer = 120.0f;

			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			int time = m_stastTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->Init(conversion.c_str());
			m_timeFontPos = { 0.0f,300.0f };
			m_timeFont->SetPosition(m_timeFontPos);

			m_isInitd = true;
		}

		void Timer::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			switch (m_state)
			{
			case enTimerStart: {
				ExecuteStartTimer();
			}break;
			case enTimerExecute: {
				ExecuteInGameTimer();
			}break;
			case enTimerEnd: {

			}break;
			default:
				break;
			}

			m_timeFont->Execution();
		}

		void Timer::ExecuteStartTimer()
		{
			m_stastTimer -= g_gameTime->GetFrameDeltaTime();

			int time = m_stastTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->SetText(conversion.c_str());

			if (m_stastTimer <= 0.0f) {
				m_state = enTimerExecute;
				return;
			}
			
			
		}

		void Timer::ExecuteInGameTimer()
		{
			m_inGameTimer -= g_gameTime->GetFrameDeltaTime();

			int time = m_inGameTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->SetText(conversion.c_str());

			if (m_inGameTimer <= 0.0f) {
				m_state = enTimerEnd;
				return;
			}
		}
	}
}