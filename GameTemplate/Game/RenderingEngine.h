#pragma once


namespace Render {
	class Lighting;
	class Shadow;
	class PostEffect;

	/// @brief レンダリングに必要な機能をまとめたクラス
	class RenderingEngine : public IGameObject
	{
	public:
		RenderingEngine();
		~RenderingEngine();
		bool Start();
		void Update();
		void Render(RenderContext& rc);

		/// @brief 描画するモデルを追加
		/// @param model 追加するモデルのアドレス
		void SetDrawModel(Model* model);

		/// @brief 描画しているモデルを削除
		/// @param model 削除するモデルのアドレス
		void DeleteModel(Model* model);

		

	private:


		/// @brief ライティング
		Lighting* m_lig = nullptr;
		/// @brief シャドウ
		Shadow* m_shadow = nullptr;
		/// @brief ポストエフェクト
		PostEffect* m_postEffect = nullptr;

		/// @brief メインレンダリングターゲット
		RenderTarget m_mainRenderTarget;

		/// @brief 描画するモデルの配列
		std::vector<Model*> m_drawModels;

		/// @brief フレームバッファのスプライトの初期化情報
		SpriteInitData m_frameBufferSpriteInitData;
		/// @brief フレームバッファのスプライト
		Sprite m_frameBufferSprite;

		Vector3 m_ligColor = g_vec3One;
	};
}
