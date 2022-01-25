#include "stdafx.h"
#include "PlayerSound.h"

namespace mainGame {
	namespace player {

		const wchar_t* WALK_SE_FILEPATH = L"Assets/sound/se/ArmorWalk.wav";

		const float WALK_SE_VOLUME = 0.1f;

		const float WALK_SE_INTERVAL = 0.6f;

		const wchar_t* RUN_SE_FILEPATH = L"Assets/sound/se/ArmorWalk.wav";

		const float RUN_SE_VOLUME = 0.2f;

		const float RUN_SE_INTERVAL = 0.3f;

		const wchar_t* ATTACK_SE_FILEPATH = L"Assets/sound/se/PlayerAttack.wav";

		const float ATTACK_SE_VOLUME = 0.1f;

		const float ATTACK_SE_PLAY_TIME = 0.4f;

		const wchar_t* DAMAGE_SE_FILEPATH = L"Assets/sound/se/WeakCollide.wav";

		const float DAMAGE_SE_VOLUME = 0.1f;

		const wchar_t* KNEE_SE_FILEPATH = L"Assets/sound/se/Knee.wav";

		const float KNEE_SE_VOLUME = 1.0f;

		const float KNEE_SE_PLAY_TIME = 1.0f;

		const wchar_t* DOWN_SE_FILEPATH = L"Assets/sound/se/Down.wav";

		const float DOWN_SE_VOLUME = 0.5f;

		const float DOWN_SE_PLAY_TIME = 2.0f;

		Sound::Sound()
		{

		}

		Sound::~Sound()
		{

		}

		void Sound::Init(Player* player)
		{
			m_player = player;
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_walkSoundID = m_soundPlayer->SetSE(WALK_SE_FILEPATH);
			m_runSoundID = m_soundPlayer->SetSE(RUN_SE_FILEPATH);
			m_attackSoundID = m_soundPlayer->SetSE(ATTACK_SE_FILEPATH);
			m_damageSoundID = m_soundPlayer->SetSE(DAMAGE_SE_FILEPATH);
			m_kneeSoundID = m_soundPlayer->SetSE(KNEE_SE_FILEPATH);
			m_downSoundID = m_soundPlayer->SetSE(DOWN_SE_FILEPATH);
			m_isInitd = true;
		}

		void Sound::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			PlayWalkSound();
			PlayRunSound();
			PlayAttackSound();
			PlayDamageSound();
			PlayDownSound();
		}

		void Sound::PlayWalkSound()
		{
			if (m_player->GetPlayerStatus() == enPlayerWark) {
				m_walkSoundTimer += g_gameTime->GetFrameDeltaTime();
				if (m_walkSoundTimer > WALK_SE_INTERVAL) {
					m_soundPlayer->SetSEVolume(m_walkSoundID, WALK_SE_VOLUME);
					m_soundPlayer->PlaySE(m_walkSoundID);
					m_walkSoundTimer = 0.0f;
				}
			}
			else {
				m_walkSoundTimer = 0.0f;
			}
		}

		void Sound::PlayRunSound()
		{
			if (m_player->GetPlayerStatus() == enPlayerRun) {
				m_runSoundTimer += g_gameTime->GetFrameDeltaTime();
				if (m_runSoundTimer > RUN_SE_INTERVAL) {
					m_soundPlayer->SetSEVolume(m_runSoundID, RUN_SE_VOLUME);
					m_soundPlayer->PlaySE(m_runSoundID);
					m_runSoundTimer = 0.0f;
				}
			}
			else {
				m_runSoundTimer = 0.0f;
			}
		}

		void Sound::PlayAttackSound()
		{
			if (m_player->GetPlayerStatus() == enPlayerAttack) {
				m_attackSoundPlayTimer += g_gameTime->GetFrameDeltaTime();

				if (m_attackSoundPlayTimer > ATTACK_SE_PLAY_TIME && m_isAttackSoundPlay == false) {
					m_soundPlayer->SetSEVolume(m_attackSoundID, ATTACK_SE_VOLUME);
					m_soundPlayer->PlaySE(m_attackSoundID);
					m_attackSoundPlayTimer = 0.0f;
					m_isAttackSoundPlay = true;
				}
			}
			else {
				m_attackSoundPlayTimer = 0.0f;
				m_isAttackSoundPlay = false;
			}
		}

		void Sound::PlayDamageSound()
		{
			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				if (m_isDamageSoundPlay == false) {
					m_soundPlayer->SetSEVolume(m_damageSoundID, DAMAGE_SE_VOLUME);
					m_soundPlayer->PlaySE(m_damageSoundID);
					m_isDamageSoundPlay = true;
				}
			}
			else {
				m_isDamageSoundPlay = false;
			}
		}

		void Sound::PlayDownSound()
		{
			if (m_player->GetPlayerAnimation() == enPlayerAnimationKneelDown) {
				m_kneeSoundTimer += g_gameTime->GetFrameDeltaTime();
				m_downSoundTimer += g_gameTime->GetFrameDeltaTime();

				if (m_kneeSoundTimer > KNEE_SE_PLAY_TIME && m_isKneeSoundPlay == false) {
					m_soundPlayer->SetSEVolume(m_kneeSoundID, KNEE_SE_VOLUME);
					m_soundPlayer->PlaySE(m_kneeSoundID);
					m_isKneeSoundPlay = true;
				}

				if (m_downSoundTimer > DOWN_SE_PLAY_TIME && m_isDownSoundPlay == false) {
					m_soundPlayer->SetSEVolume(m_downSoundID, DOWN_SE_VOLUME);
					m_soundPlayer->PlaySE(m_downSoundID);
					m_isDownSoundPlay = true;
				}
			}
			else {
				m_isKneeSoundPlay = false;
				m_isDownSoundPlay = false;
				m_downSoundTimer = 0.0f;
			}
		}
	}
}