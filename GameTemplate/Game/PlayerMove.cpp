#include "stdafx.h"
#include "PlayerMove.h"

namespace {
	/// @brief �������x
	const float WARK_VEROCITY = 10.0f;
	/// @brief ���鑬�x
	const float RUN_VEROCITY = 20.0f;
	/// @brief ���C��
	const float FRICTION = 0.03f;
	/// @brief ��~����ړ����x�̑傫��
	const float STOP_MOVE_LENGTH = 10.0f;
	/// @brief �ҋ@��ԂɂȂ�ړ����x�̑傫��
	const float IDLE_MOVE_LENGTH = 30.0f;
	/// @brief �v���C���[�̏d��
	const float PLAYER_GRAVITY = 30.0f;
	/// @brief �v���C���[�̏Փ˔���̔��a
	const float PLAYER_COLLISION_RADIUS = 30.0f;
	/// @brief �v���C���[�̏Փ˔���̍���
	const float PLAYER_COLLISION_HEIGHT = 50.0f;
	/// @brief ����{�^��
	const EnButton RUN_BUTTON = enButtonRB2;
}

namespace mainGame {
	namespace player {
		Move::Move()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Move::~Move()
		{

		}

		void Move::Init(Player* pl)
		{
			//�f�[�^���擾
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_player = pl;

			//�L�����N�^�[�R���g���[���[��������
			m_charaCon.Init(PLAYER_COLLISION_RADIUS, PLAYER_COLLISION_HEIGHT, m_player->GetPlayerPosition());
			m_gravity = PLAYER_GRAVITY;

			//����������
			m_isInitd = true;
		}

		void Move::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//���X�e�B�b�N���͂��󂯎��
			m_LStickX = g_pad[PLAYER1_CONTROLLER_NUM]->GetLStickXF();
			m_LStickY = g_pad[PLAYER1_CONTROLLER_NUM]->GetLStickYF();

			if (m_player->GetPlayerStatus() != enPlayerAttack && m_player->GetPlayerStatus() != enPlayerDamage) {

				//���X�e�B�b�N���͂�����΁c
				if (m_LStickX != 0.0f || m_LStickY != 0.0f) {
					//�����Ă���΁c
					if (g_pad[0]->IsPress(RUN_BUTTON)) {
						//�v���C���[�𑖂��ԂɕύX
						m_player->SetPlayerState(enPlayerRun);
					}
					//�����Ă��Ȃ��Ȃ�c
					else {
						//�v���C���[�������ԂɕύX 
						m_player->SetPlayerState(enPlayerWark);
					}
				}
				//���X�e�B�b�N���͂�������΁c
				else {
					//�v���C���[��ҋ@��ԂɕύX
					m_player->SetPlayerState(enPlayerIdle);
				}
			}

			//�v���C���[�̏�Ԃŏ����𕪂���
			switch (m_player->GetPlayerStatus())
			{
				//�ҋ@
			case enPlayerIdle: {
				IdleExecute();
			}break;
				//����
			case enPlayerWark: {
				MoveExecute(WARK_VEROCITY + m_addVerocity);
			}break;
				//����
			case enPlayerRun: {
				MoveExecute(RUN_VEROCITY + m_addVerocity);
			}break;
			case enPlayerAttack: {
				IdleExecute();
			}break;
				//
			case enPlayerDamage: {
				IdleExecute();
			}break;
			default:
				break;
			}
		}

		void Move::IdleExecute()
		{

			//��~���ł����C�͉�����
			m_moveSpeed = ApplyFriction(m_moveSpeed);

			//Y�����̈ړ����x�𔲂������x���擾
			Vector3 moveSpeedXZ = m_moveSpeed;
			moveSpeedXZ.y = 0.0f;

			//Y���������̈ړ����x����~���x�ȉ��ɂȂ�����c
			if (moveSpeedXZ.Length() < STOP_MOVE_LENGTH) {
				//Y�����ȊO�̈ړ����x��0�ɂ���
				m_moveSpeed.x = 0.0f;
				m_moveSpeed.z = 0.0f;
			}

			//�d�͂�������
			m_moveSpeed.y -= m_gravity;

			//�ړ����x������W�����߂�
			m_player->SetPlayerPosition(m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime()));

			return;
		}

		void Move::MoveExecute(const float moveVerocity)
		{
			
			//�X�e�B�b�N���͂ƃJ�����̕����ňړ����������߂�
			m_moveDirection =  m_gameCamera->GetCameraRight() * m_LStickX;
			m_moveDirection += m_gameCamera->GetCameraForward() * m_LStickY;

			//���������̈ړ������𖳂���
			m_moveDirection.y = 0.0f;

			//���K��
			m_moveDirection.Normalize();
			
			//�ړ������ɑ��x����Z���Ĉړ����x�����߂�
			m_moveSpeed += m_moveDirection * moveVerocity;
			
			//�ړ����x�ɖ��C�͂�������
			m_moveSpeed = ApplyFriction(m_moveSpeed);

			//�d�͂�������
			m_moveSpeed.y -= m_gravity;

			//�ړ����x������W��ݒ�
			m_player->SetPlayerPosition(m_charaCon.Execute(m_moveSpeed,g_gameTime->GetFrameDeltaTime()));

			return;
		}

		const Vector3& Move::ApplyFriction(Vector3& speed)
		{
			//�ړ����x�ɉ��������C�͂����߂�
			m_friction = speed * FRICTION;

			//�ړ����x���疀�C�͂�����
			speed -= m_friction;

			//���C�͂����������x��Ԃ�
			return speed;
		}
	}
}