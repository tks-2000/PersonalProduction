#pragma once

namespace mainGame {
	namespace ui {

		/// @brief 数字カウント画像の数
		static const int NUM_SPRITE_NUM = 3;

		/// @brief 制限時間の表示を行うクラス
		class TimeLimit
		{
		public:
			TimeLimit();
			~TimeLimit();
			/// @brief 初期化
			void Init();
			/// @brief 実行
			void Execution();
			/// @brief UIを非表示
			void HideUI();
		private:
			/// @brief カウントを進める
			void CountDown();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief カウント中かどうかのフラグ
			bool m_isCountDown = false;
			/// @brief カウント表示の画像
			render::sprite::SpriteRender* m_count[NUM_SPRITE_NUM] = { nullptr };
			/// @brief 開始の画像
			render::sprite::SpriteRender* m_go = nullptr;
			/// @brief 開始画像を表示するタイマー
			float m_goSpriteDisplayTimer = 0.0f;
			/// @brief タイマー表示を行う画像の下地
			render::sprite::SpriteRender* m_timerBaseSprite = nullptr;
			/// @brief タイマー表示を行う画像の枠
			render::sprite::SpriteRender* m_timerBaseFrame = nullptr;
			/// @brief タイム表示のフォント
			render::font::FontRender* m_timeFont = nullptr;
			/// @brief タイムの数値を表示するフォント
			render::font::FontRender* m_timerNumFont = nullptr;
			/// @brief タイマー
			timer::Timer* m_timer = nullptr;
			/// @brief ゲームシーン
			GameScene* m_gameScene = nullptr;
			/// @brief サウンドプレイヤー
			sound::SoundPlayer* m_soundPlayer = nullptr;
			/// @brief カウントサウンドのID
			int m_countSoundID = 0;
			/// @brief 開始サウンドのID
			int m_goSoundID = 0;
			/// @brief カウントサウンドが鳴ったフラグ
			bool m_isPlayCountSE[NUM_SPRITE_NUM] = { false };
		};

	}
}