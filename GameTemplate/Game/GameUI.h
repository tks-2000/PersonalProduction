#pragma once
#include "OwnedItem.h"
#include "BaseEndurance.h"
#include "TimeLimit.h"
#include "RemainingBullets.h"

namespace mainGame {

	class Game;

	namespace timer {
		class Timer;
	}

	namespace ui {
		/// @brief ゲーム中のUIを制御するクラス
		class GameUI : public IGameObject
		{
		public:
			GameUI();
			~GameUI();
			/// @brief 初期化
			void Init();
			/// @brief 実行
			void Execution();
			/// @brief スタート時のフォントを表示する
			void DisplayStartFont();
			/// @brief ゲーム終了時の画像を表示する
			void DisplayGameEndSprite();
			
		private:
			/// @brief スタート時のフォント表示を実行
			void StartFontExecution();
			/// @brief ゲーム終了時の画像表示を実行
			void GameEndSpriteExecution();
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief スタート時のフォント表示フラグ
			bool m_startFontFlag = false;
			/// @brief スタート時のフォント
			render::font::FontRender* m_startFont = nullptr;
			/// @brief スタート時のフォントが消えるまでのタイマー
			float m_startFontDisplayTimer = 0.0f;
			/// @brief ゲーム終了時の画像表示フラグ
			bool m_gameEndSpriteFlag = false;
			/// @brief ゲーム終了時の画像
			render::sprite::SpriteRender* m_gameEndSprite = nullptr;

			/// @brief 所有アイテム
			OwnedItem m_oenedItem;
			/// @brief 拠点の耐久力
			BaseEndurance m_baseEndurance;
			/// @brief 制限時間
			TimeLimit m_timeLimit;
			/// @brief 残弾
			RemainingBullets m_remainingBullets;

			/// @brief ゲーム
			Game* m_game = nullptr;
			/// @brief タイマー
			timer::Timer* m_timer = nullptr;
		};
	}
}
