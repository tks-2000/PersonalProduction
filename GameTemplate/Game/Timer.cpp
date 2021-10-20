#include "stdafx.h"
#include "Timer.h"

namespace mainGame {
	namespace timer {
		/// @brief �J�n���̃J�E���g��
		const int START_TIME = 3;
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
			m_stastTimer = 3.0f;
			m_inGameTimer = 120.0f;

			//�^�C�}�[�\���̃t�H���g���쐬
			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			int time = m_stastTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->Init(conversion.c_str());
			m_timeFontPos = { 0.0f,300.0f };
			m_timeFont->SetPosition(m_timeFontPos);

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
			switch (m_state)
			{
			case enTimerStart: {
				ExecuteStartTimer();
			}break;
			case enTimerExecute: {
				ExecuteInGameTimer();
			}break;
			case enTimerEnd: {

			}break;
			default:
				break;
			}

			m_timeFont->Execution();
		}

		void Timer::ExecuteStartTimer()
		{
			//�J�n���̃^�C�}�[��i�߂�
			m_stastTimer -= g_gameTime->GetFrameDeltaTime();

			//�t�H���g�Ƀ^�C�}�[�̐��l��`����
			int time = m_stastTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->SetText(conversion.c_str());

			//�^�C�}�[��0�ȉ��ɂȂ�����c
			if (m_stastTimer <= 0.0f) {
				//�Q�[�����̃J�E���g��i�ߎn�߂�
				m_state = enTimerExecute;
				return;
			}
			
			
		}

		void Timer::ExecuteInGameTimer()
		{
			//�Q�[�����̃J�E���g��i�߂�
			m_inGameTimer -= g_gameTime->GetFrameDeltaTime();

			//�t�H���g�Ƀ^�C�}�[�̐��l��`����
			int time = m_inGameTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->SetText(conversion.c_str());

			//�^�C�}�[��0�ȉ��ɂȂ�����c
			if (m_inGameTimer <= 0.0f) {
				//�Q�[���I����̃J�E���g��i�ߎn�߂�
				m_state = enTimerEnd;
				return;
			}
		}
	}
}