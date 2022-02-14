#pragma once
namespace render {

	class RenderingEngine;

	/// @brief ディファードレンダリングを行うクラス
	class DeferredRender
	{
	public:
		DeferredRender();
		~DeferredRender();
		void Init(RenderingEngine* renderingEngine);
		void SetPBR(const bool isPBR) { m_isPBR = isPBR; }
		void Execute(RenderContext& rc);
		void Draw(RenderContext& rc);
		void SetDrawModel(Model* model);
		void DeleteDrawModel(Model* model);
		
	private:

		bool m_isInitd = false;

		bool m_isPBR = false;

		RenderTarget m_albedRT;
		RenderTarget m_normalRT;
		RenderTarget m_metallicAndSmoothRT;
		RenderTarget m_worldPosRT;
		RenderTarget m_normalInViewRT;
		RenderTarget m_depthRT;
		RenderTarget m_lvpRT;


		RenderTarget m_effectRenderTarget;
		Sprite m_effectSprite;

		/// @brief ディファードレンダリングを行うモデルの配列
		std::vector<Model*> m_deferredModels;


		SpriteInitData m_defferdLightSpriteInitData;
		Sprite m_defferdLightSprite;

		RenderingEngine* m_renderingEngine = nullptr;
	};
}
