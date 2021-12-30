#include "stdafx.h"
#include "RepairTools.h"

namespace mainGame {
	namespace item {

		const float DISAPPEARANCE_TIME = 3.0f;

		void RepairTools::Activation()
		{
			//���_�ɕ��̃_���[�W��^���ĉ񕜂�����
			m_defensiveTarget->ReceiveDamage(-50.0f);
		}

		void RepairTools::InitData()
		{
			m_itemType = enItemRepairTools;

			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/item/item_guardup.tkm");

			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			m_endTime = DISAPPEARANCE_TIME;
		}

		void RepairTools::Efficacy()
		{

		}
	}
}