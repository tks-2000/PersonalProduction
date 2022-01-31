#include "stdafx.h"
#include "Timer.h"

namespace mainGame {
	namespace timer {
		/// @brief 開始時のカウント数
		const int START_TIME = 4;
		/// @brief ゲーム中のカウント数
		const int INGAME_TIME = 120;


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

			//タイマーの量を設定
			m_stastTimer = START_TIME;
			m_inGameTimer = INGAME_TIME;

			//タイマー表示のフォントを作成
			
			m_timeNum = m_stastTimer + 1.0f;
			
			m_timeFontPos = { 0.0f,300.0f };
			

			
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

			//状態によって実行する処理を決める
			switch (m_gameScene->GetGameSceneState())
			{
			case enGameSceneStart: {
				ExecuteStartTimer();
			}break;
			case enGameSceneInProgress: {
				ExecuteInGameTimer();
			}break;
			
			default:
				break;
			}

			
		}

		void Timer::ExecuteStartTimer()
		{
			//開始時のタイマーを進める
			m_stastTimer -= g_gameTime->GetFrameDeltaTime();

			//フォントにタイマーの数値を伝える
			m_timeNum = m_stastTimer + 1.0f;
			

			//タイマーが0以下になったら…
			if (m_stastTimer <= 0.0f) {
				//ゲーム中のカウントを進め始める
				m_state = enTimerExecute;
				
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
				m_gameScene->SetGameSceneState(enGameSceneClear);
				return;
			}
		}
	}
}