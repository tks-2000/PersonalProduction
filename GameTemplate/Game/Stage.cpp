#include "stdafx.h"
#include "Stage.h"

namespace mainGame {
	namespace stage {
		/// @brief ステージのモデルファイルパス
		const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/bg/Stage2.tkm";
		/// @brief 背景のモデルファイルパス
		const char* BACKGROUND_MODEL_FILEPATH = "Assets/modelData/bg/sky_a.tkm";
		/// @brief ステージのサウンドファイルパス
		const wchar_t* STAGE_BGM_FILEPATH = L"Assets/sound/bgm/inGameBgm.wav";
		/// @brief ステージのサウンドの大きさ
		const float STAGE_BGM_VOLUME = 0.1f;

		Stage::Stage()
		{
			m_isInitd = false;
		}

		Stage::~Stage()
		{
			//モデルを削除
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
			m_stageModel->InitDeferrd(STAGE_MODEL_TKM_FILEPATH,true);
			m_stageModel->Execution();
			m_bgModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bgModel->InitDeferrd(BACKGROUND_MODEL_FILEPATH);
			m_bgModel->Execution();
			/*m_miniMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapModel->Init(STAGE_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);
			m_miniMapModel->Execution();*/

			//使用する情報を取得
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			//サウンドを初期化
			m_stageSoundID = m_soundPlayer->SetBGM(STAGE_BGM_FILEPATH);
			m_soundPlayer->SetBGMVolume(m_stageSoundID, STAGE_BGM_VOLUME);
			m_soundPlayer->PlayBGM(m_stageSoundID, true);

			//モデルの情報から当たり判定を作成
			m_staticStageObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModelWorldMatrix());

			//初期化完了
			m_isInitd = true;
		}

		void Stage::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//ゲームクリア状態かゲームオーバー状態になったら…
			if (m_gameScene->GetGameSceneState() == enGameSceneClear || m_gameScene->GetGameSceneState() == enGameSceneOver) {
				//サウンドを停止
				m_soundPlayer->StopBGM(m_stageSoundID);
			}

		}
	}
}