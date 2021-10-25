#include "stdafx.h"
#include "PlayerBullet.h"

namespace mainGame {
	namespace player {

		const float BULLET_VEROCITY = 1000.0f;

		const float ENEMY_COLLISION_DISTANCE = 200.0f;

		const float DELETE_MOVE_DISTANCE = 3000.0f;

		const float BULLET_IMPACT_FORCE = 2000.0f;

		const int BULLET_DAMAGE = 1;

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
			m_bulletModel->SetScale({ 0.7f,0.7f,0.7f });

			m_startPos = pos;

			m_position = m_startPos;

			m_target = target;

			m_moveDirection = m_target - m_startPos;

			m_moveDirection.Normalize();

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

				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					toEnemyVec.Normalize();
					enemyData->SetMoveSpeed(toEnemyVec * BULLET_IMPACT_FORCE);

					enemyData->SetState(enemy::enEnemyDamage);
					enemyData->ReceiveDamage(BULLET_DAMAGE);
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