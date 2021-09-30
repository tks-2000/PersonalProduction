#include "stdafx.h"
#include "SkinModelRender.h"

namespace Render {

	SkinModelRender::SkinModelRender()
	{
		m_renderingEngine = FindGO<RenderingEngine>(RENDERING_ENGINE_NAME);
		m_lig = FindGO<Lighting>(LIGHTING_NAME);
		m_shadow = FindGO<Shadow>(SHADOW_NAME);
		m_shadowFlag = false;
		m_modelFilePath = nullptr;
	}

	SkinModelRender::~SkinModelRender()
	{
		if (m_shadowFlag == true) {
			m_shadow->DeleteShadowModel(&m_shadowModel);
		}
		m_renderingEngine->DeleteModel(&m_model);
	}

	bool SkinModelRender::Start()
	{
		//m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		return true;
	}

	void SkinModelRender::Init(const char* modelFilePath)
	{
		//���f���̃t�@�C���p�X��ݒ�
		m_modelFilePath = modelFilePath;
		m_modelInitData.m_tkmFilePath = modelFilePath;

		//�V�F�[�_�[�t�@�C���p�X��ݒ�
		m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";

		//���f���Ƀ��C�g�̏���n��
		m_modelInitData.m_expandConstantBuffer[0] = m_lig->GetLightAddress();
		m_modelInitData.m_expandConstantBufferSize[0] = sizeof(m_lig->GetLight());

		//���f���ɃV���h�E�}�b�v�̏���n��
		m_modelInitData.m_expandShaderResoruceView[0] = &m_shadow->GetShadowMapTexture();

		//���f���Ƀ��C�g�J�����̏���n��
		m_modelInitData.m_expandConstantBuffer[1] = (void*)&m_shadow->GetLightCameraMatrix();
		m_modelInitData.m_expandConstantBufferSize[1] = sizeof(m_shadow->GetLightCameraMatrix());

		//���������Ń��f��������������
		m_model.Init(m_modelInitData);

		//�������������f���������_�����O�G���W���ɓn��
		m_renderingEngine->SetDrawModel(&m_model);
	}

	void SkinModelRender::CreateShadow()
	{
		//�e�𐶐����邽�ߓ����t�@�C���p�X��ݒ�
		m_shadowModelInitData.m_tkmFilePath = m_modelFilePath;

		//�V���h�E�}�b�v�p�̃V�F�[�_�[�t�@�C���p�X��ݒ�
		m_shadowModelInitData.m_fxFilePath = "Assets/shader/shadowMap.fx";

		//�J���[�o�b�t�@�̃t�H�[�}�b�g��ݒ�
		m_shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		//���������ŉe�`�ʗp�̃��f����������
		m_shadowModel.Init(m_shadowModelInitData);

		//�e�`�ʗp�̃��f�����V���h�E�}�b�v�쐬�̃N���X�ɓn��
		m_shadow->SetShadowModel(&m_shadowModel);

		//�e�����ꂽ�t���O�𗧂Ă�
		m_shadowFlag = true;
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

		m_modelInitData.m_expandConstantBuffer[0] = m_lig->GetLightAddress();
		m_modelInitData.m_expandConstantBufferSize[0] = sizeof(m_lig->GetLight());

		m_animationClip = animationClip;

		m_animation.Init(m_skeleton, m_animationClip, animationNum);

		//m_modelInitData.m_cullMode = cullMode;

		//���������Ń��f��������������
		m_model.Init(m_modelInitData);
	}

	void SkinModelRender::PlayAnimation(int animNo, float interpolateTime)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	void SkinModelRender::Update()
	{

		m_animation.Progress(1.0f / 60.0f);

		if (m_shadowFlag == true) {
			m_shadowModel.UpdateWorldMatrix(m_position, m_qRot, m_scale);
		}

		m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);

		

		m_skeleton.Update(m_model.GetWorldMatrix());

	}

	void SkinModelRender::Render(RenderContext& rd)
	{
		//m_model.Draw(rd);
	}
}