#include "stdafx.h"
#include "MiniMap.h"
namespace mainGame {
	namespace ui {
		/// @brief �~�j�}�b�v�J�����̍��W
		const Vector3 MINI_MAP_CAMERA_POS = { 0.0f,2000.0f,0.0f };
		/// @brief �~�j�}�b�v�J�����̍���
		const float MINI_MAP_CAMERA_POS_HEIGHT = 1000.0f;
		/// @brief �~�j�}�b�v�J�����̉f������
		const float MINI_MAP_CAMERA_WIDTH = 1500.0f;
		/// @brief �~�j�}�b�v�J�����̉f���c��
		const float MINI_MAP_CAMERA_HEIGHT = 1500.0f;
		/// @brief �~�j�}�b�v�̉���
		const int MINI_MAP_WIDTH = 128;
		/// @brief �~�j�}�b�v�̏c��
		const int MINI_MAP_HEIGHT = 128;
		/// @brief �~�j�}�b�v�̍��W
		const Vector3 MINI_MAP_POS = { -500.0f,-220.0f,0.0f };
		/// @brief �~�j�}�b�v�̉��n�摜�̃t�@�C���p�X
		const char* MINI_MAP_BASE_FILEPATH = "Assets/Image/base_sprite_3.dds";
		/// @brief �~�j�}�b�v�̉��n�摜�̉���
		const int MINI_MAP_BASE_WIDTH = 300;
		/// @brief �~�j�}�b�v�̉��n�摜�̏c��
		const int MINI_MAP_BASE_HEIGHT = 520;
		/// @brief �~�j�}�b�v�̉��n�摜�̃J���[
		const Vector4 MINI_MAP_BASE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief �~�j�}�b�v�̘g�摜�̃t�@�C���p�X
		const char* MINI_MAP_FRAME_FILEPATH = "Assets/Image/base_sprite_4.dds";
		/// @brief �~�j�}�b�v�̘g�摜�̉���
		const int MINI_MAP_FRAME_WIDTH = 290;
		/// @brief �~�j�}�b�v�̘g�摜�̏c��
		const int MINI_MAP_FRAME_HEIGHT = 480;

		MiniMap::MiniMap()
		{
			//���������ŊJ�n
			m_isInitd = false;
			
		}

		MiniMap::~MiniMap()
		{
			//�~�j�}�b�v�`��Ɏg���������_�����O�^�[�Q�b�g������
			m_renderingEngine->DeleteExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP);
			m_renderingEngine->DeleteExpansionModelsRenderTarget(MINI_MAP_RENDER_GROUP);
			//�}�b�v�摜���폜
			DeleteGO(m_miniMapSprite);
			DeleteGO(m_miniMapBase);
			DeleteGO(m_miniMapFrame);
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
			m_renderingEngine = FindGO<render::RenderingEngine>(render::RENDERING_ENGINE_NAME);

			//�}�b�v���f���J�����̏�����
			m_mapCameraPos = MINI_MAP_CAMERA_POS;
			m_miniMapCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
			m_miniMapCamera.SetWidth(MINI_MAP_CAMERA_WIDTH);
			m_miniMapCamera.SetHeight(MINI_MAP_CAMERA_HEIGHT);
			m_miniMapCamera.SetTarget(m_player->GetPlayerPosition());
			m_miniMapCamera.SetUp(m_mapCameraUp);
			m_miniMapCamera.SetPosition(m_mapCameraPos);

			//�}�b�v�ɕ\�����郂�f����`�悷�郌���_�����O�^�[�Q�b�g���쐬
			m_miniMapRenderTarget.Create(
				MINI_MAP_WIDTH,
				MINI_MAP_HEIGHT,
				1,
				1,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				DXGI_FORMAT_D32_FLOAT
			);

			//�}�b�v�p�̃����_�����O�^�[�Q�b�g�ƃJ�����������_�����O�G���W���ɓn��
			m_renderingEngine->SetExpansionModlsRenderTarget(MINI_MAP_RENDER_GROUP, &m_miniMapRenderTarget);
			m_renderingEngine->SetExpansionModelDrawCamera(MINI_MAP_RENDER_GROUP, &m_miniMapCamera);

			//�~�j�}�b�v�̉��n�摜���쐬
			m_miniMapBase = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapBase->Init(MINI_MAP_BASE_FILEPATH, MINI_MAP_BASE_WIDTH, MINI_MAP_BASE_HEIGHT);
			m_miniMapBase->SetPosition(MINI_MAP_POS);
			m_miniMapBase->SetColor(MINI_MAP_BASE_COLOR);

			//�~�j�}�b�v�̘g�摜���쐬
			m_miniMapFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapFrame->Init(MINI_MAP_FRAME_FILEPATH, MINI_MAP_FRAME_WIDTH, MINI_MAP_FRAME_HEIGHT);
			m_miniMapFrame->SetPosition(MINI_MAP_POS);

			//�~�j�}�b�v�摜���쐬
			m_miniMapSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_miniMapSprite->InitTexture(&m_miniMapRenderTarget.GetRenderTargetTexture(), MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
			m_miniMapSprite->SetPosition(MINI_MAP_POS);

			//����������
			m_isInitd = true;
		}

		void MiniMap::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�摜���X�V
			m_miniMapSprite->Execute();
			m_miniMapBase->Execute();
			m_miniMapFrame->Execute();

			//�}�b�v�J�����̒����_�ƍ��W���X�V
			m_mapCameraPos = m_player->GetPlayerPosition();
			m_miniMapCamera.SetTarget(m_player->GetPlayerPosition());
			m_mapCameraPos.y += MINI_MAP_CAMERA_POS_HEIGHT;
			m_miniMapCamera.SetPosition(m_mapCameraPos);

			//�}�b�v�J�����̏�������X�V
			m_mapCameraUp = m_gameCamera->GetCameraGazePointPos() - m_gameCamera->GetCameraPos();
			m_mapCameraUp.Normalize();
			m_miniMapCamera.SetUp(m_mapCameraUp);

			//�}�b�v���f���J�������X�V
			m_miniMapCamera.Update();
		}

		void MiniMap::HideUI()
		{
			//�\�����Ă���UI��S�ē����ɂ���
			m_miniMapSprite->SetColor(render::COLORLESS);
			m_miniMapBase->SetColor(render::COLORLESS);
			m_miniMapFrame->SetColor(render::COLORLESS);
		}
	}
}