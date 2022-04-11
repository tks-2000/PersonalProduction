#include "stdafx.h"
#include "TimeLimit.h"

namespace mainGame {
	namespace ui {
		/// @brief �^�C�}�[�̉��n�摜�̃t�@�C���p�X
		const char* TIMER_BASE_SPRITE_FILEPATH = "Assets/Image/base_sprite_5.dds";
		/// @brief �^�C�}�[�̉��n�̘g�̉摜�̃t�@�C���p�X
		const char* TIMER_BASE_FRAME_FILEPATH = "Assets/Image/base_sprite_6.dds";
		/// @brief �^�C�}�[�̉��n�摜�̍��W
		const Vector3 TIMER_BASE_SPRITE_POS = { -450.0f,190.0f,0.0f };
		/// @brief �^�C�}�[�̉��n�摜�̃J���[
		const Vector4 TIMER_BASE_SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief �^�C�}�[�̉��n�摜�̉���
		const int TIMER_BASE_SPRITE_WIDTH = 300;
		/// @brief �^�C�}�[�̉��n�摜�̏c��
		const int TIMER_BASE_SPRITE_HEIGHT = 500;
		/// @brief �^�C���\���̃t�H���g�̍��W
		const Vector2 TIME_FONT_POS = { -560.0f,215.0f };
		/// @brief �^�C���̐��l�\���̃t�H���g�̍��W
		const Vector2 TIMER_NUM_FONT_POS = { -415.0f,215.0f };
		/// @brief �J�E���g���s���摜�̃t�@�C���p�X�z��
		const char* NUM_SPRITE_FILEPATH[NUM_SPRITE_NUM] = {
			"Assets/Image/1.DDS",
			"Assets/Image/2.DDS",
			"Assets/Image/3.DDS"
		};
		/// @brief �J�n�̉摜�t�@�C���p�X
		const char* GO_SPRITE_FILEPATH = "Assets/Image/GO.DDS";
		/// @brief UI�摜�̊J�n�J���[
		const Vector4 UI_SPRITE_START_COLOR = { 1.0f,1.0f,1.0f,0.0f };
		/// @brief UI�t�H���g�̊J�n�J���[
		const Vector4 UI_FONT_START_COLOR = { 0.0f,0.0f,0.0f,0.0f };
		/// @brief �J�E���g���s���摜�̉���
		const float NUM_SPRITE_WIDTH = 200.0f;
		/// @brief �J�E���g���s���摜�̏c��
		const float NUM_SPRITE_HEIGHT = 200.0f;
		/// @brief �����t�F�[�h�̑��x
		const float FAST_FADE_RATE = 2.5f;
		/// @brief �x���t�F�[�h�̑��x
		const float SLOW_FADE_RATE = 0.5f;
		/// @brief �J�E���g�̃T�E���h�t�@�C���p�X
		const wchar_t* COUNT_SE_FILEPATH = L"Assets/sound/se/count.wav";
		/// @brief �J�n�̃T�E���h�t�@�C���p�X
		const wchar_t* GO_SE_FILEPATH = L"Assets/sound/se/go.wav";
		/// @brief SE�̑傫��
		const float SE_VOLUME = 0.1f;

		TimeLimit::TimeLimit()
		{

		}

		TimeLimit::~TimeLimit()
		{
			//�쐬�����摜��t�H���g���폜
			DeleteGO(m_timerBaseSprite);
			DeleteGO(m_timerBaseFrame);
			DeleteGO(m_timeFont);
			DeleteGO(m_timerNumFont);
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				DeleteGO(m_count[spriteNum]);
			}

			DeleteGO(m_go);
		}

		void TimeLimit::Init()
		{
			//�g�p������������ė���
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//�\������摜���쐬
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				m_count[spriteNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
				m_count[spriteNum]->Init(NUM_SPRITE_FILEPATH[spriteNum], NUM_SPRITE_WIDTH, NUM_SPRITE_HEIGHT);
				m_count[spriteNum]->SetColor(UI_SPRITE_START_COLOR);
			}

			m_go = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_go->Init(GO_SPRITE_FILEPATH, NUM_SPRITE_WIDTH, NUM_SPRITE_HEIGHT);
			m_go->SetColor(UI_SPRITE_START_COLOR);

			m_timerBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_timerBaseSprite->Init(TIMER_BASE_SPRITE_FILEPATH, TIMER_BASE_SPRITE_WIDTH, TIMER_BASE_SPRITE_HEIGHT);
			m_timerBaseSprite->SetPosition(TIMER_BASE_SPRITE_POS);
			m_timerBaseSprite->SetColor(TIMER_BASE_SPRITE_COLOR);
			m_timerBaseFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_timerBaseFrame->Init(TIMER_BASE_FRAME_FILEPATH, TIMER_BASE_SPRITE_WIDTH, TIMER_BASE_SPRITE_HEIGHT);
			m_timerBaseFrame->SetPosition(TIMER_BASE_SPRITE_POS);

			//�\������t�H���g���쐬
			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timeFont->Init(L"TIME :");
			m_timeFont->SetPosition(TIME_FONT_POS);
			m_timeFont->SetColor(UI_FONT_START_COLOR);

			m_timerNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			m_timerNumFont->Init(L"test");
			m_timerNumFont->SetPosition(TIMER_NUM_FONT_POS);
			m_timerNumFont->SetColor(UI_FONT_START_COLOR);

			//�T�E���h��������
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_countSoundID = m_soundPlayer->SetSE(COUNT_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_countSoundID, SE_VOLUME);
			m_goSoundID = m_soundPlayer->SetSE(GO_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_goSoundID, SE_VOLUME);

			//�ϐ���������
			m_isCountDown = true;

			//����������
			m_isInitd = true;
		}

		void TimeLimit::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�^�C�}�[�̒l���t�H���g�ɓK�p
			std::wstring conversion;
			conversion = std::to_wstring(m_timer->GetTimer());
			m_timerNumFont->SetText(conversion.c_str());

			//�Q�[���V�[�����i�s���̏ꍇ
			if (m_gameScene->GetGameSceneState() == enGameSceneInProgress) {
				//�t�H���g�̐F��������悤�ɂ���
				m_timerNumFont->SetColor(g_vec4White);
				m_timeFont->SetColor(g_vec4White);
			}

			//�J�E���g���̏ꍇ
			if (m_isCountDown == true) {
				//�J�E���g�̏������s��
				CountDown();
			}

			//�摜�̐��������s
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				m_count[spriteNum]->Execute();
			}

			//�J�n�摜���s�����ɂȂ�����t�F�[�h�A�E�g����
			if (m_go->IsOpacity() == true) {
				m_go->FadeOut(SLOW_FADE_RATE);
			}

			//���������s
			m_go->Execute();
			m_timerBaseSprite->Execute();
			m_timerBaseFrame->Execute();
			m_timeFont->Execution();
			m_timerNumFont->Execution();
		}

		void TimeLimit::HideUI()
		{
			//UI�̐F�������Ȃ�����
			m_timerBaseSprite->SetColor(render::COLORLESS);
			m_timerBaseFrame->SetColor(render::COLORLESS);
			m_timeFont->SetColor(render::COLORLESS);
			m_timerNumFont->SetColor(render::COLORLESS);
		}

		void TimeLimit::CountDown()
		{
			
			//�摜�̐������J��Ԃ�
			for (int spriteNum = 0; spriteNum < NUM_SPRITE_NUM; spriteNum++) {
				//�ԍ����J�n�^�C�}�[���P�������l�Ɠ����������ꍇ�c
				if (spriteNum == m_timer->GetStartTimer() - 1) {
					//���̔ԍ��̉摜���t�F�[�h�C������
					m_count[spriteNum]->FadeIn(FAST_FADE_RATE);
					//�J�E���g�T�E���h�����Ă��Ȃ��ꍇ�c
					if (m_isPlayCountSE[spriteNum] == false) {
						//�J�E���g�T�E���h��炷
						m_soundPlayer->PlaySE(m_countSoundID);
						m_isPlayCountSE[spriteNum] = true;
					}
				}
				//�ԍ����J�n�^�C�}�[���P�������l�ł͖��������ꍇ�c
				else {
					//���̔ԍ��̉摜�̓t�F�[�h�A�E�g����
					m_count[spriteNum]->FadeOut(FAST_FADE_RATE);
				}
			}

			//�J�n�^�C�}�[��0�ɂȂ����ꍇ�c
			if (m_timer->GetStartTimer() == 0) {
				//�J�n�摜���t�F�[�h�C������
				m_go->FadeIn(FAST_FADE_RATE);
				//�J�n�̃T�E���h��炷
				m_soundPlayer->PlaySE(m_goSoundID);
				//�J�E���g�_�E�����̃t���O���~�낷
				m_isCountDown = false;
			}
		}
	}
}