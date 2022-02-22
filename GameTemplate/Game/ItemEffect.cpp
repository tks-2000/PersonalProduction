#include "stdafx.h"
#include "ItemEffect.h"

namespace mainGame {
	namespace item {

		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/boxopen.efk";

		const Vector3 SPAWN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };

		const char16_t* GET_EFFECT_FILEPATH = u"Assets/effect/itemaura.efk";

		const Vector3 GET_EFFECT_START_SCALE = { 10.0f,10.0f,10.0f };

		const Vector3 GET_EFFECT_DOWN_SCALE_RATE = { 0.1f,0.1f,0.1f };



		EffectGenerator::EffectGenerator()
		{

		}

		EffectGenerator::~EffectGenerator()
		{
			DeleteGO(m_spawnEffect);
			DeleteGO(m_getEffect);
		}

		void EffectGenerator::Init(Item* item)
		{
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_spawnEffect->Init(SPAWN_EFFECT_FILEPATH);
			m_spawnEffect->SetScale(SPAWN_EFFECT_SCALE);

			m_getEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_getEffect->Init(GET_EFFECT_FILEPATH);
			m_getEffectScale = GET_EFFECT_START_SCALE;


			m_item = item;

			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			PlaySpawnEffect();
			PlayGetEffect();

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

		void EffectGenerator::PlayGetEffect()
		{
			if (m_item->IsPlayerGet() == true && m_isGetEffectPlay == false) {
				m_getEffect->SetPosition(m_item->GetPosition());
				m_getEffect->Play(false);
				m_isGetEffectPlay = true;
			}

			if (m_isGetEffectPlay == true) {
				m_getEffectScale -= GET_EFFECT_DOWN_SCALE_RATE;
			}

			m_getEffect->SetScale(m_getEffectScale);
			m_getEffect->Execution();
		}
	}
}