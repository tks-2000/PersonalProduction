#include "stdafx.h"
#include "GameScene.h"

namespace mainGame {

	GameScene::GameScene()
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


		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);

		m_sound = NewGO<CSoundSource>(PRIORITY_VERYLOW);
	}

	GameScene::~GameScene()
	{

	}

	void GameScene::Init()
	{
		m_pause = false;

		m_miniMap->Init();

		m_player->Init();

		m_defensiveTarget->Init();

		m_gameCamera->Init();

		m_enemyGenerator->Init({ 0.0f,0.0f,0.0f });

		m_stage->Init();

		m_timer->Init();



		m_sampleSprite->Init("Assets/image/sight.dds", 100, 100);
		m_sampleSprite->SetPosition({ 0.0f,0.0f,0.0f });
		m_sampleSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });



		m_sound->Init(L"Assets/sound/bgm/SpecialBgm.wav");
		m_sound->SetVolume(1.0f);
		//m_sound->Play(true);

		m_gameSceneState = enGameSceneStart;

		m_itemGenerator->Init();

		m_gameUI->Init();

		m_isInitd = true;
		
	}

	void GameScene::Execution()
	{
		if (m_isInitd == false) {
			return;
		}

	}

	void GameScene::CreateGameScene()
	{
		
	}

	void GameScene::DeleteGameScene()
	{

	}
}