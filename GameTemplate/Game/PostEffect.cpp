#include "stdafx.h"
#include "PostEffect.h"

namespace render {
	namespace postEffect {
		PostEffect::PostEffect()
		{
			m_gaussianBlur = NewGO<GaussianBlur>(0, GAUSSIAN_BLUR_NAME);
			m_blurFlag = false;
			m_bloom = NewGO<Bloom>(0, BLOOM_NAME);
			m_bloomFlag = false;
		}

		PostEffect::~PostEffect()
		{
			DeleteGO(m_gaussianBlur);
			DeleteGO(m_bloom);
		}

		bool PostEffect::Start()
		{

			return true;
		}

		void PostEffect::Update()
		{
			m_blurWeight += g_pad[0]->GetRStickXF();
			if (m_blurWeight < 0.0f) {
				m_blurWeight = 0.0f;
			}
		}

		void PostEffect::Render(RenderContext& rc)
		{

		}

		void PostEffect::Execute(RenderContext& rc)
		{
			//�u���[�t���O�������Ă�����c
			if (m_blurFlag == true) {
				//�u���[�����s����
				m_gaussianBlur->ExecuteOnGPU(rc, m_blurWeight);
				rc.WaitUntilToPossibleSetRenderTarget(*m_mainRenderTargetAddress);
				rc.SetRenderTargetAndViewport(*m_mainRenderTargetAddress);
				//�u���[�̂��������摜��\��
				m_blurSprite.Draw(rc);
				rc.WaitUntilFinishDrawingToRenderTarget(*m_mainRenderTargetAddress);
			}
			//�u���[���t���O�������Ă�����c
			if (m_bloomFlag == true) {
				//�u���[�������s����
				m_bloom->Execute(rc);
			}
		}

		void PostEffect::SetBlur(RenderTarget* rt, float blurWeight)
		{
			//�u���[��������
			m_gaussianBlur->Init(&rt->GetRenderTargetTexture());
			//�u���[�������郌���_�����O�^�[�Q�b�g�̃A�h���X���L��
			m_mainRenderTargetAddress = rt;
			m_blurWeight = blurWeight;
			//�u���[����������Ԃ̃X�v���C�g���쐬����
			m_blurSpriteInitData.m_textures[0] = &m_gaussianBlur->GetBlurTexture();
			m_blurSpriteInitData.m_width = 1280;
			m_blurSpriteInitData.m_height = 720;
			m_blurSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
			m_blurSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
			m_blurSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
			m_blurSprite.Init(m_blurSpriteInitData);
			//�u���[�t���O�𗧂Ă�
			m_blurFlag = true;
		}

		void PostEffect::SetBloom(RenderTarget* rt)
		{
			m_bloom->Init(rt);
			m_bloomFlag = true;
		}
	}
}