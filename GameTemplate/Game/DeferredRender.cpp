#include "stdafx.h"
#include "DeferredRender.h"

namespace render {

	const int RENDER_TARGET_NUM = 6;

	const char* NORMAL_LIGHTING_FILEPATH = "Assets/shader/deferredLighting.fx";

	const char* PBR_LIGHTING_FILEPATH = "Assets/shader/deferredLightingPBR.fx";

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
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		m_normalRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		m_metallicAndSmoothRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
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

		m_depthRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		m_lvpRT.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);

		m_effectRenderTarget.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		SpriteInitData effectSpriteInitData;
		effectSpriteInitData.m_textures[0] = &m_effectRenderTarget.GetRenderTargetTexture();
		effectSpriteInitData.m_width = FRAME_BUFFER_W;
		effectSpriteInitData.m_height = FRAME_BUFFER_H;
		effectSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		effectSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		m_effectSprite.Init(effectSpriteInitData);

		
		m_defferdLightSpriteInitData.m_width = FRAME_BUFFER_W;
		m_defferdLightSpriteInitData.m_height = FRAME_BUFFER_H;
		//使用するテクスチャはアルベドテクスチャと法線テクスチャ。
		m_defferdLightSpriteInitData.m_textures[0] = &m_albedRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[1] = &m_normalRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[2] = &m_metallicAndSmoothRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[3] = &m_worldPosRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[4] = &m_normalInViewRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[5] = &m_lvpRT.GetRenderTargetTexture();
		m_defferdLightSpriteInitData.m_textures[6] = &m_renderingEngine->GetShadow()->GetShadowMapTexture();
		if (m_isPBR == true) {
			m_defferdLightSpriteInitData.m_fxFilePath = PBR_LIGHTING_FILEPATH;
		}
		else {
			m_defferdLightSpriteInitData.m_fxFilePath = NORMAL_LIGHTING_FILEPATH;
		}
		m_defferdLightSpriteInitData.m_expandConstantBuffer[0] = m_renderingEngine->GetLighting()->GetLightAddress();
		m_defferdLightSpriteInitData.m_expandConstantBufferSize[0] = sizeof(m_renderingEngine->GetLighting()->GetLight());
		m_defferdLightSpriteInitData.m_expandConstantBuffer[1] = (void*)&m_renderingEngine->GetShadow()->GetLightCameraMatrix();
		m_defferdLightSpriteInitData.m_expandConstantBufferSize[1] = sizeof(m_renderingEngine->GetShadow()->GetLightCameraMatrix());
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
			&m_metallicAndSmoothRT,
			&m_worldPosRT,
			&m_normalInViewRT,
			&m_lvpRT
		};

		rc.WaitUntilToPossibleSetRenderTargets(RENDER_TARGET_NUM, rts);
		rc.SetRenderTargetsAndViewport(RENDER_TARGET_NUM, rts);
		rc.ClearRenderTargetViews(RENDER_TARGET_NUM, rts);
		for (int modelNum = 0; modelNum < m_deferredModels.size(); modelNum++)
		{
			m_deferredModels[modelNum]->Draw(rc);
		}

		

		rc.WaitUntilFinishDrawingToRenderTargets(RENDER_TARGET_NUM, rts);
		/*EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		EffectEngine::GetInstance()->Draw();*/

		rc.WaitUntilToPossibleSetRenderTarget(m_effectRenderTarget);
		rc.SetRenderTargetAndViewport(m_effectRenderTarget);
		rc.ClearRenderTargetView(m_effectRenderTarget);

		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		EffectEngine::GetInstance()->Draw();

		rc.WaitUntilFinishDrawingToRenderTarget(m_effectRenderTarget);

		
	}

	void DeferredRender::Draw(RenderContext& rc)
	{
		m_defferdLightSprite.Draw(rc);
		m_effectSprite.Draw(rc);
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