#include "stdafx.h"
#include "GameUI.h"

namespace mainGame {
	namespace ui {
		/// @brief �Q�[���N���A�̉摜�̃t�@�C���p�X
		const char* GAME_CLEAR_SPRITE_FILEPATH = "Assets/Image/GAMECLEAR.dds";
		/// @brief �Q�[���I�[�o�[�̉摜�̃t�@�C���p�X
		const char* GAME_OVER_SPRITE_FILEPATH = "Assets/Image/GAMEOVER.dds";
		/// @brief �Q�[���I���̉摜�̉���
		const int GAME_END_SPRITE_WIDTH = 1000;
		/// @brief �Q�[���I���̉摜�̏c��
		const int GAME_END_SPRITE_HEIGHT = 200;

		GameUI::GameUI()
		{

		}

		GameUI::~GameUI()
		{
			//�Q�[���I�����̉摜���폜
			DeleteGO(m_gameEndSprite);
		}

		void GameUI::Init()
		{
			//�S�Ă�UI��������
			m_oenedItem.Init();
			m_baseEndurance.Init();
			m_timeLimit.Init();
			m_remainingBullets.Init();
			m_miniMap.Init();
			
			//�I�����ɕ\������摜���쐬
			m_gameEndSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			//�g�p������������ė���
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);
			m_timer = FindGO<timer::Timer>(timer::TIMER_NAME);

			//����������
			m_isInitd = true;
		}

		void GameUI::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�S�Ă�UI�̏��������s
			m_oenedItem.Execution();
			m_baseEndurance.Execution();
			m_timeLimit.Execution();
			m_remainingBullets.Execution();
			m_miniMap.Execution();
			
			//�I�����̉摜���o�������Ă��炸�A�Q�[���V�[���̃X�e�[�g���N���A���I�[�o�[�ɂȂ��Ă�����c
			if (m_gameEndSpriteFlag == false &&
				m_gameScene->GetGameSceneState() == enGameSceneClear ||
				m_gameScene->GetGameSceneState() == enGameSceneOver
				) 
			{
				//�I�����̉摜��\��
				DisplayGameEndSprite();
			}

			//�I�����̉摜��\�����Ă���ꍇ�c
			if (m_gameEndSpriteFlag == true) {
				//�I�����̏������s��
				GameEndExecution();
			}
		}

		

		void GameUI::DisplayGameEndSprite()
		{
			//�Q�[���V�[���̃X�e�[�g���N���A�̏ꍇ
			if (m_gameScene->GetGameSceneState() == enGameSceneClear) {
				//�Q�[���N���A�̉摜��\��
				m_gameEndSprite->Init(GAME_CLEAR_SPRITE_FILEPATH, GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}

			//�Q�[���V�[���̃X�e�[�g���I�[�o�[�̏ꍇ
			if (m_gameScene->GetGameSceneState() == enGameSceneOver) {
				//�Q�[���I�[�o�[�̉摜��\��
				m_gameEndSprite->Init(GAME_OVER_SPRITE_FILEPATH, GAME_END_SPRITE_WIDTH, GAME_END_SPRITE_HEIGHT);
			}

			//�Q�[���I�����̉摜�\���t���O�𗧂Ă�
			m_gameEndSpriteFlag = true;
		}

		

		void GameUI::GameEndExecution()
		{
			//�Q�[���I�����ɏo������摜�̏��������s
			m_gameEndSprite->Execute();

			//�S�Ă�UI���\���ɂ���
			m_oenedItem.HideUI();
			m_baseEndurance.HIdeUI();
			m_remainingBullets.HideUI();
			m_timeLimit.HideUI();
			m_miniMap.HideUI();
		}
	}
}