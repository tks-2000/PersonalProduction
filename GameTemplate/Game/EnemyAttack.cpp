#include "stdafx.h"
#include "EnemyAttack.h"


namespace {
	/// @brief �U����
	const int NORMAL_ATTACK_POWER = 1;
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

		void Attack::Init()
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�����p�����[�^�[�Ə�������
			m_attackPower = NORMAL_ATTACK_POWER;
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