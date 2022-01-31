#include "stdafx.h"
#include "Game.h"

namespace mainGame {

	Game::Game()
	{
		m_soundPlayer = NewGO<sound::SoundPlayer>(PRIORITY_VERYLOW, sound::SOUND_PLAYER_NAME);	
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
	}

	Game::~Game()
	{
		
	}

	void Game::Init()
	{

	}

	bool Game::Start()
	{

		TitleSceneStart();
		m_isInitd = true;
		return true;
	}

	void Game::Update()
	{
		
		//–¢‰Šú‰»‚È‚çŽÀs‚µ‚È‚¢
		if (m_isInitd == false) {
			return;
		}

		if (m_state == enTitleScene) {
			m_title->Execution();
		}

		if (m_state == enGameInProgress) {
			m_gameScene->Execution();
		}
		
	}

	void Game::TitleSceneStart()
	{
		m_title = NewGO<title::Title>(PRIORITY_VERYLOW, title::TITLE_NAME);
		m_title->Init();
		m_state = enTitleScene;
	}

	void Game::DeleteTitleScene()
	{
		DeleteGO(m_title);
	}

	void Game::GameSceneStart()
	{
		m_gameScene = NewGO<GameScene>(PRIORITY_VERYLOW, GAME_SCENE_NAME);
		m_gameScene->Init();
		m_state = enGameInProgress;
	}

	void Game::DeleteGameScene()
	{
		DeleteGO(m_gameScene);
	}
}