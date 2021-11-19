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
		
	}

	void Game::Init()
	{

		if (m_isInitd == true) {
			return;
		}
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

		m_sampleFont->Init(L"test");
		m_sampleFont->SetPosition({ -500.0f, 300.0f });

		m_sound->Init(L"Assets/sound/bgm/SpecialBgm.wav");
		m_sound->SetVolume(1.0f);
		//m_sound->Play(true);

		m_state = enGameStart;

		m_nvmMesh.Init("Assets/nvmData/stage3.tkn");

		m_isInitd = true;
		m_isDead = false;
	}

	bool Game::Start()
	{
		
		Init();
		

		return true;
	}

	void Game::Update()
	{
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

		//未初期化なら実行しない
		if (m_isInitd == false) {
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


		
		if (m_state != enGameOver && m_state != enGameClear) {
			int hp = m_defensiveTarget->GetDefensiveTargetHp();
			std::wstring conversion;
			conversion = std::to_wstring(hp);
			m_sampleFont->SetText(conversion.c_str());
			
			bool isEnd;
			m_sampleFont->Execution();
			if (g_pad[0]->IsTrigger(enButtonB)) {
				m_pathFinding.Execute(
					m_path,
					m_nvmMesh,
					m_pos,
					m_player->GetPlayerPosition(),
					50.0f,
					200.0f
				);
			}
			m_pos = m_path.Move(
				m_pos,
				10.0f,
				isEnd
			);




			m_unityChanModel2->SetPosition(m_pos);
			m_unityChanModel2->Execution();

			
		}

		if (m_isDead == false) {
			m_player->Execution();
			m_enemyGenerator->Execute();
			m_gameCamera->Execution();
			m_miniMap->Execution();

			if (m_gameCamera->GetCameraMode() == enCameraModeTps) {
				m_sampleSprite->FadeOut(2.0f);
			}
			else {
				m_sampleSprite->FadeIn(2.0f);
			}
			m_sampleSprite->Execute();
		}
		
	}

	void Game::GameStartExecution()
	{
		m_defensiveTarget->Execution();
		m_timer->Execution();
	}

	void Game::InGameExecution()
	{
		
		m_defensiveTarget->Execution();
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
				AllNew();
				Init();
			}
		}
		else {
			m_sampleFont->SetText(L"GAME CLEAR");
			m_sampleFont->Execution();
			if (g_pad[0]->IsTrigger(enButtonX)) {
				DeleteGO(m_sampleSprite);
				DeleteGO(m_sampleFont);
				DeleteGO(m_unityChanModel2);
				AllDelete();
				m_state = enGameClear;
				m_isDead = true;
			}
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
		m_miniMap = NewGO<map::MiniMap>(PRIORITY_VERYLOW, map::MINI_MAP_NAME);
		m_player = NewGO<player::Player>(PRIORITY_VERYLOW, player::PLAYER_NAME);
		m_gameCamera = NewGO<GameCamera>(PRIORITY_VERYLOW, GAME_CAMERA_NAME);
		m_defensiveTarget = NewGO<defensiveTarget::DefensiveTarget>(PRIORITY_VERYLOW, defensiveTarget::DEFENSIVE_TARGET_NAME);
		m_enemyGenerator = NewGO<enemy::Generator>(PRIORITY_VERYLOW, enemy::ENEMY_GENERATOR_NAME);
		m_stage = NewGO<stage::Stage>(PRIORITY_VERYLOW, stage::STAGE_NAME);
		m_timer = NewGO<timer::Timer>(PRIORITY_VERYLOW, timer::TIMER_NAME);

		m_unityChanModel2 = NewGO<render::model::SkinModelRender>(1);
		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);
		m_sampleFont = NewGO<render::font::FontRender>(0);
		m_sound = NewGO<CSoundSource>(PRIORITY_VERYLOW);

		m_isInitd = false;
	}

	void Game::AllDelete()
	{
		DeleteGO(m_gameCamera);
		DeleteGO(m_enemyGenerator);
		DeleteGO(m_player);
		DeleteGO(m_defensiveTarget);
		DeleteGO(m_stage);
		DeleteGO(m_timer);
		DeleteGO(m_sound);
		DeleteGO(m_miniMap);
	}

	void Game::Pause()
	{

	}
}