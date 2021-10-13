#include "stdafx.h"
#include "Game.h"

namespace mainGame {

	Game::Game()
	{
		m_player = NewGO<player::Player>(PRIORITY_VERYLOW, player::PLAYER_NAME);
		m_gameCamera = NewGO<GameCamera>(PRIORITY_VERYLOW, GAME_CAMERA_NAME);
		m_defensiveTarget = NewGO<defensiveTarget::DefensiveTarget>(PRIORITY_VERYLOW,defensiveTarget::DEFENSIVE_TARGET_NAME);
		m_enemy = NewGO<enemy::Enemy>(PRIORITY_VERYLOW,enemy::ENEMY_NAME);
		m_stage = NewGO<stage::Stage>(PRIORITY_VERYLOW, stage::STAGE_NAME);

		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);
		m_sampleFont = NewGO<render::font::FontRender>(0);
	}

	Game::~Game()
	{
		DeleteGO(m_unityChanModel);
		DeleteGO(m_backGroundModel);
	}

	bool Game::Start()
	{
		m_pause = false;

		m_defensiveTarget->Init();
		m_enemy->Init();
		m_stage->Init();
		
		m_unityChanModel2 = NewGO<render::model::SkinModelRender>(1);
		m_unityChanModel2->Init("Assets/modelData/unityChan/unityChan.tkm");
		//_unityChanModel2->CreateShadow();
		//m_backGroundModel = NewGO<render::model::SkinModelRender>(0);
		//m_backGroundModel->Init("Assets/modelData/bg/testStage.tkm");
		//m_backGroundModel->CreateShadow();
		m_backGroundModel2 = NewGO<render::model::SkinModelRender>(1);
		m_backGroundModel2->Init("Assets/modelData/bg/testStage.tkm");
		m_backGroundModel2->CreateShadow();
		m_backGroundModel2->SetPosition({ 0.0f,-1000.0f,0.0f });

		
		m_sampleSprite->Init("Assets/image/sample.dds", 100, 100);
		m_sampleSprite->SetPosition({ 500.0f,300.0f,0.0f });

		
		m_sampleFont->Init(L"test");
		m_sampleFont->SetPosition({ -500.0f, 300.0f });

		return true;
	}

	void Game::Update()
	{
		if (m_pause == true) {
			Pause();
			if (g_pad[0]->IsTrigger(enButtonStart)) {
				m_pause = false;
			}
			return;
		}
		else {
			if (g_pad[0]->IsTrigger(enButtonStart)) {
				m_pause = true;
			}
		}

		m_unityChanModel2->Execution();
		//m_backGroundModel->Execution();
		m_backGroundModel2->Execution();
		

		if (g_pad[0]->IsTrigger(enButtonA)) {
			DeleteGO(m_sampleSprite);
			DeleteGO(m_sampleFont);
			
			m_isDead = true;
		}
		if (m_isDead == false) {
			int hp = m_defensiveTarget->GetDefensiveTargetHp();
			std::wstring conversion;
			conversion = std::to_wstring(hp);
			m_sampleFont->SetText(conversion.c_str());
			m_sampleSprite->Execute();
			m_sampleFont->Execution();
		}

		m_player->Execution();
		m_gameCamera->SetCameraTarget(m_player->GetPlayerPosition());
		m_gameCamera->Execution();
		m_defensiveTarget->Execution();
		m_enemy->Execution();
		
	}

	void Game::Pause()
	{

	}
}