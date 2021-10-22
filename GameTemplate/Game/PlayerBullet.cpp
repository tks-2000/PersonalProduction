#include "stdafx.h"
#include "PlayerBullet.h"

namespace mainGame {
	namespace player {

		const float BULLET_VEROCITY = 3.0f;

		const float ENEMY_COLLISION_DISTANCE = 100.0f;

		const float DELETE_MOVE_DISTANCE = 3000.0f;

		Bullet::Bullet()
		{
			m_isInitd = false;
		}

		Bullet::~Bullet()
		{
			DeleteGO(m_bulletModel);
		}

		void Bullet::Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos, const Vector3& target)
		{
			if (m_isInitd == true) {
				return;
			}

			m_playerAttack = plAttack;

			m_enemys = enemys;

			m_bulletModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bulletModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_startPos = pos;

			m_startPos.y += 50.0f;

			m_position = m_startPos;

			m_target = target;

			m_moveDirection = m_target - m_startPos;

			m_isInitd = true;
		}

		void Bullet::Execution()
		{
			if (m_isInitd == false) {
				return;
			}
			m_enemys->size();

			MoveExecution();
			EnemyCollision();
			m_bulletModel->SetPosition(m_position);
			m_bulletModel->Execution();
		}

		void Bullet::MoveExecution()
		{
			m_moveSpeed = m_moveDirection * BULLET_VEROCITY * g_gameTime->GetFrameDeltaTime();

			m_position += m_moveSpeed;

			Vector3 moveVec = m_position - m_startPos;

			if (moveVec.Length() > DELETE_MOVE_DISTANCE) {
				DeleteThis();
			}
		}

		void Bullet::EnemyCollision()
		{
			//ìGÇÃêîÇæÇØé¿çsÇ∑ÇÈ
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				Vector3 toEnemyVec = m_position - enemyData->GetPosition();

				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					enemyData->SetState(enemy::enEnemyDamage);
					enemyData->ReceiveDamage(1);
					DeleteThis();
				}
			}
		}

		void Bullet::DeleteThis()
		{
			m_playerAttack->DeleteBullet(this);
			DeleteGO(this);
		}
	}
}