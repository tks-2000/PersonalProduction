#include "stdafx.h"
#include "DefensiveTarget.h"

namespace {
	/// @brief �h�q�Ώۂ̃��f���t�@�C���p�X
	const  char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/box2.tkm";
	/// @brief �h�q�Ώۂ̍ő�ϋv��
	const float MAX_HP = 100.0f;
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
			}
		}

		void DefensiveTarget::Init()
		{
			//�h�q�Ώۂ̃��f����������
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(0);
			m_defensiveTargetModel->Init(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH);

			//�����p�����[�^�[������
			m_defensiveTargetHp = MAX_HP;
			m_scale = { 2.0f,2.0f,2.0f };
			m_isInitd = true;
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
				}
			}
		}
	}
}