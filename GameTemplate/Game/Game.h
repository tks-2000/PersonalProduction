#pragma once

class SkinModelRender;
class SpriteRender;


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

	//ゲーム中の物を制御するクラス
	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		void Init();
		bool Start();
		void Update();

		void SetGameState(const EnGameState& state) { m_state = state; }


	private:
		void GameStartExecution();
		void InGameExecution();
		void GameOverExecution();
		void AllNew();
		void AllDelete();
		void Pause();

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

		GameCamera* m_gameCamera = nullptr;

		bool m_isDead = false;

		player::Player* m_player = nullptr;

		bool m_pause = false;

		defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		enemy::Generator* m_enemyGenerator = nullptr;

		enemy::Enemy* m_enemy = nullptr;

		stage::Stage* m_stage = nullptr;

		timer::Timer* m_timer = nullptr;

		render::RenderingEngine* m_renderingEngine = nullptr;
	};

}