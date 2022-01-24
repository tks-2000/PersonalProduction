#pragma once

namespace mainGame {

	namespace enemy {
		/// @brief �G�̃T�E���h�𐧌䂷��N���X
		class SoundPlayer
		{
		public:
			SoundPlayer();
			~SoundPlayer();
			/// @brief ������
			/// @param enemy �G�l�~�[�̃A�h���X
			void Init(Enemy* enemy);
			/// @brief ���s
			void Execution();

		private:
			/// @brief �o�����ɖ�T�E���h�𐧌䂷��֐�
			void PlaySpawnSound();

			void PlayAttackSound();
			/// @brief �_���[�W���ɖ�T�E���h�𐧌䂷��֐�
			void PlayDamageSound();

			void PlayDeadSound();

			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �G�l�~�[
			Enemy* m_enemy = nullptr;

		};
	}
}