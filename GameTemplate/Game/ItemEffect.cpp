#include "stdafx.h"
#include "ItemEffect.h"

namespace mainGame {
	namespace item {

		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/boxopen.efk";

		const Vector3 SPAWN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };

		EffectGenerator::EffectGenerator()
		{

		}

		EffectGenerator::~EffectGenerator()
		{
			DeleteGO(m_spawnEffect);
		}

		void EffectGenerator::Init(Item* item)
		{
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_spawnEffect->Init(SPAWN_EFFECT_FILEPATH);
			m_spawnEffect->SetScale(SPAWN_EFFECT_SCALE);

			m_item = item;

			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			PlaySpawnEffect();


		}

		void EffectGenerator::PlaySpawnEffect()
		{
			if (m_item->IsSpawn() == true && m_isSpawnEffectPlay == false) {
				m_spawnEffect->SetPosition(m_item->GetPosition());
				m_spawnEffect->Play(false);
				m_isSpawnEffectPlay = true;
			}

			m_spawnEffect->Execution();
		}
	}
}