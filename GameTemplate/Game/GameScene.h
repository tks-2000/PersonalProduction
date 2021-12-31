#pragma once

class CSoundSource;


namespace mainGame {

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

	enum EnGameSceneState {
		enGameSceneStart,
		enGameSceneInProgress,
		enGameSceneClear,
		enGameSceneOver,
		enGameSceneNum
	};

	/// @brief ゲームシーンで出現する物を管理するクラス
	class GameScene : public IGameObject
	{

	public:
		GameScene();
		~GameScene();
		void Init();
		void Execution();

	private:
		void CreateGameScene();
		void DeleteGameScene();

		bool m_isInitd = false;

		bool m_pause = false;

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

		map::MiniMap* m_miniMap = nullptr;

		item::ItemGenerator* m_itemGenerator = nullptr;

		ui::GameUI* m_gameUI = nullptr;

		CSoundSource* m_sound = nullptr;

		render::sprite::SpriteRender* m_sampleSprite = nullptr;
	};
}
