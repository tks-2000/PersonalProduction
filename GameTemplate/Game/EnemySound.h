#pragma once

namespace mainGame {

	namespace enemy {
		/// @brief �G�̃T�E���h�𐧌䂷��N���X
		class SoundPlayer
		{
		public:
			SoundPlayer();
			~SoundPlayer();
			/// @brief ������
			/// @param enemy �G�l�~�[�̃A�h���X
			void Init(Enemy* enemy);
			/// @brief ���s
			void Execution();

		private:
			/// @brief �o�����ɖ�T�E���h�𐧌䂷��֐�
			void PlaySpawnSound();
			/// @brief �U�����ɖ�T�E���h�𐧌䂷��֐�
			void PlayAttackSound();
			/// @brief �_���[�W���ɖ�T�E���h�𐧌䂷��֐�
			void PlayDamageSound();
			/// @brief ���S���ɖ�T�E���h�𐧌䂷��֐�
			void PlayDeadSound();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �o���T�E���h��ID
			int m_spawnSoundID = 0;
			/// @brief �U���T�E���hID
			int m_attackSoundID = 0;
			/// @brief �_���[�W�T�E���h��ID
			int m_damageSoundID = 0;
			/// @brief ���S�T�E���h�̍Đ��t���O
			bool m_isPlayDeadSound = false;
			/// @brief ���S�T�E���h��ID
			int m_deadSoundID = 0;
			/// @brief �G�l�~�[
			Enemy* m_enemy = nullptr;
			/// @brief 
			sound::SoundPlayer* m_soundPlayer = nullptr;

		};
	}
}
