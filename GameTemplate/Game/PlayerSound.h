#pragma once

namespace mainGame {
	namespace player {
		class Sound
		{
		public:
			Sound();
			~Sound();
			void Init(Player* player);
			void Execution();

		private:
			void PlayWalkSound();
			void PlayRunSound();
			void PlayAttackSound();
			void PlayDamageSound();
			void PlayDownSound();

			bool m_isInitd = false;

			float m_walkSoundTimer = 0.0f;

			int m_walkSoundID = 0;

			float m_runSoundTimer = 0.0f;

			int m_runSoundID = 0;

			bool m_isAttackSoundPlay = false;

			float m_attackSoundPlayTimer = 0.0f;

			int m_attackSoundID = 0;

			bool m_isDamageSoundPlay = false;

			int m_damageSoundID = 0;

			bool m_isKneeSoundPlay = false;

			int m_kneeSoundID = 0;

			float m_kneeSoundTimer = 0.0f;

			bool m_isDownSoundPlay = false;

			int m_downSoundID = 0;

			float m_downSoundTimer = 0.0f;

			

			sound::SoundPlayer* m_soundPlayer;

			Player* m_player = nullptr;
		};
	}
}
