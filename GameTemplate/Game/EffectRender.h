#pragma once

namespace render {
	namespace effect {
		class EffectRender : public IGameObject
		{
		public:
			EffectRender();
			~EffectRender();

			/// @brief ������
			/// @param filepath �Đ�����G�t�F�N�g�̃t�@�C���p�X
			void Init(const char16_t* filepath);
			/// @brief ���s
			void Execution();
			/// @brief ���W��ݒ�
			/// @param pos �ݒ肷����W
			void SetPosition(const Vector3& pos) { m_position = pos; }
			/// @brief ��]��ݒ�
			/// @param qRot �ݒ肷���]�N�H�[�^�j�I��
			void SetRotation(const Quaternion& qRot) { m_qRot = qRot; }
			/// @brief �g�嗦��ݒ�
			/// @param scale �ݒ肷��g�嗦
			void SetScale(const Vector3& scale) { m_scale = scale; }
			/// @brief �G�t�F�N�g���Đ�
			/// @param isLoop ���[�v�Đ��t���O true�Ń��[�v���� false�ň�񂾂�
			/// @param isLayers �d�˂čĐ�����t���O true�őO�̃G�t�F�N�g���c���Ă��Ă��Đ� false�őO�̃G�t�F�N�g���c���Ă���ƍĐ����Ȃ�
			void Play(const bool isLoop, const bool isLayers = false);
			/// @brief �G�t�F�N�g��A���Đ� �d�˂čĐ��������ꍇ�͂�����
			/// @param playbackInterval �G�t�F�N�g��A���Đ�����Ԋu
			/// @param playbackTime �Đ��������鎞��
			void ContinuousPlay(const float playbackInterval,const float playbackTime);
			/// @brief �G�t�F�N�g���~
			/// @param isEffectDelete �Đ����̃G�t�F�N�g���������H true�ŏ��� false�ŏI���܂ő҂�
			void Stop(const bool isEffectDelete);

		private:
			/// @brief �ʏ�Đ��̏���
			void Playing();
			/// @brief �A���Đ��̏���
			void ContinuousPlaying();

			/// @brief ������
			bool m_isInitd = false;
			/// @brief �����V���b�g�Đ��ׂ̈̍Đ��������ǂ����̃t���O
			bool m_isPlay = true;
			/// @brief ���[�v�Đ��t���O
			bool m_isLoop = false;
			/// @brief �A���Đ��t���O
			bool m_isContinuousPlayback = false;
			/// @brief �Đ��Ԋu
			float m_playbackInterval = 0.0f;
			/// @brief �Đ��Ԋu���v��^�C�}�[
			float m_playbackIntervalTimer = 0.0f;
			/// @brief �Đ��������鎞��
			float m_playbackTime = 0.0f;
			/// @brief �Đ����Ԃ��v��^�C�}�[
			float m_playbackTimer = 0.0f;
			/// @brief �G�t�F�N�g
			Effect m_effect;
			/// @brief ���W
			Vector3 m_position = g_vec3Zero;
			/// @brief ��]
			Quaternion m_qRot = Quaternion::Identity;
			/// @brief �g�嗦
			Vector3 m_scale = g_vec3One;

		};
	}
}
