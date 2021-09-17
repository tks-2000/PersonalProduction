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
	}

	bool Game::Start()
	{
		m_unityChanModel = NewGO<SkinModelRender>(0);
		m_unityChanModel->Init("Assets/modelData/unityChan.tkm");
		m_backGroundModel = NewGO<SkinModelRender>(0);
		m_backGroundModel->Init("Assets/modelData/bg/bg.tkm");
		m_lig->SetHemiSphereLifhtGroundColor({ 0.5f,0.0f,0.0f });
		m_lig->SetHemiSphereLifhtSkyColor({ 0.0f,0.0f,0.5f });
		m_lig->SetPointLightColor(0, { 0.0f,1.0f,0.0f });
		m_lig->SetPointLightRange(0, 300.0f);
		m_lig->SetSpotLightColor(0,{ -1.0f,-1.0f,-1.0f });
		return true;
	}

	void Game::Update()
	{

	}
}