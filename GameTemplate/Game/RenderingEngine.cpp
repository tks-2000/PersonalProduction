#include "stdafx.h"
#include "RenderingEngine.h"

namespace render {
	RenderingEngine::RenderingEngine()
	{
		m_lig = NewGO<light::Lighting>(0, light::LIGHTING_NAME);
		m_shadow = NewGO<shadow::Shadow>(0, shadow::SHADOW_NAME);
		m_postEffect = NewGO<postEffect::PostEffect>(0, postEffect::POST_EFFECT_NAME);

		//���C�������_�����O�^�[�Q�b�g���쐬
		m_mainRenderTarget.Create(
			1280,
			720,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//�t���[���o�b�t�@�̃R�s�[�p�̃X�v���C�g��p�ӂ���
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
		m_lig->SetDirectionLightColor({ 0.3f, 0.3f, 0.3f });
		m_lig->SetDirectionLightDirection({ 0.0f, -0.5f, 1.0f });
		m_lig->SetHemiSphereLifhtGroundColor({ 0.5f,0.0f,0.0f });
		m_lig->SetHemiSphereLifhtSkyColor({ 0.0f,0.0f,0.5f });
		m_lig->SetPointLighitPos(0, { 0.0f,200.0f,0.0f });
		m_lig->SetPointLightColor(0, { 0.0f,1.0f,0.0f });
		m_lig->SetPointLightRange(0, 1000.0f);
		m_lig->SetSpotLightDirection(0, { 0.0f,-1.0f,0.0f });
		m_lig->SetSpotLightColor(0, { 5.0f,5.0f,5.0f });
		//m_shadow->SetLightCameraTarget({ 0.0f,0.0f,0.0f });

		//�u���[��������
		//m_postEffect->SetBlur(&m_mainRenderTarget);

		//�u���[����������
		m_postEffect->SetBloom(&m_mainRenderTarget);

		return true;
	}

	void RenderingEngine::Update()
	{
		
		if (g_pad[0]->IsPress(enButtonSelect)) {


			if (g_pad[0]->IsPress(enButtonUp)) {
				m_ligColor.x += 0.01f;
				
			}

			if (g_pad[0]->IsPress(enButtonDown)) {
				m_ligColor.x -= 0.01f;
				
			}
			if (g_pad[0]->IsPress(enButtonRight)) {
				
				m_ligColor.y += 0.01f;
			
			}

			if (g_pad[0]->IsPress(enButtonLeft)) {
				
				m_ligColor.y -= 0.01f;
			
			}

		}
		else {

			if (g_pad[0]->IsPress(enButtonUp)) {

				m_ligColor.z += 0.01f;
			}

			if (g_pad[0]->IsPress(enButtonDown)) {

				m_ligColor.z -= 0.01f;
			}

			if (g_pad[0]->IsPress(enButtonRight)) {
				m_ligColor.x += 0.01f;
				m_ligColor.y += 0.01f;
				m_ligColor.z += 0.01f;
			}

			if (g_pad[0]->IsPress(enButtonLeft)) {
				m_ligColor.x -= 0.01f;
				m_ligColor.y -= 0.01f;
				m_ligColor.z -= 0.01f;
			}
		}
		m_lig->SetHemiSphereLifhtSkyColor(m_ligColor);
		
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

		//�|�X�g�G�t�F�N�g�����s
		m_postEffect->Execute(rc);

		// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

		//�t���[���o�b�t�@�̃R�s�[�̃X�v���C�g��\������
		m_frameBufferSprite.Draw(rc);

		for (int spriteNum = 0; spriteNum < m_drawSprites.size(); spriteNum++) {
			m_drawSprites[spriteNum]->Draw(rc);
		}
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

	void RenderingEngine::SetDrawSprite(Sprite* sprite)
	{
		m_drawSprites.push_back(sprite);
	}

	void RenderingEngine::DeleteSprite(Sprite* sprite)
	{
		std::vector<Sprite*>::iterator it;
		it = std::find(
			m_drawSprites.begin(),
			m_drawSprites.end(),
			sprite
		);
		if (it != m_drawSprites.end()) {
			m_drawSprites.erase(it);
		}
	}
}