#include "stdafx.h"
#include "Game.h"

namespace mainGame {

	Game::Game()
	{
		//AllNew();
		m_title = NewGO<title::Title>(PRIORITY_VERYLOW, title::TITLE_NAME);
		m_effect.Init(u"Assets/effect/kick.efk");
		m_effect.SetPosition({ 0.0f,0.0f,0.0f });
		m_state = enTitleScene;
		m_isDead = true;
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
	}

	Game::~Game()
	{
		
	}

	void Game::Init()
	{

		
		m_pause = false;

		m_miniMap->Init();

		m_player->Init();

		m_defensiveTarget->Init();

		m_gameCamera->Init();

		m_enemyGenerator->Init({ 0.0f,0.0f,0.0f });

		m_stage->Init();

		m_timer->Init();

		

		m_unityChanModel2->Init("Assets/modelData/unityChan/unityChan.tkm");


		m_sampleSprite->Init("Assets/image/sight.dds", 100, 100);
		m_sampleSprite->SetPosition({ 0.0f,0.0f,0.0f });
		m_sampleSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

		

		m_sound->Init(L"Assets/sound/bgm/SpecialBgm.wav");
		m_sound->SetVolume(1.0f);
		//m_sound->Play(true);

		m_state = enGameStart;

		m_nvmMesh.Init("Assets/nvmData/stage3.tkn");

		m_itemGenerator->Init();

		m_gameUI->Init();

		
		m_isDead = false;
	}

	bool Game::Start()
	{
		
		//Init();
		m_title->Init();
		m_isInitd = true;
		
		return true;
	}

	void Game::Update()
	{
		if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonB)) {
			m_effect.Play();
			
		}
		m_effect.Update();
		//未初期化なら実行しない
		if (m_isInitd == false) {
			return;
		}

		if (m_state == enGameInProgress) {
			//ポーズ中は実行しない
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
		}


		switch (m_state)
		{
		case enTitleScene: {
			m_title->Execution();
		}break;
		case enGameStart: {
			GameStartExecution();
		}break;
		case enGameInProgress: {
			InGameExecution();
		}break;
		case enGameClear: {
			GameClearExecution();
		}break;
		case enGameOver: {
			GameOverExecution();
		}break;
		case enGameStateNum: {

		}break;
		default:
			break;
		}


		
		

		if (m_isDead == false) {
			m_player->Execution();
			m_enemyGenerator->Execute();
			m_gameCamera->Execution();
			m_miniMap->Execution();
			m_itemGenerator->Execution();
			m_gameUI->Execution();
			m_defensiveTarget->Execution();

			if (m_gameCamera->GetCameraMode() == enCameraModeTps) {
				m_sampleSprite->FadeOut(2.0f);
			}
			else {
				m_sampleSprite->FadeIn(2.0f);
			}
			m_sampleSprite->Execute();
		}
		
	}

	void Game::GameSceneStart()
	{
		AllNew();
		Init();
	}

	void Game::SetGameOver()
	{
		m_renderingEngine->SetLightFlag(false);

		m_state = enGameOver;
	}

	void Game::GameStartExecution()
	{
		m_timer->Execution();
	}

	void Game::InGameExecution()
	{
		
		
		m_timer->Execution();

		if (m_timer->GetTimerState() == timer::enTimerEnd) {
			m_state = enGameClear;
		}
		if (m_defensiveTarget->IsBreak() == true) {
			m_state = enGameOver;
		}
	}

	void Game::GameClearExecution()
	{
		m_renderingEngine->SetLightFlag(false);


		if (m_isDead == true) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				
			}
		}
		else {
			
			if (g_pad[0]->IsTrigger(enButtonX)) {
				DeleteGO(m_sampleSprite);
				
				DeleteGO(m_unityChanModel2);
				AllDelete();
				
				m_isDead = true;
				m_title = NewGO<title::Title>(PRIORITY_VERYLOW, title::TITLE_NAME);
				m_title->Init();
				m_state = enTitleScene;
			}
		}
	}

	void Game::GameOverExecution()
	{
		
		m_renderingEngine->SetLightFlag(false);

		
		if (m_isDead == true) {
			if (g_pad[0]->IsTrigger(enButtonA)) {
				
			}
		}
		else {
			
			if (g_pad[0]->IsTrigger(enButtonX)) {
				DeleteGO(m_sampleSprite);
			
				DeleteGO(m_unityChanModel2);
				AllDelete();
				
				m_isDead = true;
				m_title = NewGO<title::Title>(PRIORITY_VERYLOW, title::TITLE_NAME);
				m_title->Init();
				m_state = enTitleScene;
			}
		}
	}

	void Game::AllNew()
	{
		
		m_miniMap = NewGO<map::MiniMap>(PRIORITY_VERYLOW, map::MINI_MAP_NAME);
		m_player = NewGO<player::Player>(PRIORITY_VERYLOW, player::PLAYER_NAME);
		m_gameCamera = NewGO<GameCamera>(PRIORITY_VERYLOW, GAME_CAMERA_NAME);
		m_defensiveTarget = NewGO<defensiveTarget::DefensiveTarget>(PRIORITY_VERYLOW, defensiveTarget::DEFENSIVE_TARGET_NAME);
		m_enemyGenerator = NewGO<enemy::Generator>(PRIORITY_VERYLOW, enemy::ENEMY_GENERATOR_NAME);
		m_stage = NewGO<stage::Stage>(PRIORITY_VERYLOW, stage::STAGE_NAME);
		m_timer = NewGO<timer::Timer>(PRIORITY_VERYLOW, timer::TIMER_NAME);
		m_itemGenerator = NewGO<item::ItemGenerator>(PRIORITY_VERYLOW, item::ITEM_GENERATOR_NAME);
		m_gameUI = NewGO<ui::GameUI>(PRIORITY_VERYLOW, ui::GAME_UI_NAME);

		m_unityChanModel2 = NewGO<render::model::SkinModelRender>(1);
		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);
		
		m_sound = NewGO<CSoundSource>(PRIORITY_VERYLOW);
	}

	void Game::AllDelete()
	{
		if (m_state == enTitleScene) {
			DeleteGO(m_title);
		}
		DeleteGO(m_gameCamera);
		DeleteGO(m_enemyGenerator);
		DeleteGO(m_player);
		DeleteGO(m_defensiveTarget);
		DeleteGO(m_stage);
		DeleteGO(m_timer);
		DeleteGO(m_sound);
		DeleteGO(m_miniMap);
		DeleteGO(m_itemGenerator);
		DeleteGO(m_gameUI);
	}

	void Game::Pause()
	{

	}
}