#include "stdafx.h"
#include "DefensiveTarget.h"

namespace {
	/// @brief �h�q�Ώۂ̃��f���t�@�C���p�X
	const  char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/box2.tkm";

	const char* MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/boxMapModel.tkm";
	/// @brief �h�q�Ώۂ̍��W
	const Vector3 DEFENSIVE_TARGET_POS = { 0.0f,0.0f,0.0f };
	/// @brief �h�q�Ώۂ̍ő�ϋv��
	const int MAX_HP = 100;
}

namespace mainGame {
	namespace defensiveTarget {
		DefensiveTarget::DefensiveTarget()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		DefensiveTarget::~DefensiveTarget()
		{
			//�j�󂳂�Ă��Ȃ��ꍇ�c
			if (m_isBreak == false) {
				//���f�����폜
				DeleteGO(m_defensiveTargetModel);
				DeleteGO(m_miniMapdefensiveTargetModel);
			}
		}

		void DefensiveTarget::Init()
		{

			//�h�q�Ώۂ̃��f����������
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(0);
			m_defensiveTargetModel->Init(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH);

			m_miniMapdefensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapdefensiveTargetModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapdefensiveTargetModel->Init(MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);

			//�����p�����[�^�[������
			m_defensiveTargetHp = MAX_HP;
			m_position = DEFENSIVE_TARGET_POS;
			m_scale = { 1.0f,1.0f,1.0f };
			m_defensiveTargetModel->SetPosition(m_position);
			m_defensiveTargetModel->Execution();

			//���f���̏�񂩂瓖���蔻����쐬
			m_staticDefensiveTargetObject.CreateFromModel(m_defensiveTargetModel->GetModel(),m_defensiveTargetModel->GetModelWorldMatrix());
			m_isInitd = true;
			m_isBreak = false;
		}


		void DefensiveTarget::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�j�󂳂�Ă��Ȃ��Ƃ��c
			if (m_isBreak == false) {

				//�g�嗦��ݒ�
				m_defensiveTargetModel->SetScale(m_scale);
				//���f���̏��������s
				m_defensiveTargetModel->Execution();

				//�ϋv�͂�0�ȉ��ɂȂ�����c
				if (m_defensiveTargetHp <= 0) {
					m_defensiveTargetHp = 0;
					//�j�󂳂ꂽ���Ƃɂ���
					m_isBreak = true;

					//���f�����폜
					DeleteGO(m_defensiveTargetModel);
					DeleteGO(m_miniMapdefensiveTargetModel);
				}
			}
		}
	}
}