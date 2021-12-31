#include "stdafx.h"
#include "TimeLimit.h"

namespace mainGame {
	namespace ui {

		const Vector3 TIMER_BASE_SPRITE_POS = { 0.0f,220.0f,0.0f };

		const int TIMER_BASE_SPRITE_WIDTH = 270;

		const int TIMER_BASE_SPRITE_HEIGHT = 70;

		const Vector2 TIME_FONT_POS = { -125.0f,240.0f };

		const Vector2 TIMER_NUM_FONT_POS = { 25.0f,240.0f };

		TimeLimit::TimeLimit()
		{

		}

		TimeLimit::~TimeLimit()
		{
			DeleteGO(m_timerBaseSprite);
			DeleteGO(m_timeFont);
			DeleteGO(m_timerNumFont);
		}

		void TimeLimit::Init()
		{
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);

			m_timerBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_timerBaseSprite->Init("Assets/Image/WB.dds", TIMER_BASE_SPRITE_WIDTH, TIMER_BASE_SPRITE_HEIGHT);
			m_timerBaseSprite->SetPosition(TIMER_BASE_SPRITE_POS);
			m_timerBaseSprite->SetColor(g_vec4Black);

			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timeFont->Init(L"TIME :");
			m_timeFont->SetPosition(TIME_FONT_POS);

			m_timerNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timerNumFont->Init(L"test");
			m_timerNumFont->SetPosition(TIMER_NUM_FONT_POS);

			m_isInitd = true;
		}

		void TimeLimit::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			std::wstring conversion;
			conversion = std::to_wstring(m_timer->GetTimer());
			m_timerNumFont->SetText(conversion.c_str());
			
			m_timerBaseSprite->Execute();
			m_timeFont->Execution();
			m_timerNumFont->Execution();
		}
	}
}