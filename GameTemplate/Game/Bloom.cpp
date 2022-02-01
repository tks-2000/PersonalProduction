#include "stdafx.h"
#include "Bloom.h"

namespace render {
	namespace postEffect {
		Bloom::Bloom()
		{
			for (int blurNum = 0; blurNum < GAUSSIAN_BLUR_NUM; blurNum++) {
				m_gaussianBlur[blurNum] = NewGO<GaussianBlur>(0);
			}


		}

		Bloom::~Bloom()
		{
			for (int blurNum = 0; blurNum < GAUSSIAN_BLUR_NUM; blurNum++) {
				DeleteGO(m_gaussianBlur[blurNum]);
			}
		}

		void Bloom::Init(RenderTarget* rt)
		{
			//�P�x���o�p�̃X�v���C�g��������
			m_luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
			m_luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
			m_luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
			m_luminanceSpriteInitData.m_width = rt->GetWidth();
			m_luminanceSpriteInitData.m_height = rt->GetHeight();
			m_luminanceSpriteInitData.m_textures[0] = &rt->GetRenderTargetTexture();
			m_luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

			m_luminanceSprite.Init(m_luminanceSpriteInitData);

			//�u���[���������郌���_�����O�^�[�Q�b�g�̃A�h���X���L�����Ă���
			m_mainRenderTargetAddress = rt;

			//�P�x���o�p�̃����_�����O�^�[�Q�b�g
			m_luminanceRenderTarget.Create(
				rt->GetWidth(),
				rt->GetHeight(),
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			//�K�E�V�A���u���[��������

			//�P�x���o�̃e�N�X�`����ݒ肷��
			m_gaussianBlur[0]->Init(&m_luminanceRenderTarget.GetRenderTargetTexture());
			//�c��͏��ԂɃu���[���������e�N�X�`����ݒ肷��
			m_gaussianBlur[1]->Init(&m_gaussianBlur[0]->GetBlurTexture());
			m_gaussianBlur[2]->Init(&m_gaussianBlur[1]->GetBlurTexture());
			m_gaussianBlur[3]->Init(&m_gaussianBlur[2]->GetBlurTexture());

			//�K�E�V�A���u���[�p�̃X�v���C�g��������
			InitBlurSprite();
		}

		bool Bloom::Start()
		{
			return true;
		}

		void Bloom::Update()
		{

		}

		void Bloom::LuminanceExtraction(RenderContext& rc)
		{
			//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɋP�x���o�X�v���C�g��`�悷�� 
			rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
			rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
			rc.ClearRenderTargetView(m_luminanceRenderTarget);
			m_luminanceSprite.Draw(rc);
			rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);
		}

		void Bloom::Execute(RenderContext& rc)
		{
			//�P�x���o�����s
			LuminanceExtraction(rc);

			//�K�E�V�A���u���[�𕡐�����s
			for (int blurNum = 0; blurNum < GAUSSIAN_BLUR_NUM; blurNum++) {
				m_gaussianBlur[blurNum]->ExecuteOnGPU(rc, m_blurWeight);
			}

			//���C�������_�����O�^�[�Q�b�g�Ƀu���[�̂��������P�x���o�e�N�X�`�������Z��������
			rc.WaitUntilToPossibleSetRenderTarget(*m_mainRenderTargetAddress);
			rc.SetRenderTargetAndViewport(*m_mainRenderTargetAddress);
			m_blurSprite.Draw(rc);
			rc.WaitUntilFinishDrawingToRenderTarget(*m_mainRenderTargetAddress);

		}

		void Bloom::InitBlurSprite()
		{
			//�u���[����������Ԃ̃X�v���C�g���쐬����
			for (int blurNum = 0; blurNum < GAUSSIAN_BLUR_NUM; blurNum++) {
				m_blurSpriteInitData.m_textures[blurNum] = &m_gaussianBlur[blurNum]->GetBlurTexture();
			}

			m_blurSpriteInitData.m_width = 1280;
			m_blurSpriteInitData.m_height = 720;
			m_blurSpriteInitData.m_fxFilePath = "Assets/shader/kawaseBloom.fx";
			m_blurSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
			m_blurSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

			m_blurSprite.Init(m_blurSpriteInitData);
		}
	}
}