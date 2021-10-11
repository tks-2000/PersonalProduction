#pragma once


namespace render {
	namespace postEffect {
		class GaussianBlur;
		class Bloom;

		/// @brief �|�X�g�G�t�F�N�g���܂Ƃ߂��N���X
		class PostEffect : public IGameObject
		{
		public:
			PostEffect();
			~PostEffect();
			bool Start();
			void Update();
			void Render(RenderContext& rc);

			/// @brief �|�X�g�G�t�F�N�g�����s����
			/// @param rc �����_�����O�R���e�L�X�g
			void Execute(RenderContext& rc);
			/// @brief �u���[��������
			/// @param rt �u���[�������郌���_�����O�^�[�Q�b�g�̃A�h���X
			/// @param blurWeight �u���[�̏d��
			void SetBlur(RenderTarget* rt, float blurWeight = 20.0f);

			/// @brief �u���[�̏d�݂�ݒ�
			/// @param blurWeight �ݒ肷��u���[�̏d��
			void SetBlurWeight(const float blurWeight) { m_blurWeight = blurWeight; }

			/// @brief �u���[����������
			/// @param rt �u���[���������郌���_�����O�^�[�Q�b�g�̃A�h���X
			void SetBloom(RenderTarget* rt);

		private:
			/// @brief �u���[�p�̃X�v���C�g
			Sprite m_blurSprite;
			/// @brief �u���[�p�̃X�v���C�g�̏��������
			SpriteInitData m_blurSpriteInitData;
			/// @brief �K�E�V�A���u���[
			GaussianBlur* m_gaussianBlur = nullptr;
			/// @brief �K�E�V�A���u���[�̏d��
			float m_blurWeight = 0.0f;
			/// @brief �u���[���s���t���O
			bool m_blurFlag = false;
			/// @brief �u���[��
			Bloom* m_bloom = nullptr;
			/// @brief �u���[�����s���t���O
			bool m_bloomFlag = false;
			/// @brief ���C�������_�����O�^�[�Q�b�g�̃A�h���X
			RenderTarget* m_mainRenderTargetAddress = nullptr;
		};
	}
}