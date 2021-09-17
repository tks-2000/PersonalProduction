#pragma once


namespace Render {
	class Lighting;

	/// @brief レンダリングに必要な機能をまとめたクラス
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();

	private:
		Lighting* m_lig = nullptr;
	};
}
