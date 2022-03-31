#pragma once

namespace mainGame {

	class GameScene;

	namespace timer {

		/// @brief �^�C�}�[���������Ă��邩�\���񋓌^
		enum EnTimerState {
			/// @brief �Q�[���J�n�̃J�E���g��
			enTimerStart,
			/// @brief �Q�[�����̃J�E���g��
			enTimerExecute,
			/// @brief �Q�[���I����̃J�E���g��
			enTimerEnd,
			/// @brief �^�C�}�[�̏�Ԃ̍��v��
			enTimerStateNum
		};

		class Timer : public IGameObject
		{
		public:
			Timer();
			~Timer();

			/// @brief ������
			void Init();

			/// @brief ���s
			void Execution();

			/// @brief �^�C�}�[�̏�Ԃ��擾
			/// @return �^�C�}�[�������s���Ă��邩�̃X�e�[�g
			const EnTimerState& GetTimerState() { return m_state; }

			/// @brief �^�C�}�[���擾
			/// @return �^�C�}�[�̒l
			const int GetTimer() const { return m_timeNum; }

			/// @brief �J�n���̃^�C�}�[���擾
			/// @return �J�n���̃^�C�}�[�̒l
			const int GetStartTimer() const { return m_startTimeNum; }

		private:
			/// @brief �J�n���̃^�C�}�[��i�߂�
			void ExecuteStartTimer();
			/// @brief �Q�[�����̃^�C�}�[��i�߂�
			void ExecuteInGameTimer();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �J�n���̃^�C�}�[
			float m_startTimer = 0.0f;
			/// @brief �Q�[�����̃^�C�}�[
			float m_inGameTimer = 0.0f;
			int m_startTimeNum = 0;
			/// @brief �t�H���g�ɐݒ肷�鐔�l
			int m_timeNum = 0;
			/// @brief �t�H���g�̏�Ԃ�\���X�e�[�g
			EnTimerState m_state = enTimerStart;
			/// @brief �^�C�}�[�̕\���ʒu
			Vector2 m_timeFontPos = g_vec2Zero;
			/// @brief �Q�[���V�[��
			GameScene* m_gameScene = nullptr;
		};
	}
}
