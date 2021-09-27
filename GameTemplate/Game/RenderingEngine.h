#pragma once


namespace Render {
	class Lighting;
	class Shadow;

	/// @brief レンダリングに必要な機能をまとめたクラス
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();

	private:
		/// @brief ライティング
		Lighting* m_lig = nullptr;
		/// @brief シャドウ
		Shadow* m_shadow = nullptr;
	};
}
