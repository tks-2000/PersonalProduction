#include "stdafx.h"
#include "Title.h"
namespace mainGame {
	namespace title {

		const int TITLE_SPRITE_WIDTH = 1280;

		const int TITLE_SPRITE_HEIGHT = 720;

		const Vector3 TITLE_CAMERA_POS = { 0.0f,500.0f,-1100.0f };

		const Vector3 TITLE_CAMERA_TARGET_POS = { 0.0f,450.0f,-900.0f };

		const float TITLE_CAMERA_FAR = 10000.0f;

		const wchar_t* TITLE_BGM_FILEPATH = L"Assets/sound/bgm/titleBgm.wav";

		const float TITLE_BGM_VOLUME = 0.1f;

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

			m_isInitd = true;
		}

		void Title::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonA)) {
				m_game->GameSceneStart();
				m_game->DeleteTitleScene();
			}

			//m_titleSprite->Execute();
			m_font->Execution();
			m_models.Execution();
		}
	}
}