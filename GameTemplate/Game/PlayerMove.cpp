#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief ���x
	const float MOVE_VEROCITY = 0.2f;
	/// @brief ���C��
	const float FRICTION = 0.03f;
	/// @brief ��~����ړ����x�̑傫��
	const float STOP_MOVE_LENGTH = 0.1f;
	/// @brief �ҋ@��ԂɂȂ�ړ����x�̑傫��
	const float IDLE_MOVE_LENGTH = 0.6f;
}

namespace MainGame {
	namespace Player {
		Move::Move()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Move::~Move()
		{

		}

		void Move::Init()
		{
			//�f�[�^���擾
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_player = FindGO<Player>(PLAYER_NAME);

			//����������
			m_isInitd = true;
		}

		const Vector3& Move::MoveExecute()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return g_vec3Zero;
			}

			//���X�e�B�b�N���͂��󂯎��
			m_LStickX = g_pad[0]->GetLStickXF();
			m_LStickY = g_pad[0]->GetLStickYF();

			//�X�e�B�b�N���͂ƃJ�����̕����ňړ����������߂�
			m_moveDirection =  m_gameCamera->GetCameraRight() * m_LStickX;
			m_moveDirection += m_gameCamera->GetCameraForward() * m_LStickY;

			//���������̈ړ������𖳂���
			m_moveDirection.y = 0.0f;

			//���K��
			m_moveDirection.Normalize();
			
			//�ړ������ɑ��x����Z���Ĉړ����x�����߂�
			m_moveSpeed += m_moveDirection * MOVE_VEROCITY;
				
			//�ړ����x�ɉ��������C�͂����߂�
			m_friction = m_moveSpeed * FRICTION;

			//�ړ����x���疀�C�͂�����
			m_moveSpeed -= m_friction;
			
			//�ړ����x����~���x�ȉ��ɂȂ�����c
			if (m_moveSpeed.Length() < STOP_MOVE_LENGTH) {
				//�ړ����x��0�ɂ���
				m_moveSpeed = g_vec3Zero;
				//�ҋ@��ԂɈڍs
				m_player->SetPlayerState(enPlayerIdle);
				//���݂̍��W��n��
				return m_position;
			}

			//���W�Ɉړ����x��n��
			m_position += m_moveSpeed;

			//�ړ����x���ҋ@���x�ɒB������c
			if (m_moveSpeed.Length() < IDLE_MOVE_LENGTH) {
				//�ҋ@��ԂɈڍs
				m_player->SetPlayerState(enPlayerIdle);
			}
			//�����łȂ��Ȃ�c
			else {
				//������ԂɈڍs
				m_player->SetPlayerState(enPlayerWark);
			}

			//�ړ���̍��W��Ԃ�
			return m_position;
		}
	}
}