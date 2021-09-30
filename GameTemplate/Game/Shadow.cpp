#include "stdafx.h"
#include "Shadow.h"

namespace Render {
	Shadow::Shadow()
	{
		//シャドウマップ描画用のレンダリングターゲットを作成
		m_shadowMap.Create(
			1024,
			1024,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			m_clearColor
		);
	}

	Shadow::~Shadow()
	{

	}

	bool Shadow::Start()
	{

		return true;
	}

	void Shadow::Update()
	{
		m_ligCameraPos = { 0.0f,100.0f,500.0f };
		m_ligCameraTarget = m_ligCameraPos;
		m_ligCameraTarget.z -= 500.0f;
		LightCameraUpdate();


		////レンダリングコンテキストを取得
		//auto& renderContext = g_graphicsEngine->GetRenderContext();

		////レンダリングターゲットとして使用できるようになるまで待つ
		//renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//renderContext.SetRenderTargetAndViewport(m_shadowMap);
		////レンダリングターゲットをクリア
		//renderContext.ClearRenderTargetView(m_shadowMap);

		////影を生成するモデルの数だけ影のモデルをドローする
		//for (int count = 0; count < m_shadowModel.size(); count++) {
		//	std::vector<Model*>::iterator it;
		//	it = std::find(
		//		m_shadowModel.begin(),
		//		m_shadowModel.end(),
		//		nullptr
		//	);
		//	if (it != m_shadowModel.end()) {
		//		m_shadowModel.erase(it);
		//		continue;
		//	}
		//	m_shadowModel[count]->Draw(renderContext, m_lightCamera);
		//}
		//
		////レンダリングターゲットへ書き込み終了
		//renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		//// レンダリングターゲットをフレームバッファに戻す
		//renderContext.SetRenderTarget(
		//	g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		//	g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		//);
		//renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

	}

	void Shadow::Render(RenderContext& rc)
	{
		//レンダリングターゲットとして使用できるようになるまで待つ
		//rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//rc.SetRenderTargetAndViewport(m_shadowMap);
		////レンダリングターゲットをクリア
		//rc.ClearRenderTargetView(m_shadowMap);

		////影を生成するモデルの数だけ影のモデルをドローする
		//for (int count = 0; count < m_shadowModel.size(); count++) {
		//
		//	m_shadowModel[count]->Draw(rc, m_lightCamera);
		//}

		////レンダリングターゲットへ書き込み終了
		//rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		// レンダリングターゲットをフレームバッファに戻す
	/*	rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());*/
	}

	void Shadow::CreateShadowMap(RenderContext& rc)
	{
		//レンダリングターゲットとして使用できるようになるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		rc.SetRenderTargetAndViewport(m_shadowMap);
		//レンダリングターゲットをクリア
		rc.ClearRenderTargetView(m_shadowMap);

		//影を生成するモデルの数だけ影のモデルをドローする
		for (int count = 0; count < m_shadowModel.size(); count++) {

			m_shadowModel[count]->Draw(rc, m_lightCamera);
		}

		//レンダリングターゲットへ書き込み終了
		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);
	}

	void Shadow::SetShadowModel(Model* shadowModel)
	{ 
		m_shadowModel.push_back(shadowModel);
	}

	void Shadow::DeleteShadowModel(Model* shadowModel)
	{
		std::vector<Model*>::iterator it;
		it = std::find(
			m_shadowModel.begin(),
			m_shadowModel.end(),
			shadowModel
		);
		if (it != m_shadowModel.end()) {
			m_shadowModel.erase(it);
		}
	}

	void Shadow::LightCameraUpdate()
	{
		m_lightCamera.SetPosition(m_ligCameraPos);
		m_lightCamera.SetTarget(m_ligCameraTarget);
		m_lightCamera.SetUp(m_ligCameraUp);
		m_lightCamera.SetViewAngle(Math::DegToRad(m_ligCameraViewAngle));
		m_lightCamera.Update();
	}
}