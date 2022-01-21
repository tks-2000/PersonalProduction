#include "stdafx.h"
#include "EffectRender.h"

namespace render {
	namespace effect {
		EffectRender::EffectRender()
		{

		}

		EffectRender::~EffectRender()
		{

		}

		void EffectRender::Init(const char16_t* filepath)
		{
			//�Đ�����G�t�F�N�g��������
			m_effect.Init(filepath);
			m_isInitd = true;
		}

		void EffectRender::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//���W�E��]�E�g�嗦��ݒ�
			m_effect.SetPosition(m_position);
			m_effect.SetRotation(m_qRot);
			m_effect.SetScale(m_scale);
			m_effect.Update();

			//�A���Đ��t���O�������Ă�����c
			if (m_isContinuousPlayback == true) {
				//�A���Đ��̏������s��
				ContinuousPlaying();
			}
			//�A���Đ��t���O�������Ă��Ȃ���΁c
			else {
				//�ʏ�Đ��̏������s��
				Playing();
			}
		}

		void EffectRender::Play(const bool isLoop, const bool isLayers)
		{
			//���ɍĐ����Ȃ���s���Ȃ�
			if (m_effect.IsPlay() == true && isLayers == false) {
				return;
			}
			//�Đ��t���O��ݒ�
			m_isLoop = isLoop;
			m_isPlay = false;
		}

		void EffectRender::ContinuousPlay(const float playbackInterval, const float playbackTime)
		{
			//���ɘA���Đ����Ȃ���s���Ȃ�
			if (m_isContinuousPlayback == true) {
				return;
			}
			//�Đ��Ԋu�ƍĐ����Ԃ�ݒ�
			m_isContinuousPlayback = true;
			m_playbackInterval = playbackInterval;
			m_playbackIntervalTimer = 0.0f;
			m_playbackTime = playbackTime;
			m_playbackTimer = 0.0f;
			//�G�t�F�N�g���Đ��J�n
			m_effect.Play(false);
		}

		void EffectRender::Stop(const bool isEffectDelete)
		{
			//�Đ��t���O���~
			m_isLoop = false;
			m_isPlay = true;
			m_isContinuousPlayback = false;

			//�G�t�F�N�g�폜�t���O�������Ă�����c
			if (isEffectDelete == true) {
				//�Đ����̃G�t�F�N�g���~
				m_effect.Stop();
			}
		}

		void EffectRender::Playing()
		{
			

			//���[�v�Đ��t���O�������Ă�����c
			if (m_isLoop == true) {

				//���ɍĐ����Ȃ���s���Ȃ�
				if (m_effect.IsPlay() == true) {
					return;
				}

				//�Đ�
				m_effect.Play(true);

			}
			//���[�v�Đ��t���O�������Ă��Ȃ�������c
			else {
				//�܂��Đ����Ă��Ȃ��ꍇ�c
				if (m_isPlay == false) {
					//�G�t�F�N�g���Đ�
					m_effect.Play(false);
					//�G�t�F�N�g���Đ����ꂽ�t���O�𗧂Ă�
					m_isPlay = true;
				}
			}
		}

		void EffectRender::ContinuousPlaying()
		{
			//�Đ����ԂƍĐ��Ԋu���v��^�C�}�[��i�߂�
			m_playbackIntervalTimer += g_gameTime->GetFrameDeltaTime();
			m_playbackTimer += g_gameTime->GetFrameDeltaTime();

			//�Đ��Ԋu�̃^�C�}�[���Đ����ԂɒB�����Ƃ��c
			if (m_playbackIntervalTimer > m_playbackInterval) {
				//�G�t�F�N�g���Đ�
				m_effect.Play(false);
				//�Đ��Ԋu�̃^�C�}�[�����ɖ߂�
				m_playbackIntervalTimer = 0.0f;
			}

			//�Đ����Ԃ̃^�C�}�[���I�����ԂɒB�����Ƃ��c
			if (m_playbackTimer > m_playbackTime) {
				//�A���Đ����I��
				m_isContinuousPlayback = false;
			}
		}
	}
}