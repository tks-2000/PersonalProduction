#pragma once
namespace render {

	class RenderingEngine;

	/// @brief �f�B�t�@�[�h�����_�����O���s���N���X
	class DeferredRender
	{
	public:
		DeferredRender();
		~DeferredRender();
		void Init(RenderingEngine* renderingEngine);
		void Execute(RenderContext& rc);
		void Draw(RenderContext& rc);
		void SetDrawModel(Model* model);
		void DeleteDrawModel(Model* model);
		
	private:

		bool m_isInitd = false;

		RenderTarget m_albedRT;
		RenderTarget m_normalRT;
		RenderTarget m_worldPosRT;
		RenderTarget m_normalInViewRT;
		RenderTarget m_depthRT;
		RenderTarget m_lvpRT;


		RenderTarget m_effectRenderTarget;
		Sprite m_effectSprite;

		/// @brief �f�B�t�@�[�h�����_�����O���s�����f���̔z��
		std::vector<Model*> m_deferredModels;


		SpriteInitData m_defferdLightSpriteInitData;
		Sprite m_defferdLightSprite;

		RenderingEngine* m_renderingEngine = nullptr;
	};
}
