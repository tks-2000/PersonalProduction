#include "stdafx.h"
#include "PlayerAttack.h"

namespace {
	/// @brief �G�ɗ^����_���[�W
	const int NORMAL_ATTACK_DAMAGE = 1;
	/// @brief �G�ɗ^����Ռ���
	const float NORMAL_ATTACK_POWER = 5000.0f;
	/// @brief �U���͈�
	const float ATTACK_RANGE = 200.0f;

}

namespace mainGame {
	namespace player {
		Attack::Attack()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Attack::~Attack()
		{

		}

		void Attack::Init(Player* pl)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�������
			m_player = pl;
			m_attackPower = NORMAL_ATTACK_POWER;
			m_attackRange = ATTACK_RANGE;

			//����������
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//�U���\�ȋ����������ꍇ�c
				if (toEnemyPos.Length() < m_attackRange) {

					//�G�ւ̃x�N�g���ŏՌ���^����
					toEnemyPos.Normalize();
					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);

					//�G�Ƀ_���[�W��^����
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::DeleteEnemyData(enemy::Enemy* enemy)
		{
			std::vector<enemy::Enemy*>::iterator it;
			it = std::find(
				m_enemys.begin(),
				m_enemys.end(),
				enemy
			);
			if (it != m_enemys.end()) {
				m_enemys.erase(it);
			}
		}
	}
}