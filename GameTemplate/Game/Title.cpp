#include "stdafx.h"
#include "Title.h"
namespace mainGame {
	namespace title {

		const int TITLE_SPRITE_WIDTH = 1280;

		const int TITLE_SPRITE_HEIGHT = 720;

		const Vector3 TITLE_CAMERA_POS = { 0.0f,100.0f,800.0f };

		const Vector3 TITLE_CAMERA_TARGET_POS = { 0.0f,50.0f, 0.0f };

		const float TITLE_CAMERA_FAR = 10000.0f;

		const wchar_t* TITLE_BGM_FILEPATH = L"Assets/sound/bgm/titleBgm.wav";

		const float TITLE_BGM_VOLUME = 0.1f;

		const wchar_t* START_SE_FILEPATH = L"Assets/sound/se/decision.wav";

		const float START_SE_VOLUME = 0.1f;

		const float FEADIN_RATE = 0.3f;

		const float FEADOUT_RATE = 1.0f;

		

		Title::Title()
		{

		}

		Title::~Title()
		{
			//DeleteGO(m_titleSprite);
			m_soundPlayer->StopBGM(m_titleSoundID);
			DeleteGO(m_font);
		}

		void Title::Init()
		{
			//m_titleSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			//m_titleSprite->Init("Assets/Image/WB.dds", TITLE_SPRITE_WIDTH, TITLE_SPRITE_HEIGHT);

			m_font = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_font->Init(L"PUSH A BUTTON");
			m_font->SetColor(g_vec4White);
			m_font->SetPosition({ -150.0f,-200.0f });

			m_game = FindGO<Game>(GAME_NAME);

			m_models.Init(this);

			g_camera3D->SetPosition(TITLE_CAMERA_POS);
			g_camera3D->SetTarget(TITLE_CAMERA_TARGET_POS);
			g_camera3D->SetFar(TITLE_CAMERA_FAR);

			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			m_titleSoundID =  m_soundPlayer->SetBGM(TITLE_BGM_FILEPATH);

			m_soundPlayer->SetBGMVolume(m_titleSoundID, TITLE_BGM_VOLUME);

			m_soundPlayer->PlayBGM(m_titleSoundID, true);

			m_startSoundID = m_soundPlayer->SetSE(START_SE_FILEPATH);

			m_soundPlayer->SetSEVolume(m_startSoundID, START_SE_VOLUME);

			m_sceneTransition = FindGO<SceneTransition>(SCENE_TRANSITION_NAME);

			m_sceneTransition->SetFeadIn(FEADIN_RATE);

			m_isInitd = true;
		}

		void Title::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonA) && m_endFlag == false) {
				m_endFlag = true;
				m_soundPlayer->PlaySE(m_startSoundID);
				m_sceneTransition->SetFeadOut(FEADOUT_RATE);
			}

			if (m_endFlag == true) {
				if (m_sceneTransition->IsFeadOut() == false) {
					m_game->GameSceneStart();
					m_game->DeleteTitleScene();
				}
			}

			//m_titleSprite->Execute();
			m_font->Execution();
			m_models.Execution();
		}
	}
}