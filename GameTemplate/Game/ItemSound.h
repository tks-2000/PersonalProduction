#pragma once

namespace mainGame {
	namespace item {
		/// @brief アイテムの音声を管理するクラス
		class Sound
		{
		public:
			Sound();
			~Sound();
			/// @brief 初期化
			/// @param item アイテムのアドレス
			void Init(Item* item);
			/// @brief 実行
			void Execution();

		private:
			/// @brief 出現時のサウンドの処理
			void PlaySpawnSound();
			/// @brief 入手時のサウンドの処理
			void PlayGetSound();
			/// @brief 入手不可時のサウンドの処理
			void PlayCantGetSound();
			/// @brief 効果発動時のサウンドの処理
			void PlayActivateSound();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 出現サウンドの再生フラグ
			bool m_isSpawnSoundPlay = false;
			/// @brief 出現サウンドのID
			int m_spawnSoundID = 0;
			/// @brief 入手サウンドの再生フラグ
			bool m_isGetSoundPlay = false;
			/// @brief 入手サウンドのID
			int m_getSoundID = 0;
			/// @brief 入手不可サウンドの再生フラグ
			bool m_isCantGetSoundPlay = false;
			/// @brief 入手不可サウンドのID
			int m_cantGetSoundID = 0;
			/// @brief 入手不可のサウンドタイマー
			float m_cantGetSoundPlayTimer = 0.0f;
			/// @brief 効果発動時サウンドの再生フラグ
			bool m_isActivateSoundPlay = false;
			/// @brief 効果発動時サウンドのID
			int m_activateSoundID = 0;
			/// @brief サウンドプレイヤー
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief アイテム
			Item* m_item = nullptr;
		};
	}
}
