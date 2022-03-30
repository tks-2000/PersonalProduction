#include "stdafx.h"
#include "PlayerSound.h"

namespace mainGame {
	namespace player {
		/// @brief ���s�T�E���h�̃t�@�C���p�X
		const wchar_t* WALK_SE_FILEPATH = L"Assets/sound/se/ArmorWalk.wav";
		/// @brief ���s�T�E���h�̑傫��
		const float WALK_SE_VOLUME = 0.1f;
		/// @brief ���s�T�E���h�̍Đ��Ԋu
		const float WALK_SE_INTERVAL = 0.6f;
		/// @brief ���s�T�E���h�̃t�@�C���p�X
		const wchar_t* RUN_SE_FILEPATH = L"Assets/sound/se/ArmorWalk.wav";
		/// @brief ���s�T�E���h�̑傫��
		const float RUN_SE_VOLUME = 0.2f;
		/// @brief ���s�T�E���h�̍Đ��Ԋu
		const float RUN_SE_INTERVAL = 0.3f;
		/// @brief �U���T�E���h�̃t�@�C���p�X
		const wchar_t* ATTACK_SE_FILEPATH = L"Assets/sound/se/PlayerAttack.wav";
		/// @brief �U���T�E���h�̑傫��
		const float ATTACK_SE_VOLUME = 0.1f;
		/// @brief �U���T�E���h�̍Đ��J�n����
		const float ATTACK_SE_PLAY_TIME = 0.4f;
		/// @brief �_���[�W�T�E���h�̃t�@�C���p�X
		const wchar_t* DAMAGE_SE_FILEPATH = L"Assets/sound/se/WeakCollide.wav";
		/// @brief �_���[�W�T�E���h�̑傫��
		const float DAMAGE_SE_VOLUME = 0.1f;
		/// @brief �G�����T�E���h�̃t�@�C���p�X
		const wchar_t* KNEE_SE_FILEPATH = L"Assets/sound/se/Knee.wav";
		/// @brief �G�����T�E���h�̑傫��
		const float KNEE_SE_VOLUME = 1.0f;
		/// @brief �G�����T�E���h�̍Đ��J�n����
		const float KNEE_SE_PLAY_TIME = 1.0f;
		/// @brief �|���T�E���h�̃t�@�C���p�X
		const wchar_t* DOWN_SE_FILEPATH = L"Assets/sound/se/Down.wav";
		/// @brief �|���T�E���h�̑傫��
		const float DOWN_SE_VOLUME = 0.5f;
		/// @brief �|���T�E���h�̍Đ��J�n����
		const float DOWN_SE_PLAY_TIME = 2.0f;

		Sound::Sound()
		{

		}

		Sound::~Sound()
		{

		}

		void Sound::Init(Player* player)
		{
			//�g�p��������擾
			m_player = player;
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);

			//������������
			m_walkSoundID = m_soundPlayer->SetSE(WALK_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_walkSoundID, WALK_SE_VOLUME);
			m_runSoundID = m_soundPlayer->SetSE(RUN_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_runSoundID, RUN_SE_VOLUME);
			m_attackSoundID = m_soundPlayer->SetSE(ATTACK_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_attackSoundID, ATTACK_SE_VOLUME);
			m_damageSoundID = m_soundPlayer->SetSE(DAMAGE_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_damageSoundID, DAMAGE_SE_VOLUME);
			m_kneeSoundID = m_soundPlayer->SetSE(KNEE_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_kneeSoundID, KNEE_SE_VOLUME);
			m_downSoundID = m_soundPlayer->SetSE(DOWN_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_downSoundID, DOWN_SE_VOLUME);

			//����������
			m_isInitd = true;
		}

		void Sound::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�e��T�E���h���Đ�
			PlayWalkSound();
			PlayRunSound();
			PlayAttackSound();
			PlayDamageSound();
			PlayDownSound();
		}

		void Sound::PlayWalkSound()
		{
			//�v���C���[�����s���Ȃ�c
			if (m_player->GetPlayerStatus() == enPlayerWark) {
				//�^�C�}�[��i�߂�
				m_walkSoundTimer += g_gameTime->GetFrameDeltaTime();
				//�^�C�}�[���Đ��Ԋu�𒴂�����c
				if (m_walkSoundTimer > WALK_SE_INTERVAL) {
					//�T�E���h���Đ�
					m_soundPlayer->PlaySE(m_walkSoundID);
					//�^�C�}�[��0�ɂ���
					m_walkSoundTimer = 0.0f;
				}
			}
			//�����łȂ��Ȃ�c
			else {
				//�^�C�}�[��0�ɂ���
				m_walkSoundTimer = 0.0f;
			}
		}

		void Sound::PlayRunSound()
		{
			//�v���C���[�����s���Ȃ�c
			if (m_player->GetPlayerStatus() == enPlayerRun) {
				//�^�C�}�[��i�߂�
				m_runSoundTimer += g_gameTime->GetFrameDeltaTime();
				//�^�C�}�[���Đ��Ԋu�𒴂�����c
				if (m_runSoundTimer > RUN_SE_INTERVAL) {
					//�T�E���h���Đ�
					m_soundPlayer->PlaySE(m_runSoundID);
					//�^�C�}�[��0�ɂ���
					m_runSoundTimer = 0.0f;
				}
			}
			//�����łȂ��Ȃ�c
			else {
				//�^�C�}�[��0�ɂ���
				m_runSoundTimer = 0.0f;
			}
		}

		void Sound::PlayAttackSound()
		{
			//�v���C���[���U�����Ȃ�c
			if (m_player->GetPlayerStatus() == enPlayerAttack) {
				//�^�C�}�[��i�߂�
				m_attackSoundPlayTimer += g_gameTime->GetFrameDeltaTime();
				//�^�C�}�[���Đ����Ԃ𒴂��čĐ��t���O�������Ă��Ȃ��Ȃ�c
				if (m_attackSoundPlayTimer > ATTACK_SE_PLAY_TIME && m_isAttackSoundPlay == false) {
					//�T�E���h���Đ�
					m_soundPlayer->PlaySE(m_attackSoundID);
					m_attackSoundPlayTimer = 0.0f;
					//�Đ��t���O�𗧂Ă�
					m_isAttackSoundPlay = true;
				}
			}
			//�����łȂ��Ȃ�c
			else {
				//�^�C�}�[�ƍĐ��t���O��߂�
				m_attackSoundPlayTimer = 0.0f;
				m_isAttackSoundPlay = false;
			}
		}

		void Sound::PlayDamageSound()
		{
			//�v���C���[���_���[�W���̏ꍇ�c
			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				//�Đ��t���O�������Ă��Ȃ��ꍇ�c
				if (m_isDamageSoundPlay == false) {
					//�T�E���h���Đ�
					m_soundPlayer->PlaySE(m_damageSoundID);
					//�Đ��t���O�𗧂Ă�
					m_isDamageSoundPlay = true;
				}
			}
			//�����łȂ��ꍇ�c
			else {
				//�Đ��t���O���~�낷
				m_isDamageSoundPlay = false;
			}
		}

		void Sound::PlayDownSound()
		{
			//�v���C���[���_�E����Ԃ̏ꍇ
			if (m_player->GetPlayerAnimation() == enPlayerAnimationKneelDown) {
				//�^�C�}�[��i�߂�
				m_kneeSoundTimer += g_gameTime->GetFrameDeltaTime();
				m_downSoundTimer += g_gameTime->GetFrameDeltaTime();

				//�^�C�}�[���Đ����Ԃ��߂��čĐ��t���O�������Ă��Ȃ��ꍇ�c
				if (m_kneeSoundTimer > KNEE_SE_PLAY_TIME && m_isKneeSoundPlay == false) {
					//�T�E���h���Đ�����
					m_soundPlayer->PlaySE(m_kneeSoundID);
					//�Đ��t���O�𗧂Ă�
					m_isKneeSoundPlay = true;
				}

				//�^�C�}�[���Đ����Ԃ��߂��čĐ��t���O�������Ă��Ȃ��ꍇ�c
				if (m_downSoundTimer > DOWN_SE_PLAY_TIME && m_isDownSoundPlay == false) {
					//�T�E���h���Đ�����
					m_soundPlayer->PlaySE(m_downSoundID);
					//�Đ��t���O�𗧂Ă�
					m_isDownSoundPlay = true;
				}
			}
			//�����łȂ��ꍇ�c
			else {
				//�Đ��t���O�ƃ^�C�}�[��߂�
				m_isKneeSoundPlay = false;
				m_isDownSoundPlay = false;
				m_kneeSoundTimer = 0.0f;
				m_downSoundTimer = 0.0f;
			}
		}
	}
}