#pragma once

class SkinModelRender;
class SpriteRender;
class Effect;
class CSoundSource;


namespace nsAI {
	class NaviMesh;
	class Path;
	class PathFinding;
}

namespace sound {
	class SoundPlayer;
}

namespace mainGame {
	namespace title {
		class Title;
	}
	namespace player {
		class Player;
	}
	namespace defensiveTarget {
		class DefensiveTarget;
	}
	namespace enemy {
		class Generator;
		class Enemy;
	}
	namespace stage {
		class Stage;
	}
	namespace timer {
		class Timer;
	}
	namespace map {
		class MiniMap;
	}
	namespace item {
		class ItemGenerator;
	}
	namespace ui {
		class GameUI;
	}
	
	class GameScene;

	class GameCamera;

	/// @brief ゲームの状態を表す列挙型
	enum EnGameState {
		/// @brief タイトル画面
		enTitleScene,
		/// @brief ゲーム進行中
		enGameInProgress,
		/// @brief ゲームの状態を表すステートの数
		enGameStateNum
	};

	/// @brief ゲーム中の流れを制御するクラス
	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		/// @brief 初期化
		void Init();

		bool Start();
		void Update();

		void TitleSceneStart();

		void DeleteTitleScene(); 

		void GameSceneStart();

		void DeleteGameScene();

		/// @brief ゲームの状態を変更
		/// @param state ゲームの状態を表すステート
		void SetGameState(const EnGameState& state) { m_state = state; }

		/// @brief ゲームの状態を取得
		/// @return ゲームの状態を表すステート
		const EnGameState& GetGameState() { return m_state; }

		

	private:
		

		/// @brief 初期化フラグ
		bool m_isInitd = false;

		EnGameState m_state = enGameStateNum;

		title::Title* m_title = nullptr;

		GameScene* m_gameScene = nullptr;

		sound::SoundPlayer* m_soundPlayer = nullptr;

		render::RenderingEngine* m_renderingEngine = nullptr;
	};

}