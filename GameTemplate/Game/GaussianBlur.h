#pragma once

namespace render {
	namespace postEffect {
		/// @brief �K�E�V�A���u���[���s���N���X
		class GaussianBlur : public IGameObject
		{
		public:
			GaussianBlur();
			~GaussianBlur();
			bool Start();
			void Update();
			/// @brief ���������s��
			/// @param originalTexture �K�E�V�A���u���[��������e�N�X�`���̃A�h���X
			void Init(Texture* originalTexture);

			/// @brief �K�E�V�A���u���[�����s
			/// @param rc �����_�����O�R���e�L�X�g
			/// @param blorPower �u���[�̋���
			void ExecuteOnGPU(RenderContext& rc, float blorPower);

			/// @brief �u���[���������e�N�X�`�����擾
			/// @return �u���[���K�p���ꂽ�e�N�X�`��
			Texture& GetBlurTexture()
			{
				return m_yBlurRenderTarget.GetRenderTargetTexture();
			}
		private:
			//�O���Ŏg��Ȃ������o�֐�

			/// @brief �����_�����O�^�[�Q�b�g��������
			void InitRenderTargets();
			/// @brief �X�v���C�g��������
			void InitSprites();
			/// @brief �d�݃e�[�u�����X�V����
			/// @param blurPower �u���[�̏d��
			void UpdateWeightsTable(float blurPower);

			//�������烁���o�ϐ�

			/// @brief �d�݂̐�
			enum { NUM_WEIGHTS = 8 };
			/// @brief �d�݃e�[�u��
			float m_weights[NUM_WEIGHTS];
			/// @brief �I���W�i���e�N�X�`��
			Texture* m_originalTexture = nullptr;
			/// @brief ���u���[�摜��`�悷�郌���_�����O�^�[�Q�b�g
			RenderTarget m_xBlurRenderTarget;
			/// @brief �c�u���[�摜��`�悷�郌���_�����O�^�[�Q�b�g
			RenderTarget m_yBlurRenderTarget;
			/// @brief ���u���[�摜��`�悷�邽�߂̃X�v���C�g
			Sprite m_xBlurSprite;
			/// @brief �c�u���[�摜��`�悷�邽�߂̃X�v���C�g
			Sprite m_yBlurSprite;
		};
	}
}