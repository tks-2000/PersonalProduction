#pragma once
#include "../../MiniEngine/RenderTarget.h"
#include "../../MiniEngine/Camera.h"

namespace render {
	namespace shadow {
		const int MAX_SHADOW_MODEL_NUM = 100;

		/// @brief �e�������s���N���X
		class Shadow
		{
		public:
			Shadow();
			~Shadow();
			void Init();
			void Execute();
			/// @brief �V���h�E�}�b�v���擾
			/// @return �V���h�E�}�b�v��const�Q��
			const RenderTarget& GetShadowMap() const { return m_shadowMap; }

			Texture& GetShadowMapTexture() { return m_shadowMap.GetRenderTargetTexture(); }

			/// @brief ���C�g�J�������擾
			/// @return ���C�g�J������const�Q��
			const Camera& GetLightCamera() const { return m_lightCamera; }

			const Matrix& GetLightCameraMatrix() { return m_lightCamera.GetViewProjectionMatrix(); }

			/// @brief ���C�g�J�����̍��W��ݒ�
			/// @param pos ���C�g�J�����ɐݒ肷����W��const�Q��
			void SetLightCameraPos(const Vector3& pos) { m_ligCameraPos = pos; }

			/// @brief ���C�g�J�����̍��W�����
			/// @return ���C�g�J�����̍��W��const�Q��
			const Vector3& GetLightCameraPos() { return m_ligCameraPos; }

			/// @brief ���C�g�J�����̒����_��ݒ�
			/// @param target ���C�g�J�����ɐݒ肷�钍���_���W��const�Q��
			void SetLightCameraTarget(const Vector3& target) { m_ligCameraTarget = target; }


			const Vector3& GetLightCameraTarget() { return m_ligCameraTarget; }

			/// @brief �e�𐶐����郂�f�����쐬
			/// @param shadowModel �e�𐶐����郂�f��
			void SetShadowModel(Model* shadowModel);

			/// @brief �e�𐶐����郂�f�����폜
			/// @param shadowModel �폜���郂�f���̃A�h���X
			void DeleteShadowModel(Model* shadowModel);

			void Render(RenderContext& rc);

			void CreateShadowMap(RenderContext& rc);
		private:
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �V���h�E�}�b�v
			RenderTarget m_shadowMap;
			/// @brief �J���[�o�b�t�@�̃N���A�J���[
			float m_clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
			/// @brief ���C�g�J����
			Camera m_lightCamera;
			/// @brief ���C�g�J�����̍��W
			Vector3 m_ligCameraPos = g_vec3One;
			/// @brief ���C�g�J�����̒����_
			Vector3 m_ligCameraTarget = g_vec3Zero;
			/// @brief ���C�g�J�����̏����
			Vector3 m_ligCameraUp = { 0.0f,0.0f,1.0f };
			/// @brief ���C�g�J�����̉�p
			float m_ligCameraViewAngle = 50.0f;
			/// @brief �V���h�E�}�b�v�ɏ������ރ��f���̍��v��
			int m_shadowModelSum = 0;
			/// @brief �V���h�E�}�b�v�����̂��߂̃��f��
			std::vector<Model*> m_shadowModel;
			/// @brief �V���h�E���f���̔ԍ�
			int m_shadowModelNum[MAX_SHADOW_MODEL_NUM] = { MAX_SHADOW_MODEL_NUM };

			/// @brief ���C�g�J�����̍X�V
			void LightCameraUpdate();
		};
	}
}

