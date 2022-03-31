#include "stdafx.h"
#include "Timer.h"

namespace mainGame {
	namespace timer {
		/// @brief 開始時のカウント数
		const int START_TIME = 4;
		/// @brief ゲーム中のカウント数
		const int INGAME_TIME = 120;
		/// @brief タイマーフォントの座標
		const Vector2 TIMER_FONT_POS = { 0.0f,300.0f };

		Timer::Timer()
		{
			//未初期化で開始
			m_isInitd = false;
			
		}

		Timer::~Timer()
		{
			
		}

		void Timer::Init()
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//変数を初期化
			m_startTimer = START_TIME;
			m_inGameTimer = INGAME_TIME;
			m_timeNum = m_startTimer + 1.0f;
			m_timeFontPos = TIMER_FONT_POS;
			
			//必要な情報を取得
			m_gameScene = FindGO<GameScene>(GAME_SCENE_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Timer::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//ゲームシーンの状態によって実行する処理を決める
			switch (m_gameScene->GetGameSceneState())
			{
				//ゲーム開始時
			case enGameSceneStart: {
				//開始時のタイマーを進める
				ExecuteStartTimer();
			}break;
				//ゲーム中
			case enGameSceneInProgress: {
				//ゲーム中のタイマーを進める
				ExecuteInGameTimer();
			}break;
			
			default:
				break;
			}

			
		}

		void Timer::ExecuteStartTimer()
		{
			//開始時のタイマーを進める
			m_startTimer -= g_gameTime->GetFrameDeltaTime();

			//フォントにタイマーの数値を伝える
			m_timeNum = m_startTimeNum = m_startTimer + 1.0f;
			

			//タイマーが0以下になったら…
			if (m_startTimer <= 0.0f) {
				//ゲーム中のカウントを進め始める
				m_state = enTimerExecute;
				//ゲームシーンをゲーム中に変更
				m_gameScene->SetGameSceneState(enGameSceneInProgress);
				return;
			}
			
			
		}

		void Timer::ExecuteInGameTimer()
		{
			//ゲーム中のカウントを進める
			m_inGameTimer -= g_gameTime->GetFrameDeltaTime();

			//フォントにタイマーの数値を伝える
			m_timeNum = m_inGameTimer + 1.0f;
			

			//タイマーが0以下になったら…
			if (m_inGameTimer <= 0.0f) {
				//ゲーム終了後のカウントを進め始める
				m_state = enTimerEnd;
				//ゲームシーンをクリア状態に変更
				m_gameScene->SetGameSceneState(enGameSceneClear);
				return;
			}
		}
	}
}