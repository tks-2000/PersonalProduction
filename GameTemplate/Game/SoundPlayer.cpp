#include "stdafx.h"
#include "SoundPlayer.h"

namespace sound {
	SoundPlayer::SoundPlayer()
	{

	}

	SoundPlayer::~SoundPlayer()
	{

	}

	void SoundPlayer::Init()
	{

	}

	void SoundPlayer::Execution()
	{

	}

	const int SoundPlayer::SetBGM(const wchar_t* filePath)
	{
		//�t�@�C�������ɂ��邩���ׂ�
		int bgmID = SearchFile(m_bgmFilepath, filePath);

		//�t�@�C���ԍ����t�@�C���T�C�Y�Ɠ����Ȃ�΁c
		if (bgmID == m_bgmFilepath.size()) {
			//�V�����o�^����
			m_bgmFilepath.push_back(filePath);
			m_bgm.push_back(NewGO<CSoundSource>(PRIORITY_VERYLOW));
			m_bgm[m_bgm.size() - 1]->Init(m_bgmFilepath[m_bgm.size() - 1]);
			//�V�����o�^�����ԍ���Ԃ�
			return m_bgm.size() - 1;
		}
		//�t�@�C���ԍ����z��̂ǂꂩ�ɊY������Ȃ�c
		else {
			//���ɂ���̂ł��̔ԍ���Ԃ�
			return bgmID;
		}
	}

	const int SoundPlayer::SetSE(const wchar_t* filePath)
	{
		//�t�@�C�������ɂ��邩���ׂ�
		int seID = SearchFile(m_seFilepath, filePath);
		//�t�@�C���ԍ����t�@�C���T�C�Y�Ɠ����Ȃ�΁c
		if (seID == m_seFilepath.size()) {
			//�V�����o�^����
			m_seFilepath.push_back(filePath);
			m_se.push_back(NewGO<CSoundSource>(PRIORITY_VERYLOW));
			m_se[m_se.size() - 1]->Init(m_seFilepath[m_se.size() - 1]);
			//�V�����o�^�����ԍ���Ԃ�
			return m_se.size() - 1;
		}
		//�t�@�C���ԍ����z��̂ǂꂩ�ɊY������Ȃ�c
		else {
			//���ɂ���̂ł��̔ԍ���Ԃ�
			return seID;
		}
	}

	const int SoundPlayer::SetVoice(const wchar_t* filePath)
	{
		//�t�@�C�������ɂ��邩���ׂ�
		int voiceID = SearchFile(m_voiceFilepath, filePath);
		//�t�@�C���ԍ����t�@�C���T�C�Y�Ɠ����Ȃ�΁c
		if (voiceID == m_voiceFilepath.size()) {
			//�V�����o�^����
			m_voiceFilepath.push_back(filePath);
			m_voice.push_back(NewGO<CSoundSource>(PRIORITY_VERYLOW));
			m_voice[m_voice.size() - 1]->Init(m_voiceFilepath[m_voice.size() - 1]);
			//�V�����o�^�����ԍ���Ԃ�
			return m_voice.size() - 1;
		}
		//�t�@�C���ԍ����z��̂ǂꂩ�ɊY������Ȃ�c
		else {
			//���ɂ���̂ł��̔ԍ���Ԃ�
			return voiceID;
		}
	}

	void SoundPlayer::SetBGMVolume(const int bgmID, float volume)
	{
		m_bgm[bgmID]->SetVolume(volume);
	}

	void SoundPlayer::SetSEVolume(const int seID, float volume)
	{
		m_se[seID]->SetVolume(volume);
	}

	void SoundPlayer::SetVoiceVolume(const int voiceID, float volume)
	{
		m_voice[voiceID]->SetVolume(volume);
	}

	void SoundPlayer::PlayBGM(const int bgmID, const bool isLoop)
	{
		if (isLoop == true) {
			m_bgm[bgmID]->Play(isLoop);
		}
		else {
			CSoundSource* bgm = NewGO<CSoundSource>(PRIORITY_VERYLOW);
			bgm->Init(m_bgmFilepath[bgmID]);
			bgm->SetVolume(m_bgm[bgmID]->GetVolume());
			bgm->Play(false);
		}
	}

	void SoundPlayer::PlaySE(const int seID, const bool isLoop)
	{
		if (isLoop == true) {
			m_se[seID]->Play(isLoop);
		}
		else {
			CSoundSource* se = NewGO<CSoundSource>(PRIORITY_VERYLOW);
			se->Init(m_seFilepath[seID]);
			se->SetVolume(m_se[seID]->GetVolume());
			se->Play(false);
		}
	}

	void SoundPlayer::PlayVoice(const int voiceID, const bool isLoop)
	{
		if (isLoop == true) {
			m_voice[voiceID]->Play(isLoop);
		}
		else {
			CSoundSource* voice = NewGO<CSoundSource>(PRIORITY_VERYLOW);
			voice->Init(m_voiceFilepath[voiceID]);
			voice->SetVolume(m_voice[voiceID]->GetVolume());
			voice->Play(false);
		}
	}

	void SoundPlayer::StopBGM(const int bgmID)
	{
		m_bgm[bgmID]->Stop();
	}

	void SoundPlayer::StopSE(const int seID)
	{
		m_se[seID]->Stop();
	}

	void SoundPlayer::StopVoice(const int voiceID)
	{
		m_voice[voiceID]->Stop();
	}

	const int SoundPlayer::SearchFile(std::vector<const wchar_t*>& filePaths, const wchar_t* filePath)
	{
		for (int fileNum = 0; fileNum < filePaths.size(); fileNum++) {
			if (filePaths[fileNum] == filePath) {
				return fileNum;
			}
		}

		return filePaths.size();
	}

}