#pragma once

namespace Render {
	class Bloom : public IGameObject
	{
	public:
		Bloom();
		~Bloom();
		void Init(RenderTarget* rt);
		bool Start();
		void Update();
		void Execute(RenderContext& rc);
		void LuminanceExtraction(RenderContext& rc);
		Texture& GetLuminanceRenderTargetTexture() { return m_luminanceRenderTarget.GetRenderTargetTexture(); }
		void SetBlurWeight(const float weight) { m_blurWeight = weight; }
	private:
		void InitBlurSprite();
		RenderTarget m_luminanceRenderTarget;
		Sprite m_luminanceSprite;
		SpriteInitData m_luminanceSpriteInitData;
		RenderTarget* m_mainRenderTargetAddress = nullptr;
		GaussianBlur* m_blur = nullptr;
		Sprite m_blurSprite;
		SpriteInitData m_blurSpriteInitData;
		float m_blurWeight = 20.0f;
	};

}