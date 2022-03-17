#include "stdafx.h"
#include "AttackPoint.h"

namespace mainGame {
	namespace defensiveTarget {
		AttackPoint::AttackPoint()
		{

		}

		AttackPoint::~AttackPoint()
		{
			//DeleteGO(m_model);
		}

		void AttackPoint::Init(DefensiveTarget* defensiveTarget)
		{

			m_defensiveTarget = defensiveTarget;

			//m_model = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);

			//m_model->Init("Assets/modelData/box/box2.tkm");

			m_isInitd = true;
		}

		void AttackPoint::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			//m_model->SetPosition(m_postion);
			//m_model->Execution();
		}
	}
}