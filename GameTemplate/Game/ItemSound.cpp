#include "stdafx.h"
#include "ItemSound.h"

namespace mainGame {
	namespace item {
		/// @brief �o��SE�̃t�@�C���p�X
		const wchar_t* SPAWN_SE_FILEPATH = L"Assets/sound/se/GuardEnd.wav";
		/// @brief �o��SE�̑傫��
		const float SPAWN_SE_VOLUME = 0.1f;
		/// @brief ����SE�̃t�@�C���p�X
		const wchar_t* GET_SE_FILEPATH = L"Assets/sound/se/Ranking.wav";
		/// @brief ����SE�̑傫��
		const float GET_SE_VOLUME = 0.1f;
		/// @brief ����s��SE�̃t�@�C���p�X
		const wchar_t* CANTGET_SE_FILEPATH = L"Assets/sound/se/NoDamageCollide.wav";
		/// @brief ����s��SE�̑傫��
		const float CANTGET_SE_VOLUME = 0.1f;
		/// @brief ����s��SE�̍Đ��^�C�}�[�̃��[�v����
		const float CANTGET_SE_PLAY_TIMER_LOOP_TIME = 1.0f;
		/// @brief ����SE�̃t�@�C���p�X
		const wchar_t* ACTIVATE_SE_FILEPATH = L"Assets/sound/se/ItemGet.wav";
		/// @brief ����SE�̑傫��
		const float ACTIVATE_SE_VOLUME = 0.1f;

		Sound::Sound()
		{

		}

		Sound::~Sound()
		{

		}

		void Sound::Init(Item* item)
		{
			//�g�p����������
			m_item = item;
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			//�T�E���h��������
			m_spawnSoundID = m_soundPlayer->SetSE(SPAWN_SE_FILEPATH);
			m_getSoundID = m_soundPlayer->SetSE(GET_SE_FILEPATH);
			m_cantGetSoundID = m_soundPlayer->SetSE(CANTGET_SE_FILEPATH);
			m_activateSoundID = m_soundPlayer->SetSE(ACTIVATE_SE_FILEPATH);

			//����������
			m_isInitd = true;
		}

		void Sound::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�S�ẴT�E���h�̏��������s
			PlaySpawnSound();
			PlayGetSound();
			PlayCantGetSound();
			PlayActivateSound();
		}

		void Sound::PlaySpawnSound()
		{
			//�A�C�e�����o�����Ă��āA�o���T�E���h���Đ�����Ă��Ȃ��ꍇ�c
			if (m_item->IsSpawn() == true && m_isSpawnSoundPlay == false) {
				//�o���T�E���h���Đ�����
				m_soundPlayer->SetSEVolume(m_spawnSoundID, SPAWN_SE_VOLUME);
				m_soundPlayer->PlaySE(m_spawnSoundID);
				m_isSpawnSoundPlay = true;
			}
		}

		void Sound::PlayGetSound()
		{
			//�A�C�e�������肳��Ă��āA����T�E���h���Đ�����Ă��Ȃ��ꍇ�c
			if (m_item->IsPlayerGet() == true && m_isGetSoundPlay == false) {
				//����T�E���h���Đ�����
				m_soundPlayer->SetSEVolume(m_getSoundID, GET_SE_VOLUME);
				m_soundPlayer->PlaySE(m_getSoundID);
				m_isGetSoundPlay = true;
			}
			
		}

		void Sound::PlayCantGetSound()
		{
			//�A�C�e��������s��Ԃ̂Ƃ��c
			if (m_item->IsCantGet() == true) {
				
				//����s�^�C�}�[��0�̂Ƃ��c
				if (m_cantGetSoundPlayTimer == 0.0f) {
					//����s�̃T�E���h���Đ�����
					m_soundPlayer->SetSEVolume(m_cantGetSoundID, CANTGET_SE_VOLUME);
					m_soundPlayer->PlaySE(m_cantGetSoundID);
				}

				//����s�T�E���h�̃^�C�}�[��i�߂�
				m_cantGetSoundPlayTimer += g_gameTime->GetFrameDeltaTime();

				//����s�T�E���h�̃^�C�}�[�����[�v���Ԃ𒴂�����c
				if (m_cantGetSoundPlayTimer > CANTGET_SE_PLAY_TIMER_LOOP_TIME) {
					//����s�T�E���h�̃^�C�}�[��0�ɖ߂�
					m_cantGetSoundPlayTimer = 0.0f;
				}
			}
			//�A�C�e��������s��Ԃł͂Ȃ��Ƃ��c
			else {
				//����s�^�C�}�[��0�ɖ߂�
				m_cantGetSoundPlayTimer = 0.0f;
			}

			
		}

		void Sound::PlayActivateSound()
		{
			//�A�C�e���̌��ʂ��������Ă��āA�������̃T�E���h���Đ�����Ă��Ȃ��ꍇ�c
			if (m_item->IsActivate() == true && m_isActivateSoundPlay == false) {
				//�������̃T�E���h���Đ�
				m_soundPlayer->SetSEVolume(m_activateSoundID, ACTIVATE_SE_VOLUME);
				m_soundPlayer->PlaySE(m_activateSoundID);
				m_isActivateSoundPlay = true;
			}
		}
	}
}