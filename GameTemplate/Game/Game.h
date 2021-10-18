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

	//ÉQÅ[ÉÄíÜÇÃï®Çêßå‰Ç∑ÇÈÉNÉâÉX
	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		bool Start();
		void Update();

	private:

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

		GameCamera* m_gameCamera = nullptr;

		bool m_isDead = false;

		player::Player* m_player = nullptr;

		bool m_pause = false;

		defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;

		enemy::Generator* m_enemyGenerator = nullptr;

		enemy::Enemy* m_enemy = nullptr;

		stage::Stage* m_stage = nullptr;

		timer::Timer* m_timer = nullptr;
	};

}