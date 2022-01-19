#include "stdafx.h"
#include "PlayerEffect.h"

namespace mainGame {
	namespace player {

		EffectGenerator::EffectGenerator()
		{
			m_attackEffect.effect.Init(u"Assets/effect/kick.efk");
		}

		EffectGenerator::~EffectGenerator()
		{

		}

		void EffectGenerator::Init(Player* player)
		{
			m_player = player;

			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (m_player->GetPlayerStatus() == enPlayerAttack) {
				m_attackEffect.pos = m_player->GetPlayerPosition();
				m_attackEffect.qRot = m_player->GetPlayerRotation();
				m_attackEffect.scale = { 10.0f,10.0f,10.0f };

				if (m_attackEffect.effect.IsPlay() == false) {
					//m_attackEffect.effect.Play();
				}
			}

			UpdateEffect(m_attackEffect);
		}

		void EffectGenerator::UpdateEffect(EffectData& effectData)
		{
			effectData.effect.SetPosition(effectData.pos);
			effectData.effect.SetRotation(effectData.qRot);
			effectData.effect.SetScale(effectData.scale);
			effectData.effect.Update();
		}
	}
}