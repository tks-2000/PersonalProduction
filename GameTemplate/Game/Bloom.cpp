#include "stdafx.h"
#include "Bloom.h"

namespace Render {
	Bloom::Bloom()
	{
		m_blur = NewGO<GaussianBlur>(0);

		
	}

	Bloom::~Bloom()
	{

	}

	void Bloom::Init(RenderTarget* rt)
	{
		m_luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		m_luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		m_luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		m_luminanceSpriteInitData.m_width = rt->GetWidth();
		m_luminanceSpriteInitData.m_height = rt->GetHeight();
		m_luminanceSpriteInitData.m_textures[0] = &rt->GetRenderTargetTexture();
		m_luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_luminanceSprite.Init(m_luminanceSpriteInitData);

		m_mainRenderTargetAddress = rt;

		m_luminanceRenderTarget.Create(
			rt->GetWidth(),
			rt->GetHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		m_blur->Init(&m_luminanceRenderTarget.GetRenderTargetTexture());
		InitBlurSprite();
	}

	bool Bloom::Start()
	{
		return true;
	}

	void Bloom::Update()
	{

	}

	void Bloom::LuminanceExtraction(RenderContext& rc)
	{
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
		rc.ClearRenderTargetView(m_luminanceRenderTarget);
		m_luminanceSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);
	}

	void Bloom::Execute(RenderContext& rc)
	{
		LuminanceExtraction(rc);
		m_blur->ExecuteOnGPU(rc, m_blurWeight);
		rc.WaitUntilToPossibleSetRenderTarget(*m_mainRenderTargetAddress);
		rc.SetRenderTargetAndViewport(*m_mainRenderTargetAddress);
		m_blurSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(*m_mainRenderTargetAddress);
		
	}

	void Bloom::InitBlurSprite()
	{
		//ブラーをかけた状態のスプライトを作成する
		m_blurSpriteInitData.m_textures[0] = &m_blur->GetBlurTexture();
		m_blurSpriteInitData.m_width = 1280;
		m_blurSpriteInitData.m_height = 720;
		m_blurSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_blurSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		m_blurSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_blurSprite.Init(m_blurSpriteInitData);
	}
}