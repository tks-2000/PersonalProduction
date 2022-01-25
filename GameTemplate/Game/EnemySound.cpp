#include "stdafx.h"
#include "EnemySound.h"

namespace mainGame {
	namespace enemy {

		const wchar_t* SPAWN_SE_FILEPATH = L"Assets/sound/se/GuardStart.wav";

		const float SPAWN_SE_VOLUME = 0.1f;

		const wchar_t* ATTACK_SE_FILEPATH = L"Assets/sound/se/enemyAttack.wav";

		const float ATTACK_SE_VOLUME = 0.1f;

		const wchar_t* DAMAGE_SE_FILEPATH = L"Assets/sound/se/enemyDamage.wav";

		const float DAMAGE_SE_VOLUME = 0.1f;

		const wchar_t* DEAD_SE_FILEPATH = L"Assets/sound/se/enemyDisappearance.wav";

		const float DEAD_SE_VOLUME = 0.1f;

		const float DEAD_SE_PLAYING_TIME_RATE = 0.99;
		
		SoundPlayer::SoundPlayer()
		{

		}

		SoundPlayer::~SoundPlayer()
		{

		}

		void SoundPlayer::Init(Enemy* enemy)
		{
			m_enemy = enemy;

			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			m_spawnSoundID = m_soundPlayer->SetSE(SPAWN_SE_FILEPATH);
			
			m_attackSoundID = m_soundPlayer->SetSE(ATTACK_SE_FILEPATH);
			
			m_damageSoundID = m_soundPlayer->SetSE(DAMAGE_SE_FILEPATH);

			m_deadSoundID = m_soundPlayer->SetSE(DEAD_SE_FILEPATH);

			PlaySpawnSound();

			m_isInitd = true;
		}

		void SoundPlayer::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			PlayAttackSound();
			PlayDamageSound();
			PlayDeadSound();

		}

		void SoundPlayer::PlaySpawnSound()
		{
			
			m_soundPlayer->SetSEVolume(m_spawnSoundID, SPAWN_SE_VOLUME);
			m_soundPlayer->PlaySE(m_spawnSoundID);
		}

		void SoundPlayer::PlayAttackSound()
		{
			if (m_enemy->GetState() == enEnemyAttack && m_enemy->IsAttack() == true) {
				
				m_soundPlayer->SetSEVolume(m_attackSoundID, ATTACK_SE_VOLUME);
				m_soundPlayer->PlaySE(m_attackSoundID);
			}
		}

		void SoundPlayer::PlayDamageSound()
		{
			if (m_enemy->GetState() == enEnemyDamage && m_enemy->IsDamage() == true) {

				m_soundPlayer->SetSEVolume(m_damageSoundID, DAMAGE_SE_VOLUME);
				m_soundPlayer->PlaySE(m_damageSoundID);
			}
		}

		void SoundPlayer::PlayDeadSound()
		{
			if (m_isPlayDeadSound == false) {
				if (m_enemy->GetDeleteTimer() > m_enemy->GetDeleteTime() * DEAD_SE_PLAYING_TIME_RATE) {

					m_soundPlayer->SetSEVolume(m_deadSoundID, DEAD_SE_VOLUME);
					m_soundPlayer->PlaySE(m_deadSoundID);
					m_isPlayDeadSound = true;
				}
			}
		}
	}
}