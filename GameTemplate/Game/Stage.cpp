#include "stdafx.h"
#include "Stage.h"
namespace {
	const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/bg/testStage3.tkm";
	//const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/stage/Stage.tkm";
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
			//既に初期化されていたら実行しない
			if (m_isInitd == true) {
				return;
			}
			//モデルを表示
			m_stageModel = NewGO <render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_stageModel->Init(STAGE_MODEL_TKM_FILEPATH);
			m_stageModel->Execution();
			m_bgModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bgModel->Init("Assets/modelData/bg/sky_a.tkm");
			m_bgModel->Execution();
			/*m_miniMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapModel->Init(STAGE_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);
			m_miniMapModel->Execution();*/
			//モデルの情報から当たり判定を作成
			m_staticStageObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModelWorldMatrix());
			m_isInitd = true;
		}
	}
}