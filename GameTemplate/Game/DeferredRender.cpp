#include "stdafx.h"
#include "DeferredRender.h"

namespace render {

	const int RENDER_TARGET_NUM = 4;

	DeferredRender::DeferredRender()
	{

	}

	DeferredRender::~DeferredRender()
	{

	}

	void DeferredRender::Init(RenderingEngine* renderingEngine)
	{
		m_renderingEngine = renderingEngine;

		m_albedRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);

		m_normalRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);

		m_worldPosRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);

		m_normalInViewRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN
		);

		
		m_defferdLightSpriteInitData.m_width = FRAME_BUFFER_W;
		m_defferdLightSpriteInitData.m_height = FRAME_BUFFER_H;
		//使用するテクスチャはアルベドテクスチャと法線テクスチャ。
		m_defferdLightSpriteInitData.m_textures[0] = &m_albedRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[1] = &m_normalRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[2] = &m_worldPosRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[3] = &m_normalInViewRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_fxFilePath = "Assets/shader/deferredLighting.fx";
		m_defferdLightSpriteInitData.m_expandConstantBuffer = m_renderingEngine->GetLighting()->GetLightAddress();
		m_defferdLightSpriteInitData.m_expandConstantBufferSize = sizeof(m_renderingEngine->GetLighting()->GetLight());
		m_defferdLightSprite.Init(m_defferdLightSpriteInitData);
	

		m_isInitd = true;
	}

	void DeferredRender::Execute(RenderContext& rc)
	{
		if (m_isInitd == false) {
			return;
		}

		RenderTarget* rts[RENDER_TARGET_NUM] = {
			&m_albedRT,
			&m_normalRT,
			&m_worldPosRT,
			&m_normalInViewRT
		};

		rc.WaitUntilToPossibleSetRenderTargets(RENDER_TARGET_NUM, rts);
		rc.SetRenderTargetsAndViewport(RENDER_TARGET_NUM, rts);
		rc.ClearRenderTargetViews(RENDER_TARGET_NUM, rts);
		for (int modelNum = 0; modelNum < m_deferredModels.size(); modelNum++)
		{
			m_deferredModels[modelNum]->Draw(rc);
		}
		rc.WaitUntilFinishDrawingToRenderTargets(RENDER_TARGET_NUM, rts);

		
	}

	void DeferredRender::Draw(RenderContext& rc)
	{
		m_defferdLightSprite.Draw(rc);
	}

	void DeferredRender::SetDrawModel(Model* model)
	{
		m_deferredModels.push_back(model);
	}

	void DeferredRender::DeleteDrawModel(Model* model)
	{
		std::vector<Model*>::iterator it;
		it = std::find(
			m_deferredModels.begin(),
			m_deferredModels.end(),
			model
		);
		if (it != m_deferredModels.end()) {
			m_deferredModels.erase(it);
		}
	}
}