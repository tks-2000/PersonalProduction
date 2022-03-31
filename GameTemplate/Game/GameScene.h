#pragma once

class CSoundSource;


namespace mainGame {

	class Game;

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

	/// @brief ゲームシーンの状態を表すステート
	enum EnGameSceneState {
		/// @brief ゲーム開始直後のカウント中
		enGameSceneStart,
		/// @brief ゲームをプレイ中
		enGameSceneInProgress,
		/// @brief ゲームクリア
		enGameSceneClear,
		/// @brief ゲームオーバー
		enGameSceneOver,
		/// @brief ゲームシーンのステートの数
		enGameSceneNum
	};

	/// @brief ゲームシーンで出現する物を管理するクラス
	class GameScene : public IGameObject
	{

	public:
		GameScene();
		~GameScene();
		/// @brief 初期化
		void Init();

		/// @brief 実行
		void Execution();

		/// @brief ゲームシーンのステートを取得
		/// @return ゲームシーンのステートのconst参照
		const EnGameSceneState& GetGameSceneState() { return m_gameSceneState; }

		/// @brief ゲームシーンのステートを設定
		/// @param state ゲームシーンに設定するステート
		void SetGameSceneState(const EnGameSceneState& state) { m_gameSceneState = state; }

	private:
		
		/// @brief ゲームシーンを終了する処理
		void GameSceneEnd();

		/// @brief 初期化フラグ
		bool m_isInitd = false;
		/// @brief 一次停止フラグ
		bool m_pause = false;
		/// @brief ゲームシーンの状態を表すステート
		EnGameSceneState m_gameSceneState = enGameSceneNum;
		/// @brief ゲームカメラ
		GameCamera* m_gameCamera = nullptr;
		/// @brief プレイヤー
		player::Player* m_player = nullptr;
		/// @brief 防衛対象
		defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		/// @brief 敵生成器
		enemy::Generator* m_enemyGenerator = nullptr;
		/// @brief ステージ
		stage::Stage* m_stage = nullptr;
		/// @brief タイマー
		timer::Timer* m_timer = nullptr;
		/// @brief レンダリングエンジン
		render::RenderingEngine* m_renderingEngine = nullptr;
		/// @brief アイテム生成器
		item::ItemGenerator* m_itemGenerator = nullptr;
		/// @brief UI
		ui::GameUI* m_gameUI = nullptr;
		/// @brief サウンドプレイヤー
		sound::SoundPlayer* m_soundPlayer = nullptr;
		/// @brief クリア時のサウンドID
		int m_clearSoundID = 0;
		/// @brief ゲームオーバー時のサウンドID
		int m_gameOverSoundID = 0;
		/// @brief ボタンを押したときのサウンドID
		int m_pressKeySoundID = 0;
		/// @brief 終了時のサウンドが再生されたフラグ
		bool m_isPlayEndSound = false;
		/// @brief 画像
		render::sprite::SpriteRender* m_sampleSprite = nullptr;
		/// @brief ゲーム
		Game* m_game = nullptr;
		/// @brief シーン遷移
		SceneTransition* m_sceneTransition = nullptr;
		/// @brief 終了フラグ
		bool m_endFlag = false;
		/// @brief ボタンを押すように促すフォント
		render::font::FontRender* m_pressKeyFont = nullptr;
		/// @brief フォントカラー
		Vector4 m_pressKeyFontColor = { 0.0f,0.0f,0.0f,0.0f };
	};
}
