#include "stdafx.h"
#include "TimeLimit.h"

namespace mainGame {
	namespace ui {

		const Vector3 TIMER_BASE_SPRITE_POS = { 0.0f,255.0f,0.0f };

		const int TIMER_BASE_SPRITE_WIDTH = 270;

		const int TIMER_BASE_SPRITE_HEIGHT = 70;

		const Vector2 TIME_FONT_POS = { -110.0f,280.0f };

		const Vector2 TIMER_NUM_FONT_POS = { 35.0f,280.0f };

		const int NUM_SPRITE_NUM = 3;

		const char* NUM_SPRITE_FILEPATH[NUM_SPRITE_NUM] = {
			"Assets/Image/1.DDS",
			"Assets/Image/2.DDS",
			"Assets/Image/3.DDS"
		};

		const Vector4 UI_SPRITE_START_COLOR = { 1.0f,1.0f,1.0f,0.0f };

		const Vector4 UI_FONT_START_COLOR = { 0.0f,0.0f,0.0f,0.0f };

		const float NUM_SPRITE_WIDTH = 200.0f;

		const float NUM_SPRITE_HEIGHT = 200.0f;

		const float FADE_RATE = 2.5f;

		TimeLimit::TimeLimit()
		{

		}

		TimeLimit::~TimeLimit()
		{
			DeleteGO(m_timerBaseSprite);
			DeleteGO(m_timeFont);
			DeleteGO(m_timerNumFont);
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				DeleteGO(m_count[spriteNum]);
			}

			DeleteGO(m_go);
		}

		void TimeLimit::Init()
		{
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				m_count[spriteNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
				m_count[spriteNum]->Init(NUM_SPRITE_FILEPATH[spriteNum], NUM_SPRITE_WIDTH, NUM_SPRITE_HEIGHT);
				m_count[spriteNum]->SetColor(UI_SPRITE_START_COLOR);
			}


			m_go = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_go->Init("Assets/Image/GO.DDS", NUM_SPRITE_WIDTH, NUM_SPRITE_HEIGHT);
			m_go->SetColor(UI_SPRITE_START_COLOR);

			m_timerBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_timerBaseSprite->Init("Assets/modelData/bg/lace-wood.dds", TIMER_BASE_SPRITE_WIDTH, TIMER_BASE_SPRITE_HEIGHT);
			m_timerBaseSprite->SetPosition(TIMER_BASE_SPRITE_POS);
			//m_timerBaseSprite->SetColor(g_vec4Black);

			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timeFont->Init(L"TIME :");
			m_timeFont->SetPosition(TIME_FONT_POS);
			m_timeFont->SetColor(UI_FONT_START_COLOR);

			m_timerNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timerNumFont->Init(L"test");
			m_timerNumFont->SetPosition(TIMER_NUM_FONT_POS);
			m_timerNumFont->SetColor(UI_FONT_START_COLOR);

			m_isCountDown = true;

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

			if (m_gameScene->GetGameSceneState() == enGameSceneInProgress) {
				m_timerNumFont->SetColor(g_vec4White);
				m_timeFont->SetColor(g_vec4White);
			}

			if (m_isCountDown == true) {
				CountDown();
			}

			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				m_count[spriteNum]->Execute();
			}

			if (m_go->IsOpacity() == true) {
				m_go->FadeOut(FADE_RATE / 5.0f);
			}

			m_go->Execute();
			
			m_timerBaseSprite->Execute();
			m_timeFont->Execution();
			m_timerNumFont->Execution();
		}

		void TimeLimit::CountDown()
		{
			

			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {

				if (spriteNum == m_timer->GetStartTimer() - 1) {
					m_count[spriteNum]->FadeIn(FADE_RATE);
				}
				else {
					m_count[spriteNum]->FadeOut(FADE_RATE);
				}
			}

			if (m_timer->GetStartTimer() == 0) {
				m_go->FadeIn(FADE_RATE);
				m_isCountDown = false;
			}
		}
	}
}