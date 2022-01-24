#include "stdafx.h"
#include "EnemySound.h"

namespace mainGame {
	namespace enemy {

		const wchar_t* SPAWN_SE_FILEPATH = L"Assets/sound/se/BoxOpen.wav";

		const float SPAWN_SE_VOLUME = 0.1f;

		const wchar_t* ATTACK_SE_FILEPATH = L"Assets/sound/se/Ranking.wav";

		const float ATTACK_SE_VOLUME = 0.1f;

		const wchar_t* DAMAGE_SE_FILEPATH = L"Assets/sound/se/StrongCollide.wav";

		const float DAMAGE_SE_VOLUME = 0.1f;

		const wchar_t* DEAD_SE_FILEPATH = L"Assets/sound/se/Stan.wav";

		const float DEAD_SE_VOLUME = 0.1f;

		const float DEAD_SE_PLAYING_TIME_RATE = 0.9;
		
		SoundPlayer::SoundPlayer()
		{

		}

		SoundPlayer::~SoundPlayer()
		{

		}

		void SoundPlayer::Init(Enemy* enemy)
		{
			m_enemy = enemy;

			m_isInitd = true;

			PlaySpawnSound();
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
			CSoundSource* spawnSound = NewGO<CSoundSource>(PRIORITY_VERYLOW);
			spawnSound->Init(SPAWN_SE_FILEPATH);
			spawnSound->SetVolume(SPAWN_SE_VOLUME);
			spawnSound->Play(false);
		}

		void SoundPlayer::PlayAttackSound()
		{
			if (m_enemy->IsAttack() == true) {
				CSoundSource* AttackSound = NewGO<CSoundSource>(PRIORITY_VERYLOW);
				AttackSound->Init(ATTACK_SE_FILEPATH);
				AttackSound->SetVolume(ATTACK_SE_VOLUME);
				AttackSound->Play(false);
			}
		}

		void SoundPlayer::PlayDamageSound()
		{
			if (m_enemy->IsDamage() == true){
				CSoundSource* damageSound = NewGO<CSoundSource>(PRIORITY_VERYLOW);
					damageSound->Init(DAMAGE_SE_FILEPATH);
					damageSound->SetVolume(DAMAGE_SE_VOLUME);
					damageSound->Play(false);
					
			}
		}

		void SoundPlayer::PlayDeadSound()
		{
			if (m_enemy->GetDeleteTimer() > m_enemy->GetDeleteTime() * DEAD_SE_PLAYING_TIME_RATE) {
				CSoundSource* deadSound = NewGO<CSoundSource>(PRIORITY_VERYLOW);
				deadSound->Init(DEAD_SE_FILEPATH);
				deadSound->SetVolume(DEAD_SE_VOLUME);
				deadSound->Play(false);
			}
		}
	}
}