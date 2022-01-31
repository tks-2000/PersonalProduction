#pragma once

namespace mainGame {

	class GameScene;

	namespace timer {

		/// @brief タイマーが何をしているか表す列挙型
		enum EnTimerState {
			/// @brief ゲーム開始のカウント中
			enTimerStart,
			/// @brief ゲーム中のカウント中
			enTimerExecute,
			/// @brief ゲーム終了後のカウント中
			enTimerEnd,
			/// @brief タイマーの状態の合計数
			enTimerStateNum
		};

		class Timer : public IGameObject
		{
		public:
			Timer();
			~Timer();

			/// @brief 初期化
			void Init();
			/// @brief 実行
			void Execution();
			/// @brief タイマーの状態を取得
			/// @return タイマーが何を行っているかのステート
			const EnTimerState& GetTimerState() { return m_state; }

			const int GetTimer() const { return m_timeNum; }

			const int GetStartTimer() const { return m_startTimeNum; }

		private:
			/// @brief 開始時のタイマーを進める
			void ExecuteStartTimer();
			/// @brief ゲーム中のタイマーを進める
			void ExecuteInGameTimer();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 開始時のタイマー
			float m_startTimer = 0.0f;
			/// @brief ゲーム中のタイマー
			float m_inGameTimer = 0.0f;

			int m_startTimeNum = 0;
			/// @brief フォントに設定する数値
			int m_timeNum = 0;
			/// @brief フォントの状態を表すステート
			EnTimerState m_state = enTimerStart;
			
			/// @brief タイマーの表示位置
			Vector2 m_timeFontPos = g_vec2Zero;


			GameScene* m_gameScene = nullptr;
		};
	}
}
