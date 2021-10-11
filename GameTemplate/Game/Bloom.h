#pragma once

namespace render {
	namespace postEffect {

		/// @brief �u���[����������N���X
		class Bloom : public IGameObject
		{
		public:
			Bloom();
			~Bloom();
			/// @brief �u���[����������
			/// @param rt �u���[���������郌���_�����O�^�[�Q�b�g�̃A�h���X
			void Init(RenderTarget* rt);
			bool Start();
			void Update();
			/// @brief �u���[�������s
			/// @param rc �����_�����O�R���e�L�X�g
			void Execute(RenderContext& rc);
			/// @brief �P�x���o�����s
			/// @param rc �����_�����O�R���e�L�X�g
			void LuminanceExtraction(RenderContext& rc);
			/// @brief �P�x���o�����e�N�X�`�����擾
			/// @return �P�x���o���ꂽ�e�N�X�`���̎Q��
			Texture& GetLuminanceRenderTargetTexture() { return m_luminanceRenderTarget.GetRenderTargetTexture(); }
			/// @brief �u���[�̏d�݂�ݒ�
			/// @param weight �u���[�ɐݒ肷��d��
			void SetBlurWeight(const float weight) { m_blurWeight = weight; }
		private:

			/// @brief �u���[��������X�v���C�g��������
			void InitBlurSprite();

			/// @brief �P�x���o�p�̃����_�����O�^�[�Q�b�g
			RenderTarget m_luminanceRenderTarget;
			/// @brief �P�x���o�p�̃X�v���C�g
			Sprite m_luminanceSprite;
			/// @brief �P�x���o�p�̃X�v���C�g�̏��������
			SpriteInitData m_luminanceSpriteInitData;
			/// @brief �u���[�������郌���_�����O�^�[�Q�b�g�̃A�h���X
			RenderTarget* m_mainRenderTargetAddress = nullptr;
			/// @brief �K�E�V�A���u���[�������鐔
			enum { GAUSSIAN_BLUR_NUM = 4 };
			/// @brief �K�E�V�A���u���[
			GaussianBlur* m_gaussianBlur[GAUSSIAN_BLUR_NUM] = { nullptr };
			/// @brief �u���[��������X�v���C�g
			Sprite m_blurSprite;
			/// @brief �u���[��������X�v���C�g�̏��������
			SpriteInitData m_blurSpriteInitData;
			/// @brief �u���[�̏d��
			float m_blurWeight = 10.0f;
		};
	}
}