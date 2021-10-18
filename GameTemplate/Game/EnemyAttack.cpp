#include "stdafx.h"
#include "EnemyAttack.h"


namespace {
	/// @brief �ʏ�̍U����
	const int NORMAL_ATTACK_POWER = 2;
	/// @brief �����U����
	const int POWERFUL_ATTACK_POWER = 3;
	/// @brief �ア�U����
	const int WEAK_ATTTACK_POWER = 1;
	/// @brief �U���Ԋu
	const float ATTACK_INTERVAL = 1.0f;
}

namespace mainGame {
	namespace enemy {
		Attack::Attack()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Attack::~Attack()
		{

		}

		void Attack::Init(Enemy* enemy)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			m_enemy = enemy;

			switch (m_enemy->GetEnemyType())
			{
			case enEnemyTypeNormal: {
				m_attackPower = NORMAL_ATTACK_POWER;
			}break;
			case enEnemyTypePowerful: {
				m_attackPower = POWERFUL_ATTACK_POWER;
			}break;
			case enEnemyTypeFast: {
				m_attackPower = WEAK_ATTTACK_POWER;
			}break;
			default:
				return;
				break;
			}

			//�U���ڕW�̏�������
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			//����������
			m_isInitd = true;
		}

		void Attack::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�U������܂ł̃^�C�}�[�����Z
			m_attackTimer += g_gameTime->GetFrameDeltaTime();

			//�U���Ԋu�܂Ń^�C�}�[���i�񂾂�c
			if (m_attackTimer >= ATTACK_INTERVAL) {
				//�U�������s
				ExecuteAttack();
				//�^�C�}�[��0�ɖ߂�
				m_attackTimer = 0.0f;
			}

		}

		void Attack::ExecuteAttack()
		{
			//�h�q�ΏۂɍU����������
			m_defensiveTarget->ReceiveDamage(m_attackPower);
		}

	}
}