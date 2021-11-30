#pragma once

class SkinModelRender;
class SpriteRender;
class CSoundSource;
;
namespace nsAI {
	class NaviMesh;
	class Path;
	class PathFinding;
}

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

	class GameCamera;

	/// @brief ゲームの状態を表す列挙型
	enum EnGameState {
		/// @brief ゲーム開始前
		enGameStart,
		/// @brief ゲーム進行中
		enGameInProgress,
		/// @brief ゲームクリア
		enGameClear,
		/// @brief ゲームオーバー
		enGameOver,
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

		/// @brief ゲームの状態を変更
		/// @param state ゲームの状態を表すステート
		void SetGameState(const EnGameState& state) { m_state = state; }

		/// @brief ゲームの状態を取得
		/// @return ゲームの状態を表すステート
		const EnGameState& GetGameState() { return m_state; }


	private:
		/// @brief ゲーム開始時の処理
		void GameStartExecution();
		/// @brief ゲームプレイ時の処理
		void InGameExecution();
		/// @brief ゲームクリア時の処理
		void GameClearExecution();
		/// @brief ゲームオーバー時の処理
		void GameOverExecution();
		/// @brief ゲーム中のオブジェクトを全て作成
		void AllNew();
		/// @brief ゲーム中のオブジェクトを全て削除
		void AllDelete();
		/// @brief ポーズ中の処理
		void Pause();

		/// @brief 初期化フラグ
		bool m_isInitd = false;

		render::model::SkinModelRender* m_unityChanModel = nullptr;
		render::model::SkinModelRender* m_unityChanModel2 = nullptr;
		render::model::SkinModelRender* m_backGroundModel = nullptr;
		render::model::SkinModelRender* m_backGroundModel2 = nullptr;

		render::sprite::SpriteRender* m_sampleSprite = nullptr;
		render::font::FontRender* m_sampleFont = nullptr;
		Vector3 m_pos = g_vec3Zero;

		Quaternion m_qRot = g_quatIdentity;

		Quaternion m_qRot2 = g_quatIdentity;

		enum UnityChanAnimation {
			enIdle,
			enWark,
			enAnimationNum
		};

		AnimationClip m_unityChanAnimationClip[enAnimationNum];

		EnGameState m_state = enGameStart;


		bool m_isDead = false;

		bool m_pause = false;

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

		CSoundSource* m_sound = nullptr;

		nsAI::NaviMesh m_nvmMesh;
		nsAI::Path m_path;
		nsAI::PathFinding m_pathFinding;
	};

}