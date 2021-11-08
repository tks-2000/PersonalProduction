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
			DeleteGO(m_timeFont);
		}

		void Timer::Init()
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//タイマーの量を設定
			m_stastTimer = 3.0f;
			m_inGameTimer = 120.0f;

			//タイマー表示のフォントを作成
			m_timeFont = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
			int time = m_stastTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->Init(conversion.c_str());
			m_timeFontPos = { 0.0f,300.0f };
			m_timeFont->SetPosition(m_timeFontPos);

			m_game = FindGO<Game>(GAME_NAME);

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
			switch (m_state)
			{
			case enTimerStart: {
				ExecuteStartTimer();
			}break;
			case enTimerExecute: {
				ExecuteInGameTimer();
			}break;
			case enTimerEnd: {

			}break;
			default:
				break;
			}

			m_timeFont->Execution();
		}

		void Timer::ExecuteStartTimer()
		{
			//開始時のタイマーを進める
			m_stastTimer -= g_gameTime->GetFrameDeltaTime();

			//フォントにタイマーの数値を伝える
			int time = m_stastTimer + 1.0f;
			std::wstring conversion;
			conversion = std::to_wstring(time);
			m_timeFont->SetText(conversion.c_str());

			//タイマーが0以下になったら…
			if (m_stastTimer <= 0.0f) {
				//ゲーム中のカウントを進め始める
				m_state = enTimerExecute;
				
				m_game->SetGameState(enGameInProgress);
				return;
			}
			
			
		}

		void Timer::ExecuteInGameTimer()
		{
			//ゲーム中のカウントを進める
			m_inGameTimer -= g_gameTime->GetFrameDeltaTime();

			//フォントにタイマーの数値を伝える
			int time = m_inGameTimer + 1.0f;
			std::wstring conversion = std::to_wstring(time);
			m_timeFont->SetText(conversion.c_str());

			m_timeFont->SetColor({ 0.5f,0.5f,0.5f,0.5f });

			//タイマーが0以下になったら…
			if (m_inGameTimer <= 0.0f) {
				//ゲーム終了後のカウントを進め始める
				m_state = enTimerEnd;
				m_game->SetGameState(enGameClear);
				return;
			}
		}
	}
}