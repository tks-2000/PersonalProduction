#include "stdafx.h"
#include "Stage.h"
namespace {
	const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/bg/testStage.tkm";
}

namespace mainGame {
	namespace stage {
		Stage::Stage()
		{
			m_isInitd = false;
		}

		Stage::~Stage()
		{
			DeleteGO(m_stageModel);
			DeleteGO(m_bgModel);
		}

		void Stage::Init()
		{
			//���ɏ���������Ă�������s���Ȃ�
			if (m_isInitd == true) {
				return;
			}
			//���f����\��
			m_stageModel = NewGO <render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_stageModel->Init(STAGE_MODEL_TKM_FILEPATH);
			m_stageModel->Execution();
			m_bgModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bgModel->Init("Assets/modelData/bg/sky_a.tkm");
			m_bgModel->Execution();
			//���f���̏�񂩂瓖���蔻����쐬
			m_staticStageObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModelWorldMatrix());
			m_isInitd = true;
		}
	}
}