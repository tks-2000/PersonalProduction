#include "stdafx.h"
#include "PlayerAttack.h"

namespace {

	const float CHARGE_MELEE_ATTACK_TIME = 1.0f;
	/// @brief �G�ɗ^����_���[�W
	const int NORMAL_ATTACK_DAMAGE = 3;
	/// @brief �G�ɗ^����Ռ���
	const float NORMAL_IMPACT_FORCE = 3000.0f;
	/// @brief �G�ɗ^���鋭�͂ȏՌ���
	const float STRONG_IMPACT_FORCE = 6000.0f;
	/// @brief �U���͈�
	const float ATTACK_RANGE = 200.0f;
	/// @brief �U���\�ȕ�����v��
	const float ATTACK_POSSIBLE_MATCH_RATE = 0.0f;
	/// @brief �ʏ�̒e�ۂ̍ő及����
	const int NORMAL_MAX_BULLET_NUM = 10;
	/// @brief �ʏ�̒e�ۂ̍đ��U����
	const float NORMAL_BULLET_RELOAD_TIME = 3.0f;
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
			m_enemys.clear();

			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				DeleteGO(m_bullets[bulletNum]);
			}

			m_bullets.clear();
		}

		void Attack::Init(Player* pl)
		{
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�������
			m_player = pl;
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_attackPower = NORMAL_IMPACT_FORCE;
			m_attackRange = ATTACK_RANGE;
			m_chargeMeleeAttackTime = CHARGE_MELEE_ATTACK_TIME;

			m_bulletReloadTimer = 0.0f;
			m_bulletReloadTime = NORMAL_BULLET_RELOAD_TIME;
			m_maxBulletNum = NORMAL_MAX_BULLET_NUM;
			m_remainingBullets = m_maxBulletNum;


			//����������
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//A�{�^���ŋߐڍU��
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA)) {
				m_isMeleeAttackButtonHold = true;
			}

			if (m_isMeleeAttackButtonHold == true) {
				m_chargeMeleeAttackTimer += g_gameTime->GetFrameDeltaTime();

				if (m_chargeMeleeAttackTimer >= m_chargeMeleeAttackTime) {
					m_isFollCharge = true;
				}

				if (!g_pad[PLAYER1_CONTROLLER_NUM]->IsPress(enButtonA)) {
					if (m_isFollCharge == true) {
						ChargeMeleeAttack();
					}
					else {
						MeleeAttack();
						
					}
					m_isMeleeAttackButtonHold = false;
					m_chargeMeleeAttackTimer = 0.0f;
					m_isFollCharge = false;
				}
			}
			
			//RB1�{�^���Œe�ۂ𔭎�
			else if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB1))
			{
				//�c�e������Δ���
				if (m_remainingBullets > 0) {
					BulletFiring();
				}
			}
			//�c�e���Ȃ��ꍇ�c
			if (m_remainingBullets <= 0) {
				//�����[�h���Ԃ�i�߂�
				m_bulletReloadTimer += g_gameTime->GetFrameDeltaTime();
				//�����[�h�������ԂɒB������c
				if (m_bulletReloadTimer >= m_bulletReloadTime) {
					//�c�e���ő�l�܂ŉ�
					m_remainingBullets = m_maxBulletNum;
					m_bulletReloadTimer = 0.0f;
				}
			}

			BulletExecution();
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

		void Attack::DeleteBullet(Bullet* bullet)
		{
			std::vector<Bullet*>::iterator it;
			it = std::find(
				m_bullets.begin(),
				m_bullets.end(),
				bullet
			);
			if (it != m_bullets.end()) {
				m_bullets.erase(it);
			}
		}

		void Attack::MeleeAttack()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//�U���\�ȋ����������ꍇ�c
				if (toEnemyPos.Length() < m_attackRange) {

					//�G�ւ̃x�N�g���ŏՌ���^����
					toEnemyPos.Normalize();

					float matchRate = Dot(toEnemyPos, m_player->GetPlayerDirection());

					if (matchRate < ATTACK_POSSIBLE_MATCH_RATE) {
						return;
					}

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);

					//�G�Ƀ_���[�W��^����
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::ChargeMeleeAttack()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//�U���\�ȋ����������ꍇ�c
				if (toEnemyPos.Length() < m_attackRange) {

					//�G�ւ̃x�N�g���ŏՌ���^����
					toEnemyPos.Normalize();

					

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * STRONG_IMPACT_FORCE);

					//�G�Ƀ_���[�W��^����
					m_enemys[enemyNum]->SetState(enemy::enEnemyDamage);
					m_enemys[enemyNum]->ReceiveDamage(NORMAL_ATTACK_DAMAGE);
				}
			}
		}

		void Attack::BulletFiring()
		{
			m_bullets.push_back(NewGO<Bullet>(PRIORITY_VERYLOW));
			Vector3 startPos = m_player->GetPlayerPosition();
			startPos.y += 50.0f;
			Vector3 targetPos;
			if (m_gameCamera->GetCameraMode() == enCameraModeFps) {
				targetPos = m_gameCamera->GetCameraGazePointPos();
			}
			else {
				targetPos = m_player->GetPlayerPosition() + m_player->GetPlayerDirection();
				targetPos.y = startPos.y;
			}
			m_bullets[m_bullets.size() - 1]->Init(this, &m_enemys, startPos, targetPos);
			m_remainingBullets--;
		}

		void Attack::BulletExecution()
		{
			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				m_bullets[bulletNum]->Execution();
			}

		}
	}
}