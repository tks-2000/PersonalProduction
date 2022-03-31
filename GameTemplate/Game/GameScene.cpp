#include "stdafx.h"
#include "GameScene.h"

namespace mainGame {
	/// @brief �t�F�[�h�C���̑��x
	const float FEADIN_RATE = 1.0f;
	/// @brief �t�F�[�h�A�E�g�̑��x
	const float FEADOUT_RATE = 1.0f;
	/// @brief �N���A���̃T�E���h�t�@�C���p�X
	const wchar_t* CLEAR_SE_FILEPATH = L"Assets/sound/se/Clear.wav";
	/// @brief �Q�[���I�[�o�[���̃T�E���h�t�@�C���p�X
	const wchar_t* GAMEOVER_SE_FILEPATH = L"Assets/sound/se/GameOver.wav";
	/// @brief �{�^�������������̃T�E���h�t�@�C���p�X
	const wchar_t* PRESSKEY_SE_FILEPATH = L"Assets/sound/se/decision.wav";
	/// @brief SE�̑傫��
	const float SE_VOLUME = 0.1f;
	/// @brief �{�^���������悤�ɑ����t�H���g�̈ʒu
	const Vector2 PRESSKEY_FONT_POS = { -150.0f,-200.0f };
	/// @brief �摜�̉���
	const int SPRITE_WIDTH = 100;
	/// @brief �摜�̏c��
	const int SPRITE_HEIGHT = 100;
	/// @brief �摜�̐F
	const Vector4 SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.0f };

	GameScene::GameScene()
	{
		//�Q�[���V�[���ŏo�����̂��쐬
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
		//�o�������̂�S�č폜
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
		
		

		//���������s��
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

		//�摜�̏�����
		m_sampleSprite->Init("Assets/image/sight.dds", SPRITE_WIDTH, SPRITE_HEIGHT);
		m_sampleSprite->SetPosition(g_vec3Zero);
		m_sampleSprite->SetColor(SPRITE_COLOR);

		//�t�H���g�̏�����
		m_pressKeyFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
		m_pressKeyFont->Init(L"PUSH X BUTTON");
		m_pressKeyFont->SetPosition(PRESSKEY_FONT_POS);
		m_pressKeyFont->SetColor(m_pressKeyFontColor);

		//�T�E���h�̏�����
		m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
		m_clearSoundID = m_soundPlayer->SetSE(CLEAR_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_clearSoundID, SE_VOLUME);
		m_gameOverSoundID = m_soundPlayer->SetSE(GAMEOVER_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_gameOverSoundID, SE_VOLUME);
		m_pressKeySoundID = m_soundPlayer->SetSE(PRESSKEY_SE_FILEPATH);
		m_soundPlayer->SetSEVolume(m_pressKeySoundID, SE_VOLUME);

		//�g�p��������擾
		m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		m_game = FindGO<Game>(GAME_NAME);
		m_sceneTransition = FindGO<SceneTransition>(SCENE_TRANSITION_NAME);

		//�t�F�[�h�C�����n�߂�
		m_sceneTransition->SetFeadIn(FEADIN_RATE);

		//����������
		m_isInitd = true;	
	}

	void GameScene::Execution()
	{
		//���������Ȃ���s���Ȃ�
		if (m_isInitd == false) {
			return;
		}



		//�|�[�Y��
		if (m_pause == true) {
			//�X�^�[�g�{�^���������ꂽ��c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonStart)) {
				//�|�[�Y����������
				m_pause = false;
				m_renderingEngine->SetLightFlag(true);
				m_renderingEngine->SetEffectFlag(true);
			}
			//�|�[�Y���͎��s���Ȃ�
			return;
		}
		//�|�[�Y���Ă��Ȃ���
		else {
			//�X�^�[�g�{�^���������ꂽ��c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonStart)) {
				//�|�[�Y���J�n����
				m_pause = true;
				m_renderingEngine->SetLightFlag(false);
				m_renderingEngine->SetEffectFlag(false);
				//�|�[�Y���n�܂�̂Ŏ��s���Ȃ�
				return;
			}
		}

		//�Q�[���V�[���ɏo���Ă�����̂����s����
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

		//�h�q�Ώۂ��j�󂳂ꂽ��c
		if (m_defensiveTarget->IsBreak() == true) {
			//�Q�[���I�[�o�[�ɂ���
			m_gameSceneState = enGameSceneOver;
		}

		//�Q�[���N���A���Q�[���I�[�o�[�ɂȂ��Ă�����c
		if (m_gameSceneState == enGameSceneClear || m_gameSceneState == enGameSceneOver) {
			//�I�����̃T�E���h�����Ă��Ȃ��ꍇ
			if (m_isPlayEndSound == false) {
				//�Q�[���N���A��ԂȂ�c
				if (m_gameSceneState == enGameSceneClear) {
					//�N���A���̃T�E���h��炷
					m_soundPlayer->PlaySE(m_clearSoundID);
				}
				//�Q�[���I�[�o�[��ԂȂ�
				else {
					//�Q�[���I�[�o�[�̃T�E���h��炷
					m_soundPlayer->PlaySE(m_gameOverSoundID);
				}
				//�I�����̃T�E���h������
				m_isPlayEndSound = true;
			}

			//X�{�^���������ꂽ��c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonX)) {
				//�Q�[�����I������
				m_endFlag = true;
				m_soundPlayer->PlaySE(m_pressKeySoundID);
				m_sceneTransition->SetFeadOut(FEADOUT_RATE);
			}

			//�t�H���g�̐F��������悤�ɂ���
			m_pressKeyFontColor = g_vec4White;
		}
		//�t�H���g�����s���n�߂�
		m_pressKeyFont->SetColor(m_pressKeyFontColor);
		m_pressKeyFont->Execution();

		//�I���t���O����������c
		if (m_endFlag == true) {
			//�t�F�[�h�A�E�g����������c
			if (m_sceneTransition->IsFeadOut() == false) {
				//�Q�[���V�[�����I������
				GameSceneEnd();
			}
		}
	}

	void GameScene::GameSceneEnd()
	{
		//�^�C�g�����쐬���Q�[���V�[�����폜
		m_game->TitleSceneStart();
		m_game->DeleteGameScene();
	}
}