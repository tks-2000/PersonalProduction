#include "stdafx.h"
#include "Stage.h"

namespace mainGame {
	namespace stage {
		/// @brief �X�e�[�W�̃��f���t�@�C���p�X
		const char* STAGE_MODEL_TKM_FILEPATH = "Assets/modelData/bg/Stage2.tkm";
		/// @brief �w�i�̃��f���t�@�C���p�X
		const char* BACKGROUND_MODEL_FILEPATH = "Assets/modelData/bg/sky_a.tkm";
		/// @brief �X�e�[�W�̃T�E���h�t�@�C���p�X
		const wchar_t* STAGE_BGM_FILEPATH = L"Assets/sound/bgm/inGameBgm.wav";
		/// @brief �X�e�[�W�̃T�E���h�̑傫��
		const float STAGE_BGM_VOLUME = 0.1f;

		Stage::Stage()
		{
			m_isInitd = false;
		}

		Stage::~Stage()
		{
			//���f�����폜
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
			m_stageModel->InitDeferrd(STAGE_MODEL_TKM_FILEPATH,true);
			m_stageModel->Execution();
			m_bgModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bgModel->InitDeferrd(BACKGROUND_MODEL_FILEPATH);
			m_bgModel->Execution();
			/*m_miniMapModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapModel->Init(STAGE_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);
			m_miniMapModel->Execution();*/

			//�g�p��������擾
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			//�T�E���h��������
			m_stageSoundID = m_soundPlayer->SetBGM(STAGE_BGM_FILEPATH);
			m_soundPlayer->SetBGMVolume(m_stageSoundID, STAGE_BGM_VOLUME);
			m_soundPlayer->PlayBGM(m_stageSoundID, true);

			//���f���̏�񂩂瓖���蔻����쐬
			m_staticStageObject.CreateFromModel(m_stageModel->GetModel(), m_stageModel->GetModelWorldMatrix());

			//����������
			m_isInitd = true;
		}

		void Stage::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�Q�[���N���A��Ԃ��Q�[���I�[�o�[��ԂɂȂ�����c
			if (m_gameScene->GetGameSceneState() == enGameSceneClear || m_gameScene->GetGameSceneState() == enGameSceneOver) {
				//�T�E���h���~
				m_soundPlayer->StopBGM(m_stageSoundID);
			}

		}
	}
}