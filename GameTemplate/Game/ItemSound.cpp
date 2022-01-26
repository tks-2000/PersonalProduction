#include "stdafx.h"
#include "ItemSound.h"

namespace mainGame {
	namespace item {

		const wchar_t* SPAWN_SE_FILEPATH = L"Assets/sound/se/GuardEnd.wav";

		const float SPAWN_SE_VOLUME = 0.1f;

		const wchar_t* GET_SE_FILEPATH = L"Assets/sound/se/Ranking.wav";

		const float GET_SE_VOLUME = 0.1f;

		const wchar_t* CANTGET_SE_FILEPATH = L"Assets/sound/se/NoDamageCollide.wav";

		const float CANTGET_SE_VOLUME = 0.1f;

		const float CANTGET_SE_PLAY_TIMER_LOOP_TIME = 1.0f;

		const wchar_t* ACTIVATE_SE_FILEPATH = L"Assets/sound/se/ItemGet.wav";

		const float ACTIVATE_SE_VOLUME = 0.1f;

		Sound::Sound()
		{

		}

		Sound::~Sound()
		{

		}

		void Sound::Init(Item* item)
		{
			m_item = item;
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			m_spawnSoundID = m_soundPlayer->SetSE(SPAWN_SE_FILEPATH);
			m_getSoundID = m_soundPlayer->SetSE(GET_SE_FILEPATH);
			m_cantGetSoundID = m_soundPlayer->SetSE(CANTGET_SE_FILEPATH);
			m_activateSoundID = m_soundPlayer->SetSE(ACTIVATE_SE_FILEPATH);
			
			

			m_isInitd = true;
		}

		void Sound::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			PlaySpawnSound();
			PlayGetSound();
			PlayCantGetSound();
			PlayActivateSound();
		}

		void Sound::PlaySpawnSound()
		{
			if (m_item->IsSpawn() == true && m_isSpawnSoundPlay == false) {
				m_soundPlayer->SetSEVolume(m_spawnSoundID, SPAWN_SE_VOLUME);
				m_soundPlayer->PlaySE(m_spawnSoundID);
				m_isSpawnSoundPlay = true;
			}
		}

		void Sound::PlayGetSound()
		{
			if (m_item->IsPlayerGet() == true && m_isGetSoundPlay == false) {
				m_soundPlayer->SetSEVolume(m_getSoundID, GET_SE_VOLUME);
				m_soundPlayer->PlaySE(m_getSoundID);
				m_isGetSoundPlay = true;
			}
			
		}

		void Sound::PlayCantGetSound()
		{
			if (m_item->IsCantGet() == true) {
				
				if (m_cantGetSoundPlayTimer == 0.0f) {
					m_soundPlayer->SetSEVolume(m_cantGetSoundID, CANTGET_SE_VOLUME);
					m_soundPlayer->PlaySE(m_cantGetSoundID);
				}

				m_cantGetSoundPlayTimer += g_gameTime->GetFrameDeltaTime();
				if (m_cantGetSoundPlayTimer > CANTGET_SE_PLAY_TIMER_LOOP_TIME) {
					m_cantGetSoundPlayTimer = 0.0f;
				}
			}
			else {
				m_cantGetSoundPlayTimer = 0.0f;
			}

			
		}

		void Sound::PlayActivateSound()
		{
			if (m_item->IsActivate() == true && m_isActivateSoundPlay == false) {
				m_soundPlayer->SetSEVolume(m_activateSoundID, ACTIVATE_SE_VOLUME);
				m_soundPlayer->PlaySE(m_activateSoundID);
				m_isActivateSoundPlay = true;
			}
		}
	}
}