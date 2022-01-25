#pragma once

namespace mainGame {

	namespace enemy {
		/// @brief 敵のサウンドを制御するクラス
		class SoundPlayer
		{
		public:
			SoundPlayer();
			~SoundPlayer();
			/// @brief 初期化
			/// @param enemy エネミーのアドレス
			void Init(Enemy* enemy);
			/// @brief 実行
			void Execution();

		private:
			/// @brief 出現時に鳴るサウンドを制御する関数
			void PlaySpawnSound();

			void PlayAttackSound();
			/// @brief ダメージ時に鳴るサウンドを制御する関数
			void PlayDamageSound();

			void PlayDeadSound();

			/// @brief 初期化フラグ
			bool m_isInitd = false;

			int m_spawnSoundID = 0;

			int m_attackSoundID = 0;

			int m_damageSoundID = 0;

			bool m_isPlayDeadSound = false;

			int m_deadSoundID = 0;

			/// @brief エネミー
			Enemy* m_enemy = nullptr;

			sound::SoundPlayer* m_soundPlayer = nullptr;

		};
	}
}
