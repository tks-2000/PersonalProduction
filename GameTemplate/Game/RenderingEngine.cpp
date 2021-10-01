#include "stdafx.h"
#include "RenderingEngine.h"

namespace Render {
	RenderingEngine::RenderingEngine()
	{
		m_lig = NewGO<Lighting>(0, LIGHTING_NAME);
		m_shadow = NewGO<Shadow>(0, SHADOW_NAME);
		m_postEffect = NewGO<PostEffect>(0, POST_EFFECT_NAME);

		//メインレンダリングターゲットを作成
		m_mainRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//フレームバッファのコピーのスプライトを用意する
		m_frameBufferSpriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		m_frameBufferSpriteInitData.m_width = 1280;
		m_frameBufferSpriteInitData.m_height = 720;
		m_frameBufferSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		m_frameBufferSprite.Init(m_frameBufferSpriteInitData);

		
	
	}

	RenderingEngine::~RenderingEngine()
	{
		DeleteGO(m_lig);
		DeleteGO(m_shadow);
		DeleteGO(m_postEffect);
	}

	bool RenderingEngine::Start()
	{
		m_lig->SetDirectionLightDirection({ 0.0f, -0.5f, 1.0f });
		m_lig->SetHemiSphereLifhtGroundColor({ 0.2f,0.0f,0.0f });
		m_lig->SetHemiSphereLifhtSkyColor({ 0.0f,0.0f,0.2f });
		m_lig->SetPointLightColor(0, { 0.0f,1.0f,0.0f });
		m_lig->SetPointLightRange(0, 300.0f);
		m_lig->SetSpotLightColor(0, { 0.1f,0.1f,0.1f });

		//ブラーをかける
		//m_postEffect->SetBlur(&m_mainRenderTarget);

		m_postEffect->SetBloom(&m_mainRenderTarget);
		return true;
	}

	void RenderingEngine::Update()
	{
		m_ligColor.x += g_pad[0]->GetRStickYF() * 0.01f;
		m_ligColor.y += g_pad[0]->GetRStickYF() * 0.01f;
		m_ligColor.z += g_pad[0]->GetRStickYF() * 0.01f;

		m_lig->SetDirectionLightColor(m_ligColor);
		
	}

	void RenderingEngine::Render(RenderContext& rc)
	{

		m_shadow->CreateShadowMap(rc);

		//メインレンダリングターゲットを使用可能になるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);

		//描画するモデルを全て描画する
		for (int modelNum = 0; modelNum < m_drawModels.size(); modelNum++) {
			m_drawModels[modelNum]->Draw(rc);
		}

		//メインレンダリングターゲットへ書き込み終了
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

		//ポストエフェクトを実行
		m_postEffect->Execute(rc);

		// レンダリングターゲットをフレームバッファに戻す
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

		//フレームバッファのコピーのスプライトを表示する
		m_frameBufferSprite.Draw(rc);
	}

	void RenderingEngine::SetDrawModel(Model* model)
	{
		m_drawModels.push_back(model);
	}

	void RenderingEngine::DeleteModel(Model* model)
	{
		std::vector<Model*>::iterator it;
		it = std::find(
			m_drawModels.begin(),
			m_drawModels.end(),
			model
		);
		if (it != m_drawModels.end()) {
			m_drawModels.erase(it);
		}
	}
}