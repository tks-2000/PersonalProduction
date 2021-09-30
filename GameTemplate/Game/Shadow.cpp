#include "stdafx.h"
#include "Shadow.h"

namespace Render {
	Shadow::Shadow()
	{
		//�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬
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


		////�����_�����O�R���e�L�X�g���擾
		//auto& renderContext = g_graphicsEngine->GetRenderContext();

		////�����_�����O�^�[�Q�b�g�Ƃ��Ďg�p�ł���悤�ɂȂ�܂ő҂�
		//renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//renderContext.SetRenderTargetAndViewport(m_shadowMap);
		////�����_�����O�^�[�Q�b�g���N���A
		//renderContext.ClearRenderTargetView(m_shadowMap);

		////�e�𐶐����郂�f���̐������e�̃��f�����h���[����
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
		////�����_�����O�^�[�Q�b�g�֏������ݏI��
		//renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		//// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
		//renderContext.SetRenderTarget(
		//	g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
		//	g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		//);
		//renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

	}

	void Shadow::Render(RenderContext& rc)
	{
		//�����_�����O�^�[�Q�b�g�Ƃ��Ďg�p�ł���悤�ɂȂ�܂ő҂�
		//rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		//rc.SetRenderTargetAndViewport(m_shadowMap);
		////�����_�����O�^�[�Q�b�g���N���A
		//rc.ClearRenderTargetView(m_shadowMap);

		////�e�𐶐����郂�f���̐������e�̃��f�����h���[����
		//for (int count = 0; count < m_shadowModel.size(); count++) {
		//
		//	m_shadowModel[count]->Draw(rc, m_lightCamera);
		//}

		////�����_�����O�^�[�Q�b�g�֏������ݏI��
		//rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

		// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
	/*	rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());*/
	}

	void Shadow::CreateShadowMap(RenderContext& rc)
	{
		//�����_�����O�^�[�Q�b�g�Ƃ��Ďg�p�ł���悤�ɂȂ�܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		rc.SetRenderTargetAndViewport(m_shadowMap);
		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_shadowMap);

		//�e�𐶐����郂�f���̐������e�̃��f�����h���[����
		for (int count = 0; count < m_shadowModel.size(); count++) {

			m_shadowModel[count]->Draw(rc, m_lightCamera);
		}

		//�����_�����O�^�[�Q�b�g�֏������ݏI��
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