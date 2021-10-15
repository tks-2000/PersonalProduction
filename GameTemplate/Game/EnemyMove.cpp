#include "stdafx.h"
#include "EnemyMove.h"

namespace {
	/// @brief �ʏ�̈ړ����x
	const float NORMAL_MOVE_VEROCITY = 5.0f;
	/// @brief �����ړ����x
	const float FAST_MOVE_VEROCITY = 7.5f;
	/// @brief �x���ړ����x
	const float SLOW_MOVE_VEROCITY = 2.5f;
	/// @brief ��~����
	const float MOVE_STOP_DISTANCE = 200.0f;
	/// @brief ��~����
	const float MOVE_START_TIME = 3.0f;
	/// @brief ���C��
	const float FRICTION = 0.03f;
	/// @brief �d��
	const float ENEMY_GRAVITY = 30.0f;
	/// @brief �G�̏Փ˔���̔��a
	const float ENEMY_COLLISION_RADIUS = 50.0f;
	/// @brief �G�̏Փ˔���̍���
	const float ENEMY_COLLISION_HEIGHT = 100.0f;
}

namespace mainGame {
	namespace enemy {
		Move::Move()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Move::~Move()
		{

		}

		void Move::Init(const EnEnemyType& type, const Vector3& pos)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			switch(type)
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

			//�����擾
			m_enemy = FindGO<Enemy>(ENEMY_NAME);
			//�L�����N�^�[�R���g���[���[��������
			m_charaCon.Init(ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_HEIGHT,pos);

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
			m_moveDirection = m_toTarget = m_moveTarget - pos;

			//�ڕW�Ƃ̋����𑪂� 
			m_targetDistance = m_toTarget.Length();

			//�c�����̈ړ�����������
			m_moveDirection.y = 0.0f;

			//���K��
			m_moveDirection.Normalize();

			//�ڕW�ւ̈ړ��������Ȃ��E�ڕW�Ƃ̋�������~�����܂ŒB������c
			if (m_moveDirection.Length() == 0.0f ||
				m_targetDistance <= MOVE_STOP_DISTANCE) {
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