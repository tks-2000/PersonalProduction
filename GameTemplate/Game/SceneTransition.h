#pragma once

namespace mainGame {
	/// @brief シーンの遷移を行うクラス
	class SceneTransition : public IGameObject
	{
	public:
		SceneTransition();
		~SceneTransition();

		/// @brief 初期化
		void Init();

		/// @brief 実行
		void Execution();

		/// @brief フェードアウトを始める
		/// @param rate フェードアウトの速度
		void SetFeadOut(const float rate) { m_feadIn = false; m_feadOut = true; m_feadRate = rate; }

		/// @brief フェードインを始める
		/// @param rate フェードインの速度
		void SetFeadIn(const float rate) { m_feadIn = true; m_feadOut = false; m_feadRate = rate; }

		/// @brief フェードアウトしている最中か？
		/// @return trueでしている falseでしていない
		const bool IsFeadOut() const { return m_feadOut; }

		/// @brief フェードインしている最中か？
		/// @return trueでしている falseでしていない
		const bool IsFeadIn() const { return m_feadIn; }

	private:
		/// @brief 初期化フラグ
		bool m_isInitd = false;
		/// @brief フェードアウトフラグ
		bool m_feadOut = false;
		/// @brief フェードインフラグ
		bool m_feadIn = false;
		/// @brief フェードの進行速度
		float m_feadRate = 0.0f;
		/// @brief レンダリングエンジン
		render::RenderingEngine* m_renderingEngine = nullptr;
		/// @brief 不透明度
		float m_opacity = 1.0f;
		/// @brief シーンのカラー
		Vector4 m_sceneColor = g_vec4White;
	};

}