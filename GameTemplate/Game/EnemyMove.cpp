#include "stdafx.h"
#include "EnemyMove.h"

namespace {
	/// @brief �ʏ�̈ړ����x
	const float NORMAL_MOVE_VEROCITY = 30.0f;
	/// @brief �����ړ����x
	const float FAST_MOVE_VEROCITY = 40.0f;
	/// @brief �x���ړ����x
	const float SLOW_MOVE_VEROCITY = 20.0f;
	/// @brief ��~����
	const float MOVE_STOP_DISTANCE = 200.0f;
	/// @brief ��~����
	const float MOVE_START_TIME = 3.0f;
	/// @brief ���C��
	const float FRICTION = 0.1f;
	/// @brief �d��
	const float ENEMY_GRAVITY = 200.0f;
	/// @brief �G�̏Փ˔���̔��a
	const float ENEMY_COLLISION_RADIUS = 30.0f;
	/// @brief �G�̏Փ˔���̍���
	const float ENEMY_COLLISION_HEIGHT = 50.0f;
}

namespace mainGame {
	namespace enemy {
		Move::Move()
		{
			//���������ŊJ�n
			m_isInitd = false;
			m_moveTarget = g_vec3Zero;
		}

		Move::~Move()
		{

		}

		void Move::Init(Enemy* enemy)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�����擾
			m_enemy = enemy;
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			m_moveTarget = m_defensiveTarget->GetPosition();

			//�G�̎�ނɂ���đ��x��ς���
			switch(m_enemy->GetEnemyType())
			{
			case enEnemyTypeNormal: {
				m_moveVerocity = NORMAL_MOVE_VEROCITY;
			}break;
			case enEnemyTypePowerful: {
				m_moveVerocity = SLOW_MOVE_VEROCITY;
			}break;
			case enEnemyTypeFast: {
				m_moveVerocity = FAST_MOVE_VEROCITY;
			}break;
			default:
				return;
				break;
			}

			//�L�����N�^�[�R���g���[���[��������
			m_charaCon.Init(ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_HEIGHT,m_enemy->GetPosition());

			//����������
			m_isInitd = true;
		}

		const Vector3& Move::MoveExecute(Vector3& pos)
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return pos;
			}

			//���W�ƈړ��ڕW����ڕW�ւ̃x�N�g�����擾
			m_toTarget = m_moveTarget - pos;
			m_moveDirection = m_toTarget;

			//�c�����̈ړ�����������
			m_moveDirection.y = 0.0f;
			m_toTarget.y = 0.0f;

			//�ڕW�Ƃ̋����𑪂� 
			m_targetDistance = m_toTarget.Length();

			//���K��
			m_moveDirection.Normalize();

			//�ڕW�Ƃ̋�������~�����܂ŒB������c
			if (m_targetDistance <= MOVE_STOP_DISTANCE) {
				//�U�����J�n����
				m_enemy->SetState(enEnemyAttack);
				//���W�����̂܂ܕԂ�
				return pos;
			}

			//�ړ���������ړ����x�����߂�
			m_moveSpeed += m_moveDirection * m_moveVerocity;

			//�ړ����x�ɉ��������C�͂�������
			m_moveSpeed -= m_moveSpeed * FRICTION;

			//�d�͂�������
			m_moveSpeed.y -= ENEMY_GRAVITY;

			//�L�����N�^�[�R���g���[���[���g���č��W�����߂�
			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//���܂������W��Ԃ�
			return pos;
		}

		const Vector3& Move::IdleExecute(Vector3& pos)
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return pos;
			}

			//���݂̈ړ����x�ɖ��C�͂�������
			m_moveSpeed -= m_moveSpeed * FRICTION;

			//�d�͂�������
			m_moveSpeed.y -= ENEMY_GRAVITY;

			//�L�����N�^�[�R���g���[���[�ňړ�������
			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//�ړ����n�߂�܂ł̃^�C�}�[��i�߂�
			m_moveStartTimer += g_gameTime->GetFrameDeltaTime();

			//�^�C�}�[���ړ��J�n���Ԃ܂Ői�񂾂�c
			if (m_moveStartTimer >= MOVE_START_TIME) {

				//�^�C�}�[�����ɖ߂�
				m_moveStartTimer = 0.0f;

				//�X�e�[�^�X���ړ����ɕύX
				m_enemy->SetState(enEnemyMove);

				//�ړ������s
				pos = MoveExecute(pos);
			}

			//�ҋ@�������ʂ�Ԃ�
			return pos;
		}

		const Vector3& Move::MoveStop(Vector3& pos)
		{
			//�ړ��ڕW�������̍��W�ɐݒ�
			m_moveTarget = pos;

			//���݂̈ړ����x�ɖ��C�͂�������
			m_moveSpeed -= m_moveSpeed * FRICTION;

			//�d�͂�������
			m_moveSpeed.y -= ENEMY_GRAVITY;

			//�L�����N�^�[�R���g���[���[�ō��W�����߂�
			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			//��~�������ʂ�Ԃ�
			return pos;
		}
	}
}