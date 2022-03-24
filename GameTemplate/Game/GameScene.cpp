#include "stdafx.h"
#include "GameScene.h"

namespace mainGame {

	const float FEADIN_RATE = 1.0f;

	const float FEADOUT_RATE = 1.0f;

	const wchar_t* CLEAR_SE_FILEPATH = L"Assets/sound/se/Clear.wav";

	const wchar_t* GAMEOVER_SE_FILEPATH = L"Assets/sound/se/GameOver.wav";

	const wchar_t* PRESSKEY_SE_FILEPATH = L"Assets/sound/se/decision.wav";

	const float SE_VOLUME = 0.1f;

	const Vector2 PRESSKEY_FONT_POS = { -150.0f,-200.0f };

	GameScene::GameScene()
	{
		

		//m_miniMap = NewGO<map::MiniMap>(PRIORITY_VERYLOW, map::MINI_MAP_NAME);
		m_player = NewGO<player::Player>(PRIORITY_VERYLOW, player::PLAYER_NAME);
		m_gameCamera = NewGO<GameCamera>(PRIORITY_VERYLOW, GAME_CAMERA_NAME);
		m_defensiveTarget = NewGO<defensiveTarget::DefensiveTarget>(PRIORITY_VERYLOW, defensiveTarget::DEFENSIVE_TARGET_NAME);
		m_enemyGenerator = NewGO<enemy::Generator>(PRIORITY_VERYLOW, enemy::ENEMY_GENERATOR_NAME);
		m_stage = NewGO<stage::Stage>(PRIORITY_VERYLOW, stage::STAGE_NAME);
		m_timer = NewGO<timer::Timer>(PRIORITY_VERYLOW, timer::TIMER_NAME);
		m_itemGenerator = NewGO<item::ItemGenerator>(PRIORITY_VERYLOW, item::ITEM_GENERATOR_NAME);
		m_gameUI = NewGO<ui::GameUI>(PRIORITY_VERYLOW, ui::GAME_UI_NAME);


		m_sampleSprite = NewGO<render::sprite::SpriteRender>(0);

	}

	GameScene::~GameScene()
	{
		DeleteGO(m_gameCamera);
		DeleteGO(m_enemyGenerator);
		DeleteGO(m_player);
		DeleteGO(m_defensiveTarget);
		DeleteGO(m_stage);
		DeleteGO(m_timer);
		//DeleteGO(m_miniMap);
		DeleteGO(m_itemGenerator);
		DeleteGO(m_gameUI);
		DeleteGO(m_sampleSprite);

		DeleteGO(m_pressKeyFont);
	}

	void GameScene::Init()
	{
		m_pause = false;

		//m_miniMap->Init();

		m_player->Init();

		m_defensiveTarget->Init();

		m_gameCamera->Init();

		m_enemyGenerator->Init({ 0.0f,0.0f,0.0f });

		m_stage->Init();

		m_timer->Init();



		m_sampleSprite->Init("Assets/image/sight.dds", 100, 100);
		m_sampleSprite->SetPosition({ 0.0f,0.0f,0.0f });
		m_sampleSprite->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });

		m_pressKeyFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
		m_pressKeyFont->Init(L"PUSH X BUTTON");
		m_pressKeyFont->SetPosition(PRESSKEY_FONT_POS);
		m_pressKeyFont->SetColor(m_pressKeyFontColor);

		m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
		m_clearSoundID = m_soundPlayer->SetSE(CLEAR_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_clearSoundID, SE_VOLUME);
		m_gameOverSoundID = m_soundPlayer->SetSE(GAMEOVER_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_gameOverSoundID, SE_VOLUME);
		m_pressKeySoundID = m_soundPlayer->SetSE(PRESSKEY_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_pressKeySoundID, SE_VOLUME);

		m_gameSceneState = enGameSceneStart;

		m_itemGenerator->Init();

		m_gameUI->Init();

		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);

		m_game = FindGO<Game>(GAME_NAME);

		m_sceneTransition = FindGO<SceneTransition>(SCENE_TRANSITION_NAME);

		m_sceneTransition->SetFeadIn(FEADIN_RATE);

		m_isInitd = true;
		
	}

	void GameScene::Execution()
	{
		if (m_isInitd == false) {
			return;
		}



		//ポーズ中は実行しない
		if (m_pause == true) {

			if (g_pad[0]->IsTrigger(enButtonStart)) {
				m_pause = false;
				m_renderingEngine->SetLightFlag(true);
				m_renderingEngine->SetEffectFlag(true);
			}
			return;
		}
		else {
			if (g_pad[0]->IsTrigger(enButtonStart)) {
				m_pause = true;
				m_renderingEngine->SetLightFlag(false);
				m_renderingEngine->SetEffectFlag(false);
				return;
			}
		}


		m_timer->Execution();

		m_player->Execution();
		m_enemyGenerator->Execute();
		m_gameCamera->Execution();
		//m_miniMap->Execution();
		m_itemGenerator->Execution();
		m_gameUI->Execution();
		m_defensiveTarget->Execution();
		m_stage->Execution();

		if (m_gameCamera->GetCameraMode() == enCameraModeTps) {
			m_sampleSprite->FadeOut(2.0f);
		}
		else {
			m_sampleSprite->FadeIn(2.0f);
		}
		m_sampleSprite->Execute();


		if (m_defensiveTarget->IsBreak() == true) {
			m_gameSceneState = enGameSceneOver;
		}

		if (m_gameSceneState == enGameSceneClear || m_gameSceneState == enGameSceneOver) {
			if (m_isPlayEndSound == false) {
				if (m_gameSceneState == enGameSceneClear) {
					m_soundPlayer->PlaySE(m_clearSoundID);
				}
				else {
					m_soundPlayer->PlaySE(m_gameOverSoundID);
				}
				m_isPlayEndSound = true;
			}
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonX)) {
				m_endFlag = true;
				m_soundPlayer->PlaySE(m_pressKeySoundID);
				m_sceneTransition->SetFeadOut(FEADOUT_RATE);
			}

			m_pressKeyFontColor = g_vec4White;
		}
		m_pressKeyFont->SetColor(m_pressKeyFontColor);
		m_pressKeyFont->Execution();

		if (m_endFlag == true) {
			if (m_sceneTransition->IsFeadOut() == false) {
				GameSceneEnd();
			}
		}
	}

	void GameScene::CreateGameScene()
	{
		
	}

	void GameScene::DeleteGameScene()
	{

	}

	void GameScene::GameSceneEnd()
	{
		m_game->TitleSceneStart();
		m_game->DeleteGameScene();
	}
}