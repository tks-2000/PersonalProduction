#include "stdafx.h"
#include "Game.h"

namespace MainGame {

	Game::Game()
	{
		m_lig = FindGO<Render::Lighting>(Render::LIGHTING_NAME);
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
		m_backGroundModel = NewGO<Render::SkinModelRender>(0);
		m_backGroundModel->Init("Assets/modelData/bg/bg.tkm");
		
		return true;
	}

	void Game::Update()
	{

	}
}