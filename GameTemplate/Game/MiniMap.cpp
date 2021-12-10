#include "stdafx.h"
#include "MiniMap.h"
namespace mainGame {
	namespace map {

		const Vector3 MINI_MAP_CAMERA_POS = { 0.0f,2000.0f,0.0f };

		const Vector3 MINI_MAP_POS = { 500.0f,200.0f,0.0f };

		const float FRICTION = 20.0f;

		const Vector3 MINI_MAP_TPS_CAMERA_UP = { 0.0f,0.0f,1.0f };

		MiniMap::MiniMap()
		{
			//���������ŊJ�n
			m_isInitd = false;
			m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);
		}

		MiniMap::~MiniMap()
		{
		
			m_renderingEngine->DeleteExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP);
			m_renderingEngine->DeleteExpansionModelsRenderTarget(MINI_MAP_RENDER_GROUP);
			//�}�b�v�摜���폜
			DeleteGO(m_miniMapSprite);
		}

		void MiniMap::Init()
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�K�v�ȃf�[�^�������ė���
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);

			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//�}�b�v���f���J�����̏�����
			m_mapCameraPos = MINI_MAP_CAMERA_POS;
			m_miniMapCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
			m_miniMapCamera.SetWidth(1500.0f);
			m_miniMapCamera.SetHeight(1500.0f);
			m_miniMapCamera.SetTarget({ 0.0f, 0.0f, 0.0f });
			m_miniMapCamera.SetUp(m_mapCameraUp);
			m_miniMapCamera.SetPosition(m_mapCameraPos);

			//�}�b�v�ɕ\�����郂�f����`�悷�郌���_�����O�^�[�Q�b�g���쐬
			m_miniMapRenderTarget.Create(
				128,
				128,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			m_renderingEngine->SetExpansionModlsRenderTarget(MINI_MAP_RENDER_GROUP, &m_miniMapRenderTarget);

			//�}�b�v�摜���쐬
			m_miniMapSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapSprite->InitTexture(&m_miniMapRenderTarget.GetRenderTargetTexture(), 128, 128);
			m_miniMapSprite->SetRotation(m_spriteQrot);
			m_miniMapSprite->SetPosition(MINI_MAP_POS);

			//�����_�����O�G���W���Ɏ��g�̏���n��
			m_renderingEngine->SetExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP, &m_miniMapCamera);

			m_isInitd = true;
		}

		void MiniMap::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�J�����̊p�x����}�b�v�摜�̉�]�p�x�����߂�
			float angle = m_gameCamera->GetCameraYAngleAmount() - m_spriteAngle;

			if (m_gameCamera->GetCameraMode() == enCameraModeTps) {
				//m_mapCameraUp = MINI_MAP_TPS_CAMERA_UP;
				m_gameCamera->GetCameraYRot().Apply(m_mapCameraUp);
			}
			else {
				Vector3 up = m_gameCamera->GetCameraTarget() - m_gameCamera->GetCameraPos();
				up.y = 0.0f;
				up.Normalize();
				m_mapCameraUp = up;
			}

			//�J�����̊p�x�Ƃ̍����J�����̈ړ���~�����ȉ���������c
			if (angle < m_gameCamera->GetCameraMoveStopDistance()) {
				//�p�x�����̂܂ܑ���
				m_spriteAngle += angle;
			}
			//�����łȂ��Ȃ�c
			else {
				//�p�x�ɖ��C�͂����������𑫂�
				m_spriteAngle += angle / m_gameCamera->GetCameraFriction();
			}

			//�摜�̉�]�����߂�
			m_spriteQrot.SetRotationZ(m_spriteAngle);

			//�摜���X�V
			//m_miniMapSprite->SetRotation(m_spriteQrot);
			m_miniMapSprite->Execute();

			m_miniMapPos = m_player->GetPlayerPosition();
			m_miniMapCamera.SetTarget(m_player->GetPlayerPosition());
			m_miniMapPos.y += 1000.0f;

			m_miniMapCamera.SetPosition(m_miniMapPos);
			m_miniMapCamera.SetUp(m_mapCameraUp);
			//�}�b�v���f���J�������X�V
			m_miniMapCamera.Update();
		}

		void MiniMap::MapRender(RenderContext& rc)
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�}�b�v�p�̃����_�����O�^�[�Q�b�g��ݒ�
			rc.WaitUntilToPossibleSetRenderTarget(m_miniMapRenderTarget);
			rc.SetRenderTargetAndViewport(m_miniMapRenderTarget);
			rc.ClearRenderTargetView(m_miniMapRenderTarget);

			//�}�b�v�p�̃��f����S�ăh���[����
			for (int modelNum = 0; modelNum < m_drawModels.size(); modelNum++) {
				m_drawModels[modelNum]->Draw(rc, m_miniMapCamera);
			}

			//�����_�����O�^�[�Q�b�g�֏������ݏI��
			rc.WaitUntilFinishDrawingToRenderTarget(m_miniMapRenderTarget);

			// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
			rc.SetRenderTarget(
				g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
				g_graphicsEngine->GetCurrentFrameBuffuerDSV()
			);
			rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
		}
	}
}