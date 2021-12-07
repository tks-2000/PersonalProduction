#include "stdafx.h"
#include "RemainingBullets.h"

namespace mainGame {
	namespace ui {

		const Vector2 BULLET_FONT_POS = { 400.0f,-200.0f };

		const Vector2 BULLET_NUM_FONT_POS = { 200.0f,-200.0f };

		RemainingBullets::RemainingBullets()
		{

		}

		RemainingBullets::~RemainingBullets()
		{
			DeleteGO(m_bulletsFont);
			DeleteGO(m_remainingBulletsNumFont);
		}

		void RemainingBullets::Init()
		{
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_remainingBulletsNumFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);

			m_bulletsFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);

			m_bulletsFont->Init(L"Bullet : ");

			std::wstring text;

			text = std::to_wstring(m_player->GetRemainingBullet());

			m_remainingBulletsNumFont->Init(text.c_str());

			m_remainingBulletsNumFont->SetPosition(BULLET_FONT_POS);

			m_bulletsFont->SetPosition(BULLET_NUM_FONT_POS);

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

			m_bulletsFont->Execution();
		}
	}
}