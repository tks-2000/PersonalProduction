#include "stdafx.h"
#include "TimeLimit.h"

namespace mainGame {
	namespace ui {

		const Vector2 TIMER_FONT_POS = { 0.0f,250.0f };

		TimeLimit::TimeLimit()
		{

		}

		TimeLimit::~TimeLimit()
		{
			DeleteGO(m_timerFont);
		}

		void TimeLimit::Init()
		{
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);

			m_timerFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);

			m_timerFont->Init(L"test");

			m_timerFont->SetPosition(TIMER_FONT_POS);

			m_isInitd = true;
		}

		void TimeLimit::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			std::wstring conversion;
			conversion = std::to_wstring(m_timer->GetTimer());
			m_timerFont->SetText(conversion.c_str());
			
			m_timerFont->Execution();
		}
	}
}