#include "stdafx.h"
#include "RemainingBullets.h"

namespace mainGame {
	namespace ui {
		/// @brief �c�e���̃t�H���g�̈ʒu
		const Vector2 BULLET_NUM_FONT_POS = { 350.0f,-115.0f };
		/// @brief �c�e��\���摜�̃t�@�C���p�X
		const char* REMAINING_BULLETS_SPRITE_FILEPATH = "Assets/Image/bullet.dds";
		/// @brief �c�e�̉摜�̉���
		const int REMAINING_BULLETS_SPRITE_WIDTH = 100;
		/// @brief �c�e�̉摜�̏c��
		const int REMAINING_BULLETS_SPRITE_HEIGHT = 100;
		/// @brief �c�e�̉摜�̍��W
		const Vector3 REMAINING_BULLETS_SPRITE_POS = { 300.0f,-140.0f,0.0f };

		RemainingBullets::RemainingBullets()
		{

		}

		RemainingBullets::~RemainingBullets()
		{
			//�쐬�������̂��폜
			DeleteGO(m_remainingBulletsNumFont);
			DeleteGO(m_remainingBulletsSprite);
		}

		void RemainingBullets::Init()
		{
			//�g�p������������ė���
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//�t�H���g���쐬
			m_remainingBulletsNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			std::wstring text;
			text = std::to_wstring(m_player->GetRemainingBullet());
			m_remainingBulletsNumFont->Init(text.c_str());
			m_remainingBulletsNumFont->SetPosition(BULLET_NUM_FONT_POS);

			//�摜���쐬
			m_remainingBulletsSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_remainingBulletsSprite->Init(REMAINING_BULLETS_SPRITE_FILEPATH, REMAINING_BULLETS_SPRITE_WIDTH, REMAINING_BULLETS_SPRITE_HEIGHT);
			m_remainingBulletsSprite->SetPosition(REMAINING_BULLETS_SPRITE_POS);

			//����������
			m_isInitd = true;
		}

		void RemainingBullets::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�v���C���[�̎c�e��0�̏ꍇ�c
			if (m_player->GetRemainingBullet() == 0) {
				//�����[�h���̕\�����s��
				m_remainingBulletsNumFont->SetText(L"Reload...");
			}
			//�v���C���[�̎c�e��0�łȂ��ꍇ�c
			else {
				//�v���C���[�̎c�e����\������
				std::wstring text;
				text = std::to_wstring(m_player->GetRemainingBullet());
				m_remainingBulletsNumFont->SetText(text.c_str());
			}
			//�摜�ƃt�H���g�̏��������s
			m_remainingBulletsNumFont->Execution();
			m_remainingBulletsSprite->Execute();
		}

		void RemainingBullets::HideUI()
		{
			//UI�̃J���[�������Ȃ�����
			m_remainingBulletsNumFont->SetColor(render::COLORLESS);
			m_remainingBulletsSprite->SetColor(render::COLORLESS);
		}
	}
}