#include "stdafx.h"
#include "Game.h"

namespace MainGame {

	Game::Game()
	{
		//m_lig = FindGO<Render::Lighting>(Render::LIGHTING_NAME);
	}

	Game::~Game()
	{
		DeleteGO(m_unityChanModel);
		DeleteGO(m_backGroundModel);
	}

	bool Game::Start()
	{
		m_unityChanModel = NewGO<Render::SkinModelRender>(0);
		m_unityChanModel->Init("Assets/modelData/unityChan.tkm");
		m_unityChanModel->CreateShadow();
		m_unityChanModel2 = NewGO<Render::SkinModelRender>(0);
		m_unityChanModel2->Init("Assets/modelData/unityChan.tkm");
		m_unityChanModel2->CreateShadow();
		m_backGroundModel = NewGO<Render::SkinModelRender>(0);
		m_backGroundModel->Init("Assets/modelData/bg/bg.tkm");
		//m_backGroundModel->CreateShadow();
		
		return true;
	}

	void Game::Update()
	{
		m_pos.x -= g_pad[0]->GetLStickXF();
		m_pos.z -= g_pad[0]->GetLStickYF();

		m_unityChanModel->SetPosition(m_pos);

		if (g_pad[0]->IsTrigger(enButtonA)) {
			DeleteGO(m_unityChanModel2);
		}
	}
}