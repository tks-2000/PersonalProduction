#include "stdafx.h"
#include "PlayerEffect.h"

namespace mainGame {
	namespace player {

		EffectGenerator::EffectGenerator()
		{
			
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

			
		}

		
	}
}