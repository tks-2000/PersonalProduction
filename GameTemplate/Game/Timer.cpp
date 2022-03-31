#include "stdafx.h"
#include "Timer.h"

namespace mainGame {
	namespace timer {
		/// @brief �J�n���̃J�E���g��
		const int START_TIME = 4;
		/// @brief �Q�[�����̃J�E���g��
		const int INGAME_TIME = 120;
		/// @brief �^�C�}�[�t�H���g�̍��W
		const Vector2 TIMER_FONT_POS = { 0.0f,300.0f };

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

			//�ϐ���������
			m_startTimer = START_TIME;
			m_inGameTimer = INGAME_TIME;
			m_timeNum = m_startTimer + 1.0f;
			m_timeFontPos = TIMER_FONT_POS;
			
			//�K�v�ȏ����擾
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

			//�Q�[���V�[���̏�Ԃɂ���Ď��s���鏈�������߂�
			switch (m_gameScene->GetGameSceneState())
			{
				//�Q�[���J�n��
			case enGameSceneStart: {
				//�J�n���̃^�C�}�[��i�߂�
				ExecuteStartTimer();
			}break;
				//�Q�[����
			case enGameSceneInProgress: {
				//�Q�[�����̃^�C�}�[��i�߂�
				ExecuteInGameTimer();
			}break;
			
			default:
				break;
			}

			
		}

		void Timer::ExecuteStartTimer()
		{
			//�J�n���̃^�C�}�[��i�߂�
			m_startTimer -= g_gameTime->GetFrameDeltaTime();

			//�t�H���g�Ƀ^�C�}�[�̐��l��`����
			m_timeNum = m_startTimeNum = m_startTimer + 1.0f;
			

			//�^�C�}�[��0�ȉ��ɂȂ�����c
			if (m_startTimer <= 0.0f) {
				//�Q�[�����̃J�E���g��i�ߎn�߂�
				m_state = enTimerExecute;
				//�Q�[���V�[�����Q�[�����ɕύX
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
				//�Q�[���V�[�����N���A��ԂɕύX
				m_gameScene->SetGameSceneState(enGameSceneClear);
				return;
			}
		}
	}
}