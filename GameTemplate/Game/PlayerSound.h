#pragma once

namespace mainGame {
	namespace player {
		/// @brief プレイヤーの音声を管理するクラス
		class Sound
		{
		public:
			Sound();
			~Sound();
			/// @brief 
			/// @param player 
			void Init(Player* player);
			/// @brief 
			void Execution();

		private:
			/// @brief 歩行サウンドを再生
			void PlayWalkSound();
			/// @brief 走行サウンドを再生
			void PlayRunSound();
			/// @brief 攻撃サウンドを再生
			void PlayAttackSound();
			/// @brief ダメージサウンドを再生
			void PlayDamageSound();
			/// @brief ダウンサウンドを再生
			void PlayDownSound();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 歩行サウンドのタイマー
			float m_walkSoundTimer = 0.0f;
			/// @brief 歩行サウンドのID
			int m_walkSoundID = 0;
			/// @brief 走行サウンドのタイマー
			float m_runSoundTimer = 0.0f;
			/// @brief 走行サウンドのID
			int m_runSoundID = 0;
			/// @brief 攻撃サウンドの再生フラグ
			bool m_isAttackSoundPlay = false;
			/// @brief 攻撃サウンドのタイマー
			float m_attackSoundPlayTimer = 0.0f;
			/// @brief 攻撃サウンドのID
			int m_attackSoundID = 0;
			/// @brief ダメージサウンドの再生フラグ
			bool m_isDamageSoundPlay = false;
			/// @brief ダメージサウンドのID
			int m_damageSoundID = 0;
			/// @brief 膝をつくサウンドの再生フラグ
			bool m_isKneeSoundPlay = false;
			/// @brief 膝をつくサウンドのID
			int m_kneeSoundID = 0;
			/// @brief 膝をつくサウンドのタイマー
			float m_kneeSoundTimer = 0.0f;
			/// @brief 倒れるサウンドの再生フラグ
			bool m_isDownSoundPlay = false;
			/// @brief 倒れるサウンドのID
			int m_downSoundID = 0;
			/// @brief 倒れるサウンドのタイマー
			float m_downSoundTimer = 0.0f;

			
			/// @brief サウンドプレイヤー
			sound::SoundPlayer* m_soundPlayer;
			/// @brief プレイヤー
			Player* m_player = nullptr;
		};
	}
}
