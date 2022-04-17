#include "stdafx.h"
#include "RepairTools.h"

namespace mainGame {
	namespace item {
		/// @brief �A�C�e�����f���̃t�@�C���p�X
		const char* TOOLS_MODEL_FILEPATH = "Assets/modelData/item/item_guardup.tkm";
		/// @brief ���ʔ�������I���܂ł̎���
		const float DISAPPEARANCE_TIME = 3.0f;
		/// @brief �񕜃_���[�W
		const float RECOVERY_DAMAGE = -50.0f;

		void RepairTools::Activation()
		{
			//���_�ɕ��̃_���[�W��^���ĉ񕜂�����
			m_defensiveTarget->ReceiveDamage(RECOVERY_DAMAGE);

			//���ʔ����t���O�𗧂Ă�
			m_isActivate = true;
		}

		void RepairTools::InitData()
		{
			//�ϐ���������
			m_itemType = enItemRepairTools;
			m_endTime = DISAPPEARANCE_TIME;

			//�g�p��������擾
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
		}

		void RepairTools::Spawn()
		{
			//���f�����쐬
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->InitDeferrd(TOOLS_MODEL_FILEPATH);
		}

		void RepairTools::Efficacy()
		{

		}
	}
}