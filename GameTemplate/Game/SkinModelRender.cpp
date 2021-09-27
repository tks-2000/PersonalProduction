#include "stdafx.h"
#include "SkinModelRender.h"

namespace Render {

	SkinModelRender::SkinModelRender()
	{
		m_lig = FindGO<Lighting>(LIGHTING_NAME);
		m_shadow = FindGO<Shadow>(SHADOW_NAME);
		m_shadowFlag = false;
		m_modelFilePath = nullptr;
	}

	SkinModelRender::~SkinModelRender()
	{

	}

	bool SkinModelRender::Start()
	{
		m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		return true;
	}

	void SkinModelRender::Init(const char* modelFilePath)
	{
		m_modelFilePath = modelFilePath;
		m_modelInitData.m_tkmFilePath = modelFilePath;
		m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

		m_modelInitData.m_expandConstantBuffer = m_lig->GetLightAddress();
		m_modelInitData.m_expandConstantBufferSize = sizeof(m_lig->GetLight());

		//‰Šú‰»î•ñ‚Åƒ‚ƒfƒ‹‚ð‰Šú‰»‚·‚é
		m_model.Init(m_modelInitData);
	}

	void SkinModelRender::CreateShadow()
	{
		m_shadowModelInitData.m_tkmFilePath = m_modelFilePath;
		m_shadowModelInitData.m_fxFilePath = "Assets/shader/shadowMap.fx";
		m_shadowModel.Init(m_shadowModelInitData);
		m_shadow->SetShadowModel(&m_shadowModel);
	}

	void SkinModelRender::InitA(const char* modelFilePath, const char* skeletonPath, EnModelUpAxis enAxsis, AnimationClip* animationClip, int animationNum, bool cullMode)
	{
		m_modelInitData.m_tkmFilePath = modelFilePath;
		m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
		m_modelInitData.m_vsEntryPointFunc = "VSMain";
		m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

		if (skeletonPath != nullptr) {
			m_skeleton.Init(skeletonPath);
			m_modelInitData.m_skeleton = &m_skeleton;
		}

		m_modelInitData.m_modelUpAxis = enAxsis;

		m_modelInitData.m_expandConstantBuffer = m_lig->GetLightAddress();
		m_modelInitData.m_expandConstantBufferSize = sizeof(m_lig->GetLight());

		m_animationClip = animationClip;

		m_animation.Init(m_skeleton, m_animationClip, animationNum);

		//m_modelInitData.m_cullMode = cullMode;

		//‰Šú‰»î•ñ‚Åƒ‚ƒfƒ‹‚ð‰Šú‰»‚·‚é
		m_model.Init(m_modelInitData);
	}

	void SkinModelRender::PlayAnimation(int animNo, float interpolateTime)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	void SkinModelRender::Update()
	{

		m_animation.Progress(1.0f / 60.0f);

		m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);

		m_skeleton.Update(m_model.GetWorldMatrix());

	}

	void SkinModelRender::Render(RenderContext& rd)
	{
		if (m_shadowFlag == true) {
			RenderTarget shadowMap = m_shadow->GetShadowMap();
			rd.WaitUntilToPossibleSetRenderTarget(shadowMap);
			rd.SetRenderTargetAndViewport(shadowMap);
			rd.ClearRenderTargetView(shadowMap);
			m_shadowModel.Draw(rd);

			rd.WaitUntilFinishDrawingToRenderTarget(shadowMap);
		}
		m_model.Draw(rd);
	}
}