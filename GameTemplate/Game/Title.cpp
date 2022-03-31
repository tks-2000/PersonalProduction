#include "stdafx.h"
#include "Title.h"
namespace mainGame {
	namespace title {
		/// @brief �^�C�g���̉摜�̉���
		const int TITLE_SPRITE_WIDTH = 1280;
		/// @brief �^�C�g���̉摜�̏c��
		const int TITLE_SPRITE_HEIGHT = 720;
		/// @brief �^�C�g���̃J�������W
		const Vector3 TITLE_CAMERA_POS = { 0.0f,100.0f,800.0f };
		/// @brief �^�C�g���̃J���������_
		const Vector3 TITLE_CAMERA_TARGET_POS = { 0.0f,50.0f, 0.0f };
		/// @brief �^�C�g���̃J����������
		const float TITLE_CAMERA_FAR = 10000.0f;
		/// @brief �^�C�g���̃T�E���h�t�@�C���p�X
		const wchar_t* TITLE_BGM_FILEPATH = L"Assets/sound/bgm/titleBgm.wav";
		/// @brief �^�C�g���T�E���h�̑傫��
		const float TITLE_BGM_VOLUME = 0.1f;
		/// @brief �X�^�[�g���̃T�E���h�t�@�C���p�X
		const wchar_t* START_SE_FILEPATH = L"Assets/sound/se/decision.wav";
		/// @brief �X�^�[�g���̃T�E���h�̑傫��
		const float START_SE_VOLUME = 0.1f;
		/// @brief �t�F�[�h�C���̑��x
		const float FEADIN_RATE = 0.3f;
		/// @brief �t�F�[�h�A�E�g�̑��x
		const float FEADOUT_RATE = 1.0f;
		/// @brief �t�H���g�̍��W
		const Vector2 FONT_POS = { -150.0f,-200.0f };
		

		Title::Title()
		{

		}

		Title::~Title()
		{
			//�T�E���h���~�߂�
			m_soundPlayer->StopBGM(m_titleSoundID);
			//�t�H���g������
			DeleteGO(m_font);
		}

		void Title::Init()
		{
			//�t�H���g���쐬
			m_font = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_font->Init(L"PUSH A BUTTON");
			m_font->SetColor(g_vec4White);
			m_font->SetPosition(FONT_POS);

			//���f�����쐬
			m_models.Init(this);

			//�J������ݒ�
			g_camera3D->SetPosition(TITLE_CAMERA_POS);
			g_camera3D->SetTarget(TITLE_CAMERA_TARGET_POS);
			g_camera3D->SetFar(TITLE_CAMERA_FAR);

			//�T�E���h�̏�����
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_titleSoundID =  m_soundPlayer->SetBGM(TITLE_BGM_FILEPATH);
			m_soundPlayer->SetBGMVolume(m_titleSoundID, TITLE_BGM_VOLUME);
			m_soundPlayer->PlayBGM(m_titleSoundID, true);
			m_startSoundID = m_soundPlayer->SetSE(START_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_startSoundID, START_SE_VOLUME);

			//�g�p��������擾
			m_game = FindGO<Game>(GAME_NAME);
			m_sceneTransition = FindGO<SceneTransition>(SCENE_TRANSITION_NAME);

			//�t�F�[�h�C�����J�n
			m_sceneTransition->SetFeadIn(FEADIN_RATE);

			//����������
			m_isInitd = true;
		}

		void Title::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//A�{�^���������ꂽ��c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonA) && m_endFlag == false) {
				//�I���t���O�𗧂Ă�
				m_endFlag = true;
				//�X�^�[�g���̃T�E���h��炷
				m_soundPlayer->PlaySE(m_startSoundID);
				//�t�F�[�h�A�E�g���J�n����
				m_sceneTransition->SetFeadOut(FEADOUT_RATE);
			}
			
			//�I���t���O�������Ă���ꍇ�c
			if (m_endFlag == true) {
				//�t�F�[�h�A�E�g���I�������c
				if (m_sceneTransition->IsFeadOut() == false) {
					//�Q�[���V�[�����J�n���ă^�C�g�����I������
					m_game->GameSceneStart();
					m_game->DeleteTitleScene();
				}
			}

			//�t�H���g�ƃ��f���̏��������s
			m_font->Execution();
			m_models.Execution();
		}
	}
}