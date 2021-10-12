#include "stdafx.h"
#include "DefensiveTarget.h"

namespace {
	const  char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/box2.tkm";

	const float MAX_HP = 100.0f;
}

namespace mainGame {
	namespace defensiveTarget {
		DefensiveTarget::DefensiveTarget()
		{

			m_isInitd = false;
		}

		DefensiveTarget::~DefensiveTarget()
		{

		}

		void DefensiveTarget::Init()
		{
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(0);
			m_defensiveTargetModel->Init(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH);
			m_defensiveTargetHp = MAX_HP;
			m_scale = { 2.0f,2.0f,2.0f };
			m_isInitd = true;
		}


		void DefensiveTarget::Execution()
		{
			if (m_isInitd == false) {
				return;
			}
			if (m_isBreak == false) {
				if (m_defensiveTargetHp <= 0) {
					m_defensiveTargetHp = 0;
					m_isBreak = true;
				}
			}
			m_defensiveTargetModel->SetScale(m_scale);

			m_defensiveTargetModel->Execution();
		}
	}
}