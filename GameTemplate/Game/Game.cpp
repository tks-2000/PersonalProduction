#include "stdafx.h"
#include "Game.h"

namespace MainGame {

	Game::Game()
	{
		//m_lig = FindGO<Render::Lighting>(Render::LIGHTING_NAME);
		m_gameCamera = NewGO<GameCamera>(0, GAME_CAMERA_NAME);
	}

	Game::~Game()
	{
		DeleteGO(m_unityChanModel);
		DeleteGO(m_backGroundModel);
	}

	bool Game::Start()
	{
		m_unityChanAnimationClip[enIdle].Load("Assets/animData/idle.tka");
		m_unityChanAnimationClip[enIdle].SetLoopFlag(true);
		m_unityChanAnimationClip[enWark].Load("Assets/animData/walk.tka");
		m_unityChanAnimationClip[enWark].SetLoopFlag(true);
		m_unityChanModel = NewGO<Render::SkinModelRender>(1);
		m_unityChanModel->Init(
			"Assets/modelData/unityChan.tkm",
			"Assets/modelData/unityChan.tks",
			m_unityChanAnimationClip,
			enAnimationNum,
			enModelUpAxisY
		);
		m_unityChanModel->CreateShadow();
		//m_unityChanModel2 = NewGO<Render::SkinModelRender>(1);
		//m_unityChanModel2->Init("Assets/modelData/unityChan.tkm");
		//m_unityChanModel2->CreateShadow();
		m_backGroundModel = NewGO<Render::SkinModelRender>(0);
		m_backGroundModel->Init("Assets/modelData/bg/testStage.tkm");
		//m_backGroundModel->CreateShadow();
		
		return true;
	}

	void Game::Update()
	{
		m_pos.x -= g_pad[0]->GetLStickXF();
		m_pos.z -= g_pad[0]->GetLStickYF();

		m_unityChanModel->SetPosition(m_pos);

		if (g_pad[0]->IsTrigger(enButtonA)) {
			//DeleteGO(m_unityChanModel2);
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			m_unityChanModel->PlayAnimation(enIdle);
		}
		if (g_pad[0]->IsTrigger(enButtonX)) {
			m_unityChanModel->PlayAnimation(enWark);
		}

		m_gameCamera->SetCameraTarget(m_pos);
	}
}