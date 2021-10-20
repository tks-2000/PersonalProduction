#pragma once

namespace mainGame {
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
		private:
			/// @brief �J�n���̃^�C�}�[��i�߂�
			void ExecuteStartTimer();
			/// @brief �Q�[�����̃^�C�}�[��i�߂�
			void ExecuteInGameTimer();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �J�n���̃^�C�}�[
			float m_stastTimer = 0.0f;
			/// @brief �Q�[�����̃^�C�}�[
			float m_inGameTimer = 0.0f;
			/// @brief �t�H���g�ɐݒ肷�鐔�l
			int m_timeNum = 0;
			/// @brief �t�H���g�̏�Ԃ�\���X�e�[�g
			EnTimerState m_state = enTimerStart;
			/// @brief �^�C�}�[�̐��l��\������t�H���g
			render::font::FontRender* m_timeFont = nullptr;
			/// @brief �^�C�}�[�̕\���ʒu
			Vector2 m_timeFontPos = g_vec2Zero;
		};
	}
}