#include "stdafx.h"
#include "GameUI.h"

namespace mainGame {
	namespace ui {

		const int GAME_END_SPRITE_WIDTH = 1000;

		const int GAME_END_SPRITE_HEIGHT = 200;

		GameUI::GameUI()
		{

		}

		GameUI::~GameUI()
		{
			

			DeleteGO(m_gameEndSprite);

			DeleteGO(m_startFont);
		}

		void GameUI::Init()
		{
			

			m_oenedItem.Init();

			m_baseEndurance.Init();

			m_timeLimit.Init();

			m_remainingBullets.Init();

			m_startFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);

			m_gameEndSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_game = FindGO<Game>(GAME_NAME);

			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);

			m_isInitd = true;
		}

		void GameUI::Execution()
		{
			if (m_isInitd == false) {
				return;
			}


			m_oenedItem.Execution();

			m_baseEndurance.Execution();

			m_timeLimit.Execution();

			m_remainingBullets.Execution();

			if (m_startFontFlag == false && m_timer->GetTimerState() == timer::enTimerExecute) {
				DisplayStartFont();
			}

			if (m_gameEndSpriteFlag == false &&
				m_game->GetGameState() == enGameClear ||
				m_game->GetGameState() == enGameOver
				) 
			{
				DisplayGameEndSprite();
			}

			if (m_startFontFlag == true) {
				StartFontExecution();
			}
			if (m_gameEndSpriteFlag == true) {
				GameEndSpriteExecution();
			}
		}

		void GameUI::DisplayStartFont()
		{
			m_startFont->Init(L"Start");

			m_startFontFlag = true;
		}

		void GameUI::DisplayGameEndSprite()
		{
			if (m_game->GetGameState() == enGameClear) {
				m_gameEndSprite->Init("Assets/Image/GAMECLEAR.dds", GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}
			if (m_game->GetGameState() == enGameOver) {
				m_gameEndSprite->Init("Assets/Image/GAMEOVER.dds", GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}

			m_gameEndSpriteFlag = true;
		}

		void GameUI::StartFontExecution()
		{
			m_startFontDisplayTimer += g_gameTime->GetFrameDeltaTime();

			if (m_startFontDisplayTimer > 3.0f) {
				m_startFont->SetColor({ 0.0f,0.0f,0.0f,0.0f });
				m_startFontFlag = false;
			}

			m_startFont->Execution();
		}

		void GameUI::GameEndSpriteExecution()
		{
			m_gameEndSprite->Execute();
		}
	}
}