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
		SkinModelRender* m_unityChanModel = nullptr;
		SkinModelRender* m_backGroundModel = nullptr;
		Render::Lighting* m_lig = nullptr;
	};

}