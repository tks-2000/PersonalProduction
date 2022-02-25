#include "stdafx.h"
#include "RemainingBullets.h"

namespace mainGame {
	namespace ui {

		const Vector2 BULLET_FONT_POS = { 200.0f,-120.0f };

		const Vector2 BULLET_NUM_FONT_POS = { 375.0f,-105.0f };

		const int REMAINING_BULLETS_BASE_SPRITE_WIDTH = 325;

		const int REMAINING_BULLETS_BASE_SPRITE_HEIGHT = 100;

		const Vector3 REMAINING_BULLETS_BASE_SPRITE_POS = { 427.5f,-120.0f,0.0f };

		const int REMAINING_BULLETS_SPRITE_WIDTH = 100;

		const int REMAINING_BULLETS_SPRITE_HEIGHT = 100;

		const Vector3 REMAINING_BULLETS_SPRITE_POS = { 327.5f,-120.0f,0.0f };

		RemainingBullets::RemainingBullets()
		{

		}

		RemainingBullets::~RemainingBullets()
		{
			DeleteGO(m_remainingBulletsNumFont);
			DeleteGO(m_remainingBulletsSprite);
			DeleteGO(m_remainingBulletsBaseSprite);
		}

		void RemainingBullets::Init()
		{
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_remainingBulletsNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);


			std::wstring text;

			text = std::to_wstring(m_player->GetRemainingBullet());

			m_remainingBulletsNumFont->Init(text.c_str());

			m_remainingBulletsNumFont->SetPosition(BULLET_NUM_FONT_POS);

			m_remainingBulletsBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_remainingBulletsSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_remainingBulletsBaseSprite->Init("Assets/Image/WB.dds", REMAINING_BULLETS_BASE_SPRITE_WIDTH, REMAINING_BULLETS_BASE_SPRITE_HEIGHT);
			m_remainingBulletsSprite->Init("Assets/Image/bullet.dds", REMAINING_BULLETS_SPRITE_WIDTH, REMAINING_BULLETS_SPRITE_HEIGHT);

			m_remainingBulletsBaseSprite->SetPosition(REMAINING_BULLETS_BASE_SPRITE_POS);
			m_remainingBulletsSprite->SetPosition(REMAINING_BULLETS_SPRITE_POS);

			m_remainingBulletsBaseSprite->SetColor({1.0f,1.0f,1.0f,0.0f});

			m_isInitd = true;
		}

		void RemainingBullets::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (m_player->GetRemainingBullet() == 0) {
				m_remainingBulletsNumFont->SetText(L"Reload...");
			}
			else {
				std::wstring text;

				text = std::to_wstring(m_player->GetRemainingBullet());

				m_remainingBulletsNumFont->SetText(text.c_str());
			}

			m_remainingBulletsNumFont->Execution();

			m_remainingBulletsBaseSprite->Execute();

			m_remainingBulletsSprite->Execute();
		}
	}
}