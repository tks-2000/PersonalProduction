#pragma once

class SkinModelRender;
class Lighting;
class Shadow;


namespace MainGame {
	namespace Player {
		class Player;
	}

	class GameCamera;

	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		bool Start();
		void Update();

	private:

		void Pause();

		Render::SkinModelRender* m_unityChanModel = nullptr;
		Render::SkinModelRender* m_unityChanModel2 = nullptr;
		Render::SkinModelRender* m_backGroundModel = nullptr;
		Render::SkinModelRender* m_backGroundModel2 = nullptr;
		Render::Lighting* m_lig = nullptr;
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

		Render::Shadow* m_shadow = nullptr;

		Player::Player* m_player = nullptr;

		bool m_pause = false;
	};

}