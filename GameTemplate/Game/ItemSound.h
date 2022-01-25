#pragma once

namespace mainGame {
	namespace item {
		class Sound
		{
		public:
			Sound();
			~Sound();
			void Init(Item* item);
			void Execution();

		private:
			void PlaySpawnSound();
			void PlayGetSound();
			void PlayCantGetSound();
			void PlayActivateSound();

			bool m_isInitd = false;

			int m_spawnSoundID = 0;

			bool m_isGetSoundPlay = false;

			int m_getSoundID = 0;

			bool m_isCantGetSoundPlay = false;

			int m_cantGetSoundID = 0;

			bool m_isActivateSoundPlay = false;

			int m_activateSoundID = 0;
			
			sound::SoundPlayer* m_soundPlayer = nullptr;

			Item* m_item = nullptr;
		};
	}
}
