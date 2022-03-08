#pragma once

namespace mainGame {
	/// @brief シーンの遷移を行うクラス
	class SceneTransition : public IGameObject
	{
	public:
		SceneTransition();
		~SceneTransition();
		void Init();
		void Execution();
		void SetFeadOut(const float rate) { m_feadIn = false; m_feadOut = true; m_feadRate = rate; }
		void SetFeadIn(const float rate) { m_feadIn = true; m_feadOut = false; m_feadRate = rate; }

		const bool IsFeadOut() const { return m_feadOut; }
		const bool IsFeadIn() const { return m_feadIn; }

	private:
		bool m_isInitd = false;

		bool m_feadOut = false;
		bool m_feadIn = false;

		float m_feadRate = 0.0f;

		render::RenderingEngine* m_renderingEngine = nullptr;

		float m_opacity = 1.0f;

		Vector4 m_sceneColor = g_vec4White;


	};

}