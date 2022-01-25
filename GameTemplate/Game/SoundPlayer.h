#pragma once
namespace sound {

	/// @brief �Đ����鉹�����Ǘ�����N���X
	class SoundPlayer : public IGameObject
	{
	public:
		SoundPlayer();
		~SoundPlayer();
		void Init();
		void Execution();

		/// @brief BGM��ݒ�
		/// @param filePath �ݒ肷��t�@�C���p�X
		/// @return �ݒ肵��BGM���w�肷��ID�ԍ�
		const int SetBGM(const wchar_t* filePath);
		/// @brief SE��ݒ�
		/// @param filePath �ݒ肷��t�@�C���p�X 
		/// @return �ݒ肵��SE���w�肷��ID�ԍ�
		const int SetSE(const wchar_t* filePath);
		/// @brief ������ݒ�
		/// @param filePath �ݒ肷��t�@�C���p�X
		/// @return �ݒ肵���������w�肷��ID�ԍ�
		const int SetVoice(const wchar_t* filePath);

		void SetBGMVolume(const int bgmID, float volume);
		void SetSEVolume(const int seID, float volume);
		void SetVoiceVolume(const int voiceID, float volume);

		/// @brief BGM���Đ�
		/// @param bgmID �Đ�����BGM��ID�ԍ�
		/// @param isLoop ���[�v�t���O
		void PlayBGM(const int bgmID,const bool isLoop = false);
		/// @brief SE���Đ�
		/// @param seID �Đ�����SE��ID�ԍ�
		/// @param isLoop ���[�v�t���O
		void PlaySE(const int seID,const bool isLoop = false);
		/// @brief �������Đ�
		/// @param VoiceID �Đ����鉹����ID�ԍ�
		/// @param isLoop ���[�v�t���O
		void PlayVoice(const int VoiceID,const bool isLoop = false);

		void StopBGM(const int bgmID);

		void StopSE(const int seID);

		void StopVoice(const int voiceID);

	private:
		/// @brief �t�@�C���p�X�����ɓ����Ă��邩���ׂ�
		/// @param filePaths ���ׂ�t�@�C���p�X�̔z��
		/// @param filePath �z��ɂ��邩���ׂ�t�@�C���p�X
		/// @return ���g������΂��̃t�@�C���̔z���ID ���g��������Δz��̑傫����Ԃ�
		const int SearchFile(std::vector<const wchar_t*>& filePaths, const wchar_t* filePath);
		/// @brief ���y�̃t�@�C���p�X
		std::vector<const wchar_t*> m_bgmFilepath;
		/// @brief ���y
		std::vector<CSoundSource*> m_bgm;
		/// @brief ���ʉ��̃t�@�C���p�X
		std::vector<const wchar_t*> m_seFilepath;
		/// @brief ���ʉ�
		std::vector<CSoundSource*> m_se;
		/// @brief ���̃t�@�C���p�X
		std::vector<const wchar_t*> m_voiceFilepath;
		/// @brief ��
		std::vector<CSoundSource*> m_voice;

	};
}
