#include "stdafx.h"
#include "Timer.h"

namespace mainGame {
	namespace timer {
		/// @brief �J�n���̃J�E���g��
		const int START_TIME = 4;
		/// @brief �Q�[�����̃J�E���g��
		const int INGAME_TIME = 120;


		Timer::Timer()
		{
			//���������ŊJ�n
			m_isInitd = false;
			
		}

		Timer::~Timer()
		{
			
		}

		void Timer::Init()
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�^�C�}�[�̗ʂ�ݒ�
			m_stastTimer = START_TIME;
			m_inGameTimer = INGAME_TIME;

			//�^�C�}�[�\���̃t�H���g���쐬
			
			m_timeNum = m_stastTimer + 1.0f;
			
			m_timeFontPos = { 0.0f,300.0f };
			

			
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//����������
			m_isInitd = true;
		}

		void Timer::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//��Ԃɂ���Ď��s���鏈�������߂�
			switch (m_gameScene->GetGameSceneState())
			{
			case enGameSceneStart: {
				ExecuteStartTimer();
			}break;
			case enGameSceneInProgress: {
				ExecuteInGameTimer();
			}break;
			
			default:
				break;
			}

			
		}

		void Timer::ExecuteStartTimer()
		{
			//�J�n���̃^�C�}�[��i�߂�
			m_stastTimer -= g_gameTime->GetFrameDeltaTime();

			//�t�H���g�Ƀ^�C�}�[�̐��l��`����
			m_timeNum = m_stastTimer + 1.0f;
			

			//�^�C�}�[��0�ȉ��ɂȂ�����c
			if (m_stastTimer <= 0.0f) {
				//�Q�[�����̃J�E���g��i�ߎn�߂�
				m_state = enTimerExecute;
				
				m_gameScene->SetGameSceneState(enGameSceneInProgress);
				return;
			}
			
			
		}

		void Timer::ExecuteInGameTimer()
		{
			//�Q�[�����̃J�E���g��i�߂�
			m_inGameTimer -= g_gameTime->GetFrameDeltaTime();

			//�t�H���g�Ƀ^�C�}�[�̐��l��`����
			m_timeNum = m_inGameTimer + 1.0f;
			

			//�^�C�}�[��0�ȉ��ɂȂ�����c
			if (m_inGameTimer <= 0.0f) {
				//�Q�[���I����̃J�E���g��i�ߎn�߂�
				m_state = enTimerEnd;
				m_gameScene->SetGameSceneState(enGameSceneClear);
				return;
			}
		}
	}
}