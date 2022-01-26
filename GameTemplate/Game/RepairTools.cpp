#include "stdafx.h"
#include "RepairTools.h"

namespace mainGame {
	namespace item {

		const float DISAPPEARANCE_TIME = 3.0f;

		void RepairTools::Activation()
		{
			//拠点に負のダメージを与えて回復させる
			m_defensiveTarget->ReceiveDamage(-50.0f);

			m_isActivate = true;
		}

		void RepairTools::InitData()
		{
			m_itemType = enItemRepairTools;

			

			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			m_endTime = DISAPPEARANCE_TIME;
		}

		void RepairTools::Spawn()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/item/item_guardup.tkm");
		}

		void RepairTools::Efficacy()
		{

		}
	}
}