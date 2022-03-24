#include "stdafx.h"
#include "SkinModelRender.h"

namespace render {
	namespace model {

		const char* DEFERRED_PBR_FILEPATH = "Assets/shader/deferredModelPBR.fx";

		SkinModelRender::SkinModelRender()
		{
			m_renderingEngine = FindGO<RenderingEngine>(RENDERING_ENGINE_NAME);
			m_lig = m_renderingEngine->GetLighting();
			m_shadow = m_renderingEngine->GetShadow();
			m_shadowFlag = false;
			m_animFlag = false;
			m_modelFilePath = nullptr;
			m_fxFilePath = "Assets/shader/model.fx";
			m_deferredFxFilepath = "Assets/shader/deferredModel.fx";
			m_skeletonFilePath = nullptr;
			m_isInitd = false;
		}

		SkinModelRender::~SkinModelRender()
		{
			if (m_shadowFlag == true) {
				m_shadow->DeleteShadowModel(&m_shadowModel);
			}

			if (m_isDeferred == true) {
				m_renderingEngine->DeleteDeferrdModel(&m_model);
			}
			else {
				switch (m_target)
				{
				case enMainRenderTarget: {

					m_renderingEngine->DeleteModel(&m_model);
				}break;
				default: {
					m_renderingEngine->DeleteExpansionDrawModel(m_target, &m_model);
				}break;
				}
			}
		}

		bool SkinModelRender::Start()
		{
			
			return true;
		}


		void SkinModelRender::Init(
			const char* modelFilePath, 
			const EnModelDrawTarget& drawTarget,
			const char* skeletonPath, 
			AnimationClip* animationClip, 
			int animationNum, 
			EnModelUpAxis enAxsis
			
		)
		{
			//���ɏ���������Ă�������s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//���f���̃t�@�C���p�X��ݒ�
			m_modelFilePath = modelFilePath;
			m_modelInitData.m_tkmFilePath = modelFilePath;

			m_modelInitData.m_fxFilePath = m_fxFilePath;

			//���f���̏������ݒ�
			m_modelInitData.m_modelUpAxis = enAxsis;

			//�X�P���g���̃t�@�C���p�X���w�肳��Ă�����X�P���g�����쐬
			if (skeletonPath != nullptr) {

				//�X�P���g���̃t�@�C���p�X���L�����Ă���
				m_skeletonFilePath = skeletonPath;

				m_skeleton.Init(skeletonPath);
				//�X�P���g�������f���ɐݒ�
				m_modelInitData.m_skeleton = &m_skeleton;

				//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
				m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

				//�A�j���[�V�����N���b�v�ƃA�j���[�V�����̐����ݒ肳��Ă�����A�j���[�V�������쐬
				if (animationClip != nullptr && animationNum != 0) {

					m_animationClip = animationClip;

					m_animation.Init(m_skeleton, m_animationClip, animationNum);

					m_animFlag = true;
				}
			}
			else {
				//�A�j���[�V���������̒��_�V�F�[�_�[�̃G���g���[�|�C���g��ݒ�
				m_modelInitData.m_vsEntryPointFunc = "VSMain";
			}

			//���f���Ƀ��C�g�̏���n��
			m_modelInitData.m_expandConstantBuffer[0] = m_lig->GetLightAddress();
			m_modelInitData.m_expandConstantBufferSize[0] = sizeof(m_lig->GetLight());

			//���f���ɃV���h�E�}�b�v�̏���n��
			m_modelInitData.m_expandShaderResoruceView[0] = &m_shadow->GetShadowMapTexture();

			//���f���Ƀ��C�g�J�����̏���n��
			m_modelInitData.m_expandConstantBuffer[1] = (void*)&m_shadow->GetLightCameraMatrix();
			m_modelInitData.m_expandConstantBufferSize[1] = sizeof(m_shadow->GetLightCameraMatrix());

			

			m_target = drawTarget;

			//���������Ń��f��������������
			m_model.Init(m_modelInitData);

			switch (m_target)
			{
			case enExpandModelGroup1: {
				m_renderingEngine->SetExpansionDrawModel(m_target, &m_model);
			}break;
			case enExpandModelGroup2: {
				m_renderingEngine->SetExpansionDrawModel(m_target, &m_model);	
			}break;
			case enExpandModelGroup3: {
				m_renderingEngine->SetExpansionDrawModel(m_target, &m_model);
			}break;
			case enMainRenderTarget: {
				//�������������f���������_�����O�G���W���ɓn��
				m_renderingEngine->SetDrawModel(&m_model);
			}break;
			case enDeferrdRender: {
				//�������������f���������_�����O�G���W���ɓn��
				m_renderingEngine->SetDrawModel(&m_model);
			}break;
			default:
				break;
			}

			m_isDeferred = false;

			//����������
			m_isInitd = true;
		}

		void SkinModelRender::InitDeferrd(
			const char* modelFilepath,
			const bool isPBR,
			const char* skeletonPath,
			AnimationClip* animationClip,
			int animationNum,
			EnModelUpAxis enAxsis)
		{
			//���f���̃t�@�C���p�X��ݒ�
			m_modelFilePath = modelFilepath;
			m_modelInitData.m_tkmFilePath = modelFilepath;

			if (isPBR == true) {
				m_modelInitData.m_fxFilePath = DEFERRED_PBR_FILEPATH;
			}
			else {
				m_modelInitData.m_fxFilePath = m_deferredFxFilepath;
			}

			m_modelInitData.m_modelUpAxis = enAxsis;

			//�X�P���g���̃t�@�C���p�X���w�肳��Ă�����X�P���g�����쐬
			if (skeletonPath != nullptr) {

				//�X�P���g���̃t�@�C���p�X���L�����Ă���
				m_skeletonFilePath = skeletonPath;

				m_skeleton.Init(skeletonPath);
				//�X�P���g�������f���ɐݒ�
				m_modelInitData.m_skeleton = &m_skeleton;

				//���_�V�F�[�_�[�̃G���g���[�|�C���g���w��
				m_modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";

				//�A�j���[�V�����N���b�v�ƃA�j���[�V�����̐����ݒ肳��Ă�����A�j���[�V�������쐬
				if (animationClip != nullptr && animationNum != 0) {

					m_animationClip = animationClip;

					m_animation.Init(m_skeleton, m_animationClip, animationNum);

					m_animFlag = true;
				}
			}
			else {
				//�A�j���[�V���������̒��_�V�F�[�_�[�̃G���g���[�|�C���g��ݒ�
				m_modelInitData.m_vsEntryPointFunc = "VSMain";
			}

			//���f���Ƀ��C�g�J�����̏���n��
			m_modelInitData.m_expandConstantBuffer[0] = (void*)&m_shadow->GetLightCameraMatrix();
			m_modelInitData.m_expandConstantBufferSize[0] = sizeof(m_shadow->GetLightCameraMatrix());
			

			m_model.Init(m_modelInitData);

			m_renderingEngine->SetDeferredModel(&m_model);

			m_isDeferred = true;

			m_isInitd = true;
		}

		void SkinModelRender::SetRenderTarget(int groupNum, RenderTarget* rt)
		{
			m_renderingEngine->SetExpansionModlsRenderTarget(groupNum, rt);
		}


		void SkinModelRender::CreateShadow()
		{
			//�e�𐶐����邽�ߓ����t�@�C���p�X��ݒ�
			m_shadowModelInitData.m_tkmFilePath = m_modelFilePath;

			//�V���h�E�}�b�v�p�̃V�F�[�_�[�t�@�C���p�X��ݒ�
			m_shadowModelInitData.m_fxFilePath = "Assets/shader/shadowMap.fx";

			//�J���[�o�b�t�@�̃t�H�[�}�b�g��ݒ�
			m_shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

			if (m_animFlag == true) {
				m_shadowModelInitData.m_skeleton = &m_skeleton;

				m_shadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
				m_modelInitData.m_vsEntryPointFunc = "VSMain";
			}
			else {
				//�A�j���[�V���������̒��_�V�F�[�_�[�̃G���g���[�|�C���g��ݒ�
				m_modelInitData.m_vsEntryPointFunc = "VSMain";
			}

			//���������ŉe�`�ʗp�̃��f����������
			m_shadowModel.Init(m_shadowModelInitData);

			//�e�`�ʗp�̃��f�����V���h�E�}�b�v�쐬�̃N���X�ɓn��
			m_shadow->SetShadowModel(&m_shadowModel);

			//�e�����ꂽ�t���O�𗧂Ă�
			m_shadowFlag = true;
		}

		void SkinModelRender::PlayAnimation(const int animNo, const float interpolateTime)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		void SkinModelRender::Update()
		{


		}

		void SkinModelRender::Execution()
		{
			//����������Ă��Ȃ���Ύ��s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			if (m_updateWithMatrix == true) {
				m_model.SetWorldMatrix(m_world);
			}
			else {
				m_model.UpdateWorldMatrix(m_position, m_qRot, m_scale);
			}
			m_skeleton.Update(m_model.GetWorldMatrix());
			m_animation.Progress(1.0f / 60.0f);

			if (m_shadowFlag == true) {
				if (m_updateWithMatrix == true) {
					m_shadowModel.SetWorldMatrix(m_world);
				}
				else {
					m_shadowModel.UpdateWorldMatrix(m_position, m_qRot, m_scale);
				}
			}
		}
	}
}