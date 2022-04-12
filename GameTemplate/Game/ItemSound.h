#pragma once

namespace mainGame {
	namespace item {
		/// @brief �A�C�e���̉������Ǘ�����N���X
		class Sound
		{
		public:
			Sound();
			~Sound();
			/// @brief ������
			/// @param item �A�C�e���̃A�h���X
			void Init(Item* item);
			/// @brief ���s
			void Execution();

		private:
			/// @brief �o�����̃T�E���h�̏���
			void PlaySpawnSound();
			/// @brief ���莞�̃T�E���h�̏���
			void PlayGetSound();
			/// @brief ����s���̃T�E���h�̏���
			void PlayCantGetSound();
			/// @brief ���ʔ������̃T�E���h�̏���
			void PlayActivateSound();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �o���T�E���h�̍Đ��t���O
			bool m_isSpawnSoundPlay = false;
			/// @brief �o���T�E���h��ID
			int m_spawnSoundID = 0;
			/// @brief ����T�E���h�̍Đ��t���O
			bool m_isGetSoundPlay = false;
			/// @brief ����T�E���h��ID
			int m_getSoundID = 0;
			/// @brief ����s�T�E���h�̍Đ��t���O
			bool m_isCantGetSoundPlay = false;
			/// @brief ����s�T�E���h��ID
			int m_cantGetSoundID = 0;
			/// @brief ����s�̃T�E���h�^�C�}�[
			float m_cantGetSoundPlayTimer = 0.0f;
			/// @brief ���ʔ������T�E���h�̍Đ��t���O
			bool m_isActivateSoundPlay = false;
			/// @brief ���ʔ������T�E���h��ID
			int m_activateSoundID = 0;
			/// @brief �T�E���h�v���C���[
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief �A�C�e��
			Item* m_item = nullptr;
		};
	}
}
