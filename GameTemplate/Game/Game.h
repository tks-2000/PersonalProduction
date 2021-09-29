#pragma once

class SkinModelRender;
class Lighting;

namespace MainGame {
	class Game : public IGameObject
	{
	public:
		Game();
		~Game();
		bool Start();
		void Update();

	private:
		Render::SkinModelRender* m_unityChanModel = nullptr;
		Render::SkinModelRender* m_unityChanModel2 = nullptr;
		Render::SkinModelRender* m_backGroundModel = nullptr;
		Render::Lighting* m_lig = nullptr;
		Vector3 m_pos = g_vec3Zero;
	};

}