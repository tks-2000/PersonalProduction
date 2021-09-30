#include "stdafx.h"
#include "RenderingEngine.h"

namespace Render {
	RenderingEngine::RenderingEngine()
	{
		//���C�������_�����O�^�[�Q�b�g���쐬
		m_mainRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//�t���[���o�b�t�@�̃R�s�[�̃X�v���C�g��p�ӂ���
		m_frameBufferSpriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		m_frameBufferSpriteInitData.m_width = 1280;
		m_frameBufferSpriteInitData.m_height = 720;
		m_frameBufferSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		m_frameBufferSprite.Init(m_frameBufferSpriteInitData);

		m_lig = NewGO<Lighting>(0, LIGHTING_NAME);
		m_shadow = NewGO<Shadow>(0, SHADOW_NAME);
	
	}

	RenderingEngine::~RenderingEngine()
	{
		DeleteGO(m_lig);
		DeleteGO(m_shadow);
	}

	bool RenderingEngine::Start()
	{
		m_lig->SetHemiSphereLifhtGroundColor({ 0.3f,0.0f,0.0f });
		m_lig->SetHemiSphereLifhtSkyColor({ 0.0f,0.0f,0.3f });
		m_lig->SetPointLightColor(0, { 0.0f,1.0f,0.0f });
		m_lig->SetPointLightRange(0, 300.0f);
		m_lig->SetSpotLightColor(0, { 1.0f,1.0f,1.0f });
		

		return true;
	}

	void RenderingEngine::Update()
	{
		
	}

	void RenderingEngine::Render(RenderContext& rc)
	{

		m_shadow->CreateShadowMap(rc);

		//���C�������_�����O�^�[�Q�b�g���g�p�\�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);

		//�`�悷�郂�f����S�ĕ`�悷��
		for (int modelNum = 0; modelNum < m_drawModels.size(); modelNum++) {
			m_drawModels[modelNum]->Draw(rc);
		}

		//���C�������_�����O�^�[�Q�b�g�֏������ݏI��
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

		

		// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

		//�t���[���o�b�t�@�̃R�s�[�̃X�v���C�g��\������
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