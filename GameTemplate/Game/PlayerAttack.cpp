#include "stdafx.h"
#include "PlayerAttack.h"

namespace {
	/// @brief “G‚É—^‚¦‚éƒ_ƒ[ƒW
	const int NORMAL_ATTACK_DAMAGE = 3;
	/// @brief “G‚É—^‚¦‚éÕŒ‚—Í
	const float NORMAL_IMPACT_FORCE = 3000.0f;
	/// @brief UŒ‚”ÍˆÍ
	const float ATTACK_RANGE = 200.0f;

	const float ATTACK_POSSIBLE_MATCH_RATE = 0.0f;

}

namespace mainGame {
	namespace player {
		Attack::Attack()
		{
			//–¢‰Šú‰»‚ÅŠJn
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
			//‰Šú‰»Ï‚İ‚È‚çÀs‚µ‚È‚¢
			if (m_isInitd == true) {
				return;
			}

			//î•ñ‚ğ“üè
			m_player = pl;
			m_gameCamera = FindGO<GameCamera>(GAME_CAMERA_NAME);
			m_attackPower = NORMAL_IMPACT_FORCE;
			m_attackRange = ATTACK_RANGE;

			//‰Šú‰»Š®—¹
			m_isInitd = true;
		}

		void Attack::Execute()
		{
			//–¢‰Šú‰»‚È‚çÀs‚µ‚È‚¢
			if (m_isInitd == false) {
				return;
			}

			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonA)) {
				MeleeAttack();
			}
			else if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRB1))
			{
				BulletFiring();
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
				m_bulletNum--;
			}
		}

		void Attack::MeleeAttack()
		{
			//“G‚Ì”‚¾‚¯Às‚·‚é
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				//“G‚Æ‚Ì‹——£‚ğ‘ª‚é
				Vector3 toEnemyPos = m_enemys[enemyNum]->GetPosition() - m_player->GetPlayerPosition();

				//UŒ‚‰Â”\‚È‹——£‚¾‚Á‚½ê‡c
				if (toEnemyPos.Length() < m_attackRange) {

					//“G‚Ö‚ÌƒxƒNƒgƒ‹‚ÅÕŒ‚‚ğ—^‚¦‚é
					toEnemyPos.Normalize();

					float matchRate = Dot(toEnemyPos, m_player->GetPlayerDirection());

					if (matchRate < ATTACK_POSSIBLE_MATCH_RATE) {
						return;
					}

					m_enemys[enemyNum]->SetMoveSpeed(toEnemyPos * m_attackPower);

					//“G‚Éƒ_ƒ[ƒW‚ğ—^‚¦‚é
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
			m_bullets[m_bulletNum]->Init(this, &m_enemys, startPos,targetPos);
			m_bulletNum++;

		}

		void Attack::BulletExecution()
		{
			for (int bulletNum = 0; bulletNum < m_bullets.size(); bulletNum++) {
				m_bullets[bulletNum]->Execution();
			}

		}
	}
}