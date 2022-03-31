#include "stdafx.h"
#include "GameScene.h"

namespace mainGame {
	/// @brief フェードインの速度
	const float FEADIN_RATE = 1.0f;
	/// @brief フェードアウトの速度
	const float FEADOUT_RATE = 1.0f;
	/// @brief クリア時のサウンドファイルパス
	const wchar_t* CLEAR_SE_FILEPATH = L"Assets/sound/se/Clear.wav";
	/// @brief ゲームオーバー時のサウンドファイルパス
	const wchar_t* GAMEOVER_SE_FILEPATH = L"Assets/sound/se/GameOver.wav";
	/// @brief ボタンを押した時のサウンドファイルパス
	const wchar_t* PRESSKEY_SE_FILEPATH = L"Assets/sound/se/decision.wav";
	/// @brief SEの大きさ
	const float SE_VOLUME = 0.1f;
	/// @brief ボタンを押すように促すフォントの位置
	const Vector2 PRESSKEY_FONT_POS = { -150.0f,-200.0f };
	/// @brief 画像の横幅
	const int SPRITE_WIDTH = 100;
	/// @brief 画像の縦幅
	const int SPRITE_HEIGHT = 100;
	/// @brief 画像の色
	const Vector4 SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.0f };

	GameScene::GameScene()
	{
		//ゲームシーンで出すものを作成
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
		//出したものを全て削除
		DeleteGO(m_gameCamera);
		DeleteGO(m_enemyGenerator);
		DeleteGO(m_player);
		DeleteGO(m_defensiveTarget);
		DeleteGO(m_stage);
		DeleteGO(m_timer);
		DeleteGO(m_itemGenerator);
		DeleteGO(m_gameUI);
		DeleteGO(m_sampleSprite);
		DeleteGO(m_pressKeyFont);
	}

	void GameScene::Init()
	{
		
		

		//初期化を行う
		m_player->Init();
		m_defensiveTarget->Init();
		m_gameCamera->Init();
		m_enemyGenerator->Init(g_vec3Zero);
		m_stage->Init();
		m_timer->Init();
		m_pause = false;
		m_gameSceneState = enGameSceneStart;
		m_itemGenerator->Init();
		m_gameUI->Init();

		//画像の初期化
		m_sampleSprite->Init("Assets/image/sight.dds", SPRITE_WIDTH, SPRITE_HEIGHT);
		m_sampleSprite->SetPosition(g_vec3Zero);
		m_sampleSprite->SetColor(SPRITE_COLOR);

		//フォントの初期化
		m_pressKeyFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
		m_pressKeyFont->Init(L"PUSH X BUTTON");
		m_pressKeyFont->SetPosition(PRESSKEY_FONT_POS);
		m_pressKeyFont->SetColor(m_pressKeyFontColor);

		//サウンドの初期化
		m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
		m_clearSoundID = m_soundPlayer->SetSE(CLEAR_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_clearSoundID, SE_VOLUME);
		m_gameOverSoundID = m_soundPlayer->SetSE(GAMEOVER_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_gameOverSoundID, SE_VOLUME);
		m_pressKeySoundID = m_soundPlayer->SetSE(PRESSKEY_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_pressKeySoundID, SE_VOLUME);

		//使用する情報を取得
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		m_game = FindGO<Game>(GAME_NAME);
		m_sceneTransition = FindGO<SceneTransition>(SCENE_TRANSITION_NAME);

		//フェードインを始める
		m_sceneTransition->SetFeadIn(FEADIN_RATE);

		//初期化完了
		m_isInitd = true;	
	}

	void GameScene::Execution()
	{
		//未初期化なら実行しない
		if (m_isInitd == false) {
			return;
		}



		//ポーズ中
		if (m_pause == true) {
			//スタートボタンが押されたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonStart)) {
				//ポーズを解除する
				m_pause = false;
				m_renderingEngine->SetLightFlag(true);
				m_renderingEngine->SetEffectFlag(true);
			}
			//ポーズ中は実行しない
			return;
		}
		//ポーズしていない時
		else {
			//スタートボタンが押されたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonStart)) {
				//ポーズを開始する
				m_pause = true;
				m_renderingEngine->SetLightFlag(false);
				m_renderingEngine->SetEffectFlag(false);
				//ポーズが始まるので実行しない
				return;
			}
		}

		//ゲームシーンに出しているものを実行する
		m_timer->Execution();
		m_player->Execution();
		m_enemyGenerator->Execute();
		m_gameCamera->Execution();
		m_itemGenerator->Execution();
		m_gameUI->Execution();
		m_defensiveTarget->Execution();
		m_stage->Execution();

		/*if (m_gameCamera->GetCameraMode() == enCameraModeTps) {
			m_sampleSprite->FadeOut(2.0f);
		}
		else {
			m_sampleSprite->FadeIn(2.0f);
		}*/
		m_sampleSprite->Execute();

		//防衛対象が破壊されたら…
		if (m_defensiveTarget->IsBreak() == true) {
			//ゲームオーバーにする
			m_gameSceneState = enGameSceneOver;
		}

		//ゲームクリアかゲームオーバーになっていたら…
		if (m_gameSceneState == enGameSceneClear || m_gameSceneState == enGameSceneOver) {
			//終了時のサウンドが鳴っていない場合
			if (m_isPlayEndSound == false) {
				//ゲームクリア状態なら…
				if (m_gameSceneState == enGameSceneClear) {
					//クリア時のサウンドを鳴らす
					m_soundPlayer->PlaySE(m_clearSoundID);
				}
				//ゲームオーバー状態なら
				else {
					//ゲームオーバーのサウンドを鳴らす
					m_soundPlayer->PlaySE(m_gameOverSoundID);
				}
				//終了時のサウンドが鳴った
				m_isPlayEndSound = true;
			}

			//Xボタンが押されたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonX)) {
				//ゲームを終了する
				m_endFlag = true;
				m_soundPlayer->PlaySE(m_pressKeySoundID);
				m_sceneTransition->SetFeadOut(FEADOUT_RATE);
			}

			//フォントの色を見えるようにする
			m_pressKeyFontColor = g_vec4White;
		}
		//フォントを実行し始める
		m_pressKeyFont->SetColor(m_pressKeyFontColor);
		m_pressKeyFont->Execution();

		//終了フラグが立ったら…
		if (m_endFlag == true) {
			//フェードアウト完了したら…
			if (m_sceneTransition->IsFeadOut() == false) {
				//ゲームシーンを終了する
				GameSceneEnd();
			}
		}
	}

	void GameScene::GameSceneEnd()
	{
		//タイトルを作成しゲームシーンを削除
		m_game->TitleSceneStart();
		m_game->DeleteGameScene();
	}
}