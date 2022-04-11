#pragma once

namespace mainGame {
	namespace ui {

		/// @brief �����J�E���g�摜�̐�
		static const int NUM_SPRITE_NUM = 3;

		/// @brief �������Ԃ̕\�����s���N���X
		class TimeLimit
		{
		public:
			TimeLimit();
			~TimeLimit();
			/// @brief ������
			void Init();
			/// @brief ���s
			void Execution();
			/// @brief UI���\��
			void HideUI();
		private:
			/// @brief �J�E���g��i�߂�
			void CountDown();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �J�E���g�����ǂ����̃t���O
			bool m_isCountDown = false;
			/// @brief �J�E���g�\���̉摜
			render::sprite::SpriteRender* m_count[NUM_SPRITE_NUM] = { nullptr };
			/// @brief �J�n�̉摜
			render::sprite::SpriteRender* m_go = nullptr;
			/// @brief �J�n�摜��\������^�C�}�[
			float m_goSpriteDisplayTimer = 0.0f;
			/// @brief �^�C�}�[�\�����s���摜�̉��n
			render::sprite::SpriteRender* m_timerBaseSprite = nullptr;
			/// @brief �^�C�}�[�\�����s���摜�̘g
			render::sprite::SpriteRender* m_timerBaseFrame = nullptr;
			/// @brief �^�C���\���̃t�H���g
			render::font::FontRender* m_timeFont = nullptr;
			/// @brief �^�C���̐��l��\������t�H���g
			render::font::FontRender* m_timerNumFont = nullptr;
			/// @brief �^�C�}�[
			timer::Timer* m_timer = nullptr;
			/// @brief �Q�[���V�[��
			GameScene* m_gameScene = nullptr;
			/// @brief �T�E���h�v���C���[
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief �J�E���g�T�E���h��ID
			int m_countSoundID = 0;
			/// @brief �J�n�T�E���h��ID
			int m_goSoundID = 0;
			/// @brief �J�E���g�T�E���h�������t���O
			bool m_isPlayCountSE[NUM_SPRITE_NUM] = { false };
		};

	}
}