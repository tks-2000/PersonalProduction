#include "stdafx.h"
#include "Shadow.h"

namespace render {
	namespace shadow {
		Shadow::Shadow()
		{
			


		}

		Shadow::~Shadow()
		{

		}

		void Shadow::Init()
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

			m_ligCameraPos = { 0.0f,1100.0f,1000.0f };
			m_ligCameraTarget = { 0.0f,0.0f,0.0f };
			m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
			m_lightCamera.SetWidth(1024.0f);
			m_lightCamera.SetHeight(1024.0f);
			m_isInitd = true;
		}

		void Shadow::Execute()
		{
			if (m_isInitd == false) {
				return;
			}
			//Quaternion qRot;

			//qRot.SetRotationDegY(0.5f);


			//qRot.Apply(m_ligCameraPos);


			LightCameraUpdate();



		}

		void Shadow::Render(RenderContext& rc)
		{
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
			m_lightCamera.SetFar(10000.0f);
			m_lightCamera.SetPosition(m_ligCameraPos);
			m_lightCamera.SetTarget(m_ligCameraTarget);
			Vector3 cameraDir = m_ligCameraTarget - m_ligCameraPos;
			cameraDir.Normalize();
			Vector3 cameraUp = Cross(cameraDir, m_lightCamera.GetRight());
			m_lightCamera.SetUp(m_ligCameraUp);
			//m_lightCamera.SetViewAngle(Math::DegToRad(m_ligCameraViewAngle));
			m_lightCamera.Update();
		}
	}
}