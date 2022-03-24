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

			
		}

		void GameUI::Init()
		{
			

			m_oenedItem.Init();

			m_baseEndurance.Init();

			m_timeLimit.Init();

			m_remainingBullets.Init();
			m_miniMap.Init();
			

			m_gameEndSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

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
			m_miniMap.Execution();
			

			if (m_gameEndSpriteFlag == false &&
				m_gameScene->GetGameSceneState() == enGameSceneClear ||
				m_gameScene->GetGameSceneState() == enGameSceneOver
				) 
			{
				DisplayGameEndSprite();
			}

			
			if (m_gameEndSpriteFlag == true) {
				GameEndSpriteExecution();
			}
		}

		

		void GameUI::DisplayGameEndSprite()
		{
			if (m_gameScene->GetGameSceneState() == enGameSceneClear) {
				m_gameEndSprite->Init("Assets/Image/GAMECLEAR.dds", GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}
			if (m_gameScene->GetGameSceneState() == enGameSceneOver) {
				m_gameEndSprite->Init("Assets/Image/GAMEOVER.dds", GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}

			m_gameEndSpriteFlag = true;
		}

		

		void GameUI::GameEndSpriteExecution()
		{
			m_gameEndSprite->Execute();
			m_oenedItem.HideUI();
			m_baseEndurance.HIdeUI();
			m_remainingBullets.HideUI();
			m_timeLimit.HideUI();
			m_miniMap.HideUI();
		}
	}
}