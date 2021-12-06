#include "stdafx.h"
#include "BaseEndurance.h"

namespace mainGame {
	namespace ui {

		const int ENDURANCE_SPRITE_WIDTH = 1000.0f;

		const int ENDURANCE_SPRITE_HEIGHT = 25;

		const Vector3 ENDURANCE_SPRITE_POS = { -500.0f,280.0f,0.0f };

		const Vector4 ENDURANCE_SPRITE_NORMAL_COLOR = { 0.0f,2.0f,0.0f,1.0f };

		const Vector4 ENDURANCE_SPRITE_END_COLOR = { 2.0f,0.0f,0.0f,1.0f };

		const Vector2 ENDURANCE_SPRITE_PIVOT = { 0.0f,0.5f };

		BaseEndurance::BaseEndurance()
		{
			m_isInitd = false;
		}

		BaseEndurance::~BaseEndurance()
		{
			DeleteGO(m_enduranceSprite);
		}

		void BaseEndurance::Init()
		{
			m_enduranceBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_enduranceSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_enduranceBaseSprite->Init("Assets/Image/WB.dds", ENDURANCE_SPRITE_WIDTH, ENDURANCE_SPRITE_HEIGHT);

			m_enduranceSprite->Init("Assets/Image/WB.dds", ENDURANCE_SPRITE_WIDTH,ENDURANCE_SPRITE_HEIGHT);

			m_enduranceBaseSprite->SetColor(g_vec4Black);

			m_enduranceSpritePos = ENDURANCE_SPRITE_POS;

			m_enduranceSpriteColor = ENDURANCE_SPRITE_NORMAL_COLOR;

			m_enduranceBaseSprite->SetPosition(m_enduranceSpritePos);

			m_enduranceSprite->SetPosition(m_enduranceSpritePos);

			m_enduranceBaseSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);

			m_enduranceSprite->SetPivot(ENDURANCE_SPRITE_PIVOT);

			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			m_isInitd = true;
		}

		void BaseEndurance::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			

			m_enduranceSprite->SetScale(m_enduranceSpriteScale);

			m_enduranceSprite->SetColor(m_enduranceSpriteColor);

			m_enduranceBaseSprite->Execute();

			m_enduranceSprite->Execute();
		}

		void BaseEndurance::SetDamage()
		{
			
		}

		void BaseEndurance::ApplyDamage()
		{
			float hpRatio = m_defensiveTarget->GetDefensiveTargetHp() / m_defensiveTarget->GetDefensiveTargetMaxHp();

			m_enduranceSpriteScale.x = hpRatio;

			m_enduranceSpriteColor.Lerp(hpRatio,
				ENDURANCE_SPRITE_END_COLOR,
				ENDURANCE_SPRITE_NORMAL_COLOR);

		}
	}
}