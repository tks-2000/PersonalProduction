#pragma once

namespace mainGame {
	namespace player {
		/// @brief �v���C���[�̉������Ǘ�����N���X
		class Sound
		{
		public:
			Sound();
			~Sound();
			/// @brief 
			/// @param player 
			void Init(Player* player);
			/// @brief 
			void Execution();

		private:
			/// @brief ���s�T�E���h���Đ�
			void PlayWalkSound();
			/// @brief ���s�T�E���h���Đ�
			void PlayRunSound();
			/// @brief �U���T�E���h���Đ�
			void PlayAttackSound();
			/// @brief �_���[�W�T�E���h���Đ�
			void PlayDamageSound();
			/// @brief �_�E���T�E���h���Đ�
			void PlayDownSound();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief ���s�T�E���h�̃^�C�}�[
			float m_walkSoundTimer = 0.0f;
			/// @brief ���s�T�E���h��ID
			int m_walkSoundID = 0;
			/// @brief ���s�T�E���h�̃^�C�}�[
			float m_runSoundTimer = 0.0f;
			/// @brief ���s�T�E���h��ID
			int m_runSoundID = 0;
			/// @brief �U���T�E���h�̍Đ��t���O
			bool m_isAttackSoundPlay = false;
			/// @brief �U���T�E���h�̃^�C�}�[
			float m_attackSoundPlayTimer = 0.0f;
			/// @brief �U���T�E���h��ID
			int m_attackSoundID = 0;
			/// @brief �_���[�W�T�E���h�̍Đ��t���O
			bool m_isDamageSoundPlay = false;
			/// @brief �_���[�W�T�E���h��ID
			int m_damageSoundID = 0;
			/// @brief �G�����T�E���h�̍Đ��t���O
			bool m_isKneeSoundPlay = false;
			/// @brief �G�����T�E���h��ID
			int m_kneeSoundID = 0;
			/// @brief �G�����T�E���h�̃^�C�}�[
			float m_kneeSoundTimer = 0.0f;
			/// @brief �|���T�E���h�̍Đ��t���O
			bool m_isDownSoundPlay = false;
			/// @brief �|���T�E���h��ID
			int m_downSoundID = 0;
			/// @brief �|���T�E���h�̃^�C�}�[
			float m_downSoundTimer = 0.0f;

			
			/// @brief �T�E���h�v���C���[
			sound::SoundPlayer* m_soundPlayer;
			/// @brief �v���C���[
			Player* m_player = nullptr;
		};
	}
}
