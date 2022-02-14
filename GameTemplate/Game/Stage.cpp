#include "stdafx.h"
#include "Stage.h"
namespace {
	const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/bg/testStage3.tkm";
	//const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/stage/Stage.tkm";
}

namespace mainGame {
	namespace stage {


		const wchar_t* STAGE_BGM_FILEPATH = L"Assets/sound/bgm/inGameBgm.wav";

		const float STAGE_BGM_VOLUME = 0.1f;

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
			m_stageModel->InitDeferrd(STAGE_MODEL_TKM_FILEPATH);
			//m_stageModel->CreateShadow();
			m_stageModel->Execution();
			m_bgModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bgModel->InitDeferrd("Assets/modelData/bg/sky_a.tkm");
			m_bgModel->Execution();
			/*m_miniMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapModel->Init(STAGE_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);
			m_miniMapModel->Execution();*/

			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_stageSoundID = m_soundPlayer->SetBGM(STAGE_BGM_FILEPATH);
			m_soundPlayer->SetBGMVolume(m_stageSoundID, STAGE_BGM_VOLUME);
			m_soundPlayer->PlayBGM(m_stageSoundID, true);

			//モデルの情報から当たり判定を作成
			m_staticStageObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModelWorldMatrix());
			m_isInitd = true;
		}

		void Stage::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (m_gameScene->GetGameSceneState() == enGameSceneClear || m_gameScene->GetGameSceneState() == enGameSceneOver) {
				m_soundPlayer->StopBGM(m_stageSoundID);
			}

		}
	}
}