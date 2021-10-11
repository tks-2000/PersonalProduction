#include "stdafx.h"
#include "Game.h"

namespace mainGame {

	Game::Game()
	{
		//m_lig = FindGO<Render::Lighting>(Render::LIGHTING_NAME);
		m_player = NewGO<player::Player>(PRIORITY_VERYLOW, player::PLAYER_NAME);
		m_gameCamera = NewGO<GameCamera>(0, GAME_CAMERA_NAME);
		
	}

	Game::~Game()
	{
		DeleteGO(m_unityChanModel);
		DeleteGO(m_backGroundModel);
	}

	bool Game::Start()
	{
		m_pause = false;
		//m_unityChanAnimationClip[enIdle].Load("Assets/animData/idle.tka");
		//m_unityChanAnimationClip[enIdle].SetLoopFlag(true);
		//m_unityChanAnimationClip[enWark].Load("Assets/animData/walk.tka");
		//m_unityChanAnimationClip[enWark].SetLoopFlag(true);
		//m_unityChanModel = NewGO<Render::SkinModelRender>(1);
		//m_unityChanModel->Init(
		//	"Assets/modelData/unityChan.tkm",
		//	"Assets/modelData/unityChan.tks",
		//	m_unityChanAnimationClip,
		//	enAnimationNum,
		//	enModelUpAxisY
		//);
		//m_unityChanModel->CreateShadow();
		m_unityChanModel2 = NewGO<render::model::SkinModelRender>(1);
		m_unityChanModel2->Init("Assets/modelData/unityChan.tkm");
		//_unityChanModel2->CreateShadow();
		m_backGroundModel = NewGO<render::model::SkinModelRender>(0);
		m_backGroundModel->Init("Assets/modelData/bg/testStage.tkm");
		//m_backGroundModel->CreateShadow();
		m_backGroundModel2 = NewGO<render::model::SkinModelRender>(1);
		m_backGroundModel2->Init("Assets/modelData/bg/testStage.tkm");
		m_backGroundModel2->CreateShadow();
		m_backGroundModel2->SetPosition({ 0.0f,-1000.0f,0.0f });
		
		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);
		m_sampleSprite->Init("Assets/image/sample.dds",100,100);
		m_sampleSprite->SetPosition({ 500.0f,300.0f,0.0f });

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
		m_backGroundModel->Execution();
		m_backGroundModel2->Execution();
		if (g_pad[0]->IsTrigger(enButtonA)) {
			DeleteGO(m_sampleSprite);
			m_isDead = true;
		}
		if (m_isDead == false) {
			m_sampleSprite->Execute();
		}

		m_player->Execution();
		m_gameCamera->Execution();

		m_gameCamera->SetCameraTarget(m_player->GetPlayerPosition());
	}

	void Game::Pause()
	{

	}
}