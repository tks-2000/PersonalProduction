#include "stdafx.h"
#include "SpriteRender.h"

namespace {
	const float STOP_DISTANCE_LENGTH = 1.0f;
}

namespace render {
	namespace sprite {

		SpriteRender::SpriteRender()
		{
			m_renderingEngine = FindGO<RenderingEngine>(RENDERING_ENGINE_NAME);
		}

		SpriteRender::~SpriteRender()
		{
			m_renderingEngine->DeleteSprite(&m_sprite);
		}

		void SpriteRender::Init(const char* spriteFilePath, int width, int height)
		{
			//���ɏ���������Ă�������s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			m_spriteInitData.m_ddsFilePath[0] = spriteFilePath;
			m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
			m_spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

			m_spriteInitData.m_width = width;
			m_spriteInitData.m_height = height;
			m_spriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
			m_sprite.Init(m_spriteInitData);

			//�����_�����O�G���W���ɃX�v���C�g��n��
			m_renderingEngine->SetDrawSprite(&m_sprite);
			//����������
			m_isInitd = true;
		}

		void SpriteRender::InitTexture(Texture* texture, int width, int height)
		{
			//���ɏ���������Ă�������s���Ȃ�
			if (m_isInitd == true) {
				return;
			}
			m_spriteInitData.m_textures[0] = texture;
			m_spriteInitData.m_width = width;
			m_spriteInitData.m_height = height;
			m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
			m_spriteInitData.m_alphaBlendMode = AlphaBlendMode_Trans;

			m_sprite.Init(m_spriteInitData);

			//�����_�����O�G���W���ɃX�v���C�g��n��
			m_renderingEngine->SetDrawSprite(&m_sprite);
			//����������
			m_isInitd = true;
		}

		bool SpriteRender::IsOpacity()
		{
			if (m_color.w >= 1.0f) {
				return true;
			}
			else {
				return false;
			}
		}

		bool SpriteRender::IsTransparent()
		{
			if (m_color.w <= 1.0f) {
				return true;
			}
			else {
				return false;
			}
		}

		void SpriteRender::Fade()
		{
			if (m_fadeInFlag == true) {
				m_color.w += m_fadeRate * g_gameTime->GetFrameDeltaTime();
			}
			if (m_fadeOutFlag == true) {
				m_color.w -= m_fadeRate * g_gameTime->GetFrameDeltaTime();
			}
			if (m_color.w > 1.0f) {
				m_color.w = 1.0f;
				m_fadeInFlag = false;
			}
			if (m_color.w < 0.0f) {
				m_color.w = 0.0f;
				m_fadeOutFlag = false;
			}
		}

		void SpriteRender::MoveStart(Vector3 targetPos, float velocity)
		{
			m_targetPos = targetPos;
			m_moveSpeed = m_targetPos - m_position;
			m_moveSpeed.Normalize();
			m_moveSpeed *= velocity;
			m_moveFlag = true;
		}

		void SpriteRender::Move()
		{
			/// @brief �ړ�����O�̎����̍��W���L������
			m_previousPos = m_position;

			m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();

			/// @brief �ڕW�n�_��ʂ�߂�����ڕW�n�_�ɍ��킹��
			if (m_previousPos.x < m_targetPos.x) {
				if (m_targetPos.x <= m_position.x) {
					m_position.x = m_targetPos.x;
				}
			}
			if (m_previousPos.x > m_targetPos.x) {
				if (m_targetPos.x >= m_position.x) {
					m_position.x = m_targetPos.x;
				}
			}

			if (m_previousPos.y < m_targetPos.y) {
				if (m_targetPos.y <= m_position.y) {
					m_position.y = m_targetPos.y;
				}
			}
			if (m_previousPos.y > m_targetPos.y) {
				if (m_targetPos.y >= m_position.y) {
					m_position.y = m_targetPos.y;
				}
			}

			if (m_previousPos.z < m_targetPos.z) {
				if (m_targetPos.z <= m_position.z) {
					m_position.z = m_targetPos.z;
				}
			}
			if (m_previousPos.z > m_targetPos.z) {
				if (m_targetPos.z >= m_position.z) {
					m_position.z = m_targetPos.z;
				}
			}

			/// @brief �ڕW�n�_�ɒ�������ړ����I���
			if (m_position.x == m_targetPos.x && m_position.y == m_targetPos.y && m_position.z == m_targetPos.z) {
				m_moveFlag = false;
			}
		}

		void SpriteRender::Execute()
		{
			//���������Ȃ珈�����s��Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�t�F�[�h�����s
			Fade();

			if (m_moveFlag == true) {
				Move();
			}

			//�J���[��K�p
			m_sprite.ColorUpdate(m_color);
			//�X�v���C�g�̃��[���h�s����X�V
			m_sprite.Update(m_position, m_qRot, m_scale, m_pivot);
		}
	}
}