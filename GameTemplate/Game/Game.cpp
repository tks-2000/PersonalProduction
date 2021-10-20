#include "stdafx.h"
#include "Game.h"

namespace mainGame {

	Game::Game()
	{
		AllNew();

		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
	}

	Game::~Game()
	{
		DeleteGO(m_unityChanModel);
		DeleteGO(m_backGroundModel);
	}

	void Game::Init()
	{
		m_pause = false;

		
		//m_enemy->Init(enemy::enEnemyTypeNormal, { 0.0f,500.0f,1000.0f });

		m_enemyGenerator->Init({ 0.0f,1000.0f,0.0f });

		m_stage->Init();

		m_timer->Init();

		m_defensiveTarget->Init();

		m_unityChanModel2->Init("Assets/modelData/unityChan/unityChan.tkm");


		m_sampleSprite->Init("Assets/image/sample.dds", 100, 100);
		m_sampleSprite->SetPosition({ 500.0f,300.0f,0.0f });


		m_sampleFont->Init(L"test");
		m_sampleFont->SetPosition({ -500.0f, 300.0f });

		m_state = enGameStart;
		m_isDead = false;
	}

	bool Game::Start()
	{
		
		Init();
		

		return true;
	}

	void Game::Update()
	{
		if (m_pause == true) {
			Pause();
			if (g_pad[0]->IsTrigger(enButtonStart)) {
				m_pause = false;
				m_renderingEngine->SetLightFlag(true);
			}
			return;
		}
		else {
			if (g_pad[0]->IsTrigger(enButtonStart)) {
				m_pause = true;
				m_renderingEngine->SetLightFlag(false);
				return;
			}
		}

		if (m_timer->GetTimerState() == timer::enTimerEnd) {
			m_renderingEngine->SetLightFlag(false);
			m_timer->Execution();
			return;
		}

		switch (m_state)
		{
		case enGameStart: {
			GameStartExecution();
		}break;
		case enGameInProgress: {
			InGameExecution();
		}break;
		case enGameClear: {

		}break;
		case enGameOver: {
			GameOverExecution();
		}break;
		case enGameStateNum: {

		}break;
		default:
			break;
		}
		
		if (m_state != enGameOver) {

			int hp = m_defensiveTarget->GetDefensiveTargetHp();
			std::wstring conversion;
			conversion = std::to_wstring(hp);
			m_sampleFont->SetText(conversion.c_str());
			m_sampleSprite->Execute();
			m_sampleFont->Execution();
			m_unityChanModel2->Execution();
		}


	}

	void Game::GameStartExecution()
	{
		m_player->Execution();
		m_gameCamera->SetCameraTarget(m_player->GetPlayerPosition());
		m_gameCamera->Execution();
		m_defensiveTarget->Execution();
		m_enemyGenerator->Execute();
		m_timer->Execution();
	}

	void Game::InGameExecution()
	{
		m_player->Execution();
		m_gameCamera->SetCameraTarget(m_player->GetPlayerPosition());
		m_gameCamera->Execution();
		m_defensiveTarget->Execution();
		m_enemyGenerator->Execute();
		m_timer->Execution();

		if (m_defensiveTarget->IsBreak() == true) {
			m_state = enGameOver;
		}
	}

	void Game::GameOverExecution()
	{
		
		m_renderingEngine->SetLightFlag(false);

		
		if (m_isDead == true) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				AllNew();
				Init();
			}
		}
		else {
			m_sampleFont->SetText(L"GAME OVER");
			m_sampleFont->Execution();
			if (g_pad[0]->IsTrigger(enButtonX)) {
				DeleteGO(m_sampleSprite);
				DeleteGO(m_sampleFont);
				DeleteGO(m_unityChanModel2);
				AllDelete();
				m_state = enGameOver;
				m_isDead = true;
			}
		}
	}

	void Game::AllNew()
	{
		m_player = NewGO<player::Player>(PRIORITY_VERYLOW, player::PLAYER_NAME);
		m_gameCamera = NewGO<GameCamera>(PRIORITY_VERYLOW, GAME_CAMERA_NAME);
		m_defensiveTarget = NewGO<defensiveTarget::DefensiveTarget>(PRIORITY_VERYLOW, defensiveTarget::DEFENSIVE_TARGET_NAME);
		//m_enemy = NewGO<enemy::Enemy>(PRIORITY_VERYLOW,enemy::ENEMY_NAME);
		m_enemyGenerator = NewGO<enemy::Generator>(PRIORITY_VERYLOW, enemy::ENEMY_GENERATOR_NAME);
		m_stage = NewGO<stage::Stage>(PRIORITY_VERYLOW, stage::STAGE_NAME);
		m_timer = NewGO<timer::Timer>(PRIORITY_VERYLOW, timer::TIMER_NAME);

		m_unityChanModel2 = NewGO<render::model::SkinModelRender>(1);
		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);
		m_sampleFont = NewGO<render::font::FontRender>(0);
	}

	void Game::AllDelete()
	{
		DeleteGO(m_gameCamera);
		DeleteGO(m_enemyGenerator);
		DeleteGO(m_player);
		DeleteGO(m_defensiveTarget);
		DeleteGO(m_stage);
		DeleteGO(m_timer);
	}

	void Game::Pause()
	{

	}
}