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
			/// @brief 攻撃時に鳴るサウンドを制御する関数
			void PlayAttackSound();
			/// @brief ダメージ時に鳴るサウンドを制御する関数
			void PlayDamageSound();
			/// @brief 死亡時に鳴るサウンドを制御する関数
			void PlayDeadSound();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 出現サウンドのID
			int m_spawnSoundID = 0;
			/// @brief 攻撃サウンドID
			int m_attackSoundID = 0;
			/// @brief ダメージサウンドのID
			int m_damageSoundID = 0;
			/// @brief 死亡サウンドの再生フラグ
			bool m_isPlayDeadSound = false;
			/// @brief 死亡サウンドのID
			int m_deadSoundID = 0;
			/// @brief エネミー
			Enemy* m_enemy = nullptr;
			/// @brief 
			sound::SoundPlayer* m_soundPlayer = nullptr;

		};
	}
}
