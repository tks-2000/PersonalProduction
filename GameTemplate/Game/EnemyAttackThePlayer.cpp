#include "stdafx.h"
#include "EnemyAttackThePlayer.h"

namespace mainGame {
	namespace enemy {

		const float ATTACK_THE_PLAYER_START_TIME = 1.0f;

		const float ATTACK_THE_PLAYER_END_TIME = 2.0f;

		const float ATTACK_THE_PLAYER_DISTANCE = 200.0f;

		const float ATTACK_THE_PLAYER_ANGLE_MATCH_RATE = 0.0f;

		AttackThePlayer::AttackThePlayer()
		{

		}

		AttackThePlayer::~AttackThePlayer()
		{

		}

		void AttackThePlayer::Init(Enemy* enemy)
		{
			m_enemy = enemy;

			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_isInitd = true;
		}

		void AttackThePlayer::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (m_enemy->GetState() == enEnemyDamage) {
				m_attackTimer = 0.0f;
				return;
			}


			if (m_enemy->GetState() == enEnemyAttack) {

				m_attackTimer += g_gameTime->GetFrameDeltaTime();

				Vector3 distance = m_player->GetPlayerPosition() - m_enemy->GetPosition();

				if (m_attackTimer >= ATTACK_THE_PLAYER_START_TIME) {
					if (distance.Length() <= ATTACK_THE_PLAYER_DISTANCE) {
						distance.Normalize();
						float rate = Dot(distance, m_enemy->GetDirection());

						if (rate >= ATTACK_THE_PLAYER_ANGLE_MATCH_RATE) {
							DamageThePlayer();

						}
					}
				}
				if (m_attackTimer >= ATTACK_THE_PLAYER_END_TIME) {
					m_attackTimer = 0.0f;
				}

				if (distance.Length() >= ATTACK_THE_PLAYER_DISTANCE && m_attackTimer == 0.0f) {
					m_enemy->SetState(enEnemyMove);
				}
				
			}
			else {
				m_attackTimer = 0.0f;
			}
		}

		void AttackThePlayer::DamageThePlayer()
		{
			if (m_player->IsInvincible() == true) {
				return;
			}
			m_player->SetPlayerState(player::enPlayerDamage);
			/*CSoundSource* attackSe = NewGO<CSoundSource>(PRIORITY_VERYLOW);
			attackSe->Init(L"Assets/sound/se/WeakCollide.wav");
			attackSe->Play(false);*/
		}
	}
}