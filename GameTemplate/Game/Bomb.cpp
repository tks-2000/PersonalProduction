#include "stdafx.h"
#include "Bomb.h"

namespace mainGame {
	namespace item {

		const float ENEMY_COLLISION_DISTANCE = 100.0f;

		const float BULLET_COLLISION_DISTANCE = 200.0f;

		const float EXPLOSION_RADIUS = 500.0f;

		const float EXPLOSION_IMPACT = 5000.0f;

		const int EXPLOSION_DAMAGE = 10;

		Bomb::~Bomb()
		{
			if (m_modelFlag == true) {
				DeleteGO(m_itemModel);
			}
		}

		void Bomb::InitData()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_position = { -200.0f,50.0f,200.0f };

			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);

			m_enemys = m_enemyGenerator->GetEnemys();

			m_bullets = m_player->GetBulletData();

			m_endTime = 10.0f;
		}

		void Bomb::Activation()
		{
			m_isActivate = true;

			m_position = m_player->GetPlayerPosition();

			CreateModel();
		}

		void Bomb::Efficacy()
		{

			

			if (m_modelFlag == true) {
				
				m_itemModel->SetPosition(m_position);
				m_itemModel->Execution();

				EnemyCollision();

				BulletCollision();
			}
		}

		void Bomb::CreateModel()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_modelFlag = true;
		}

		void Bomb::EnemyCollision()
		{
			//“G‚Ì”‚¾‚¯Às‚·‚é
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//“G‚Ìƒf[ƒ^‚ğæ‚èo‚·
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//“G‚Æ‚Ì‹——£‚ğ‘ª‚é
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//“G‚Æ‚Ì‹——£‚ªÚG‹——£ˆÈ‰º‚È‚çc
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					m_activateTimer = 0.0f;

					m_endTime = 3.0f;

					//”š”­‚·‚é
					Explosion();

					DeleteGO(m_itemModel);

					m_modelFlag = false;
				}
			}
		}

		void Bomb::BulletCollision()
		{
			for (int bulletNum = 0; bulletNum < m_bullets->size(); bulletNum++) {
				player::Bullet* bulletData = *(m_bullets->begin() + bulletNum);

				Vector3 toBulletVec = bulletData->GetPosition() - m_position;

				if (toBulletVec.Length() < BULLET_COLLISION_DISTANCE) {
					m_activateTimer = 0.0f;

					m_endTime = 3.0f;

					//”š”­‚·‚é
					Explosion();

					DeleteGO(m_itemModel);

					m_modelFlag = false;
				}

			}
		}

		void Bomb::Explosion()
		{
			//“G‚Ì”‚¾‚¯Às‚·‚é
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//“G‚Ìƒf[ƒ^‚ğæ‚èo‚·
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//“G‚Æ‚Ì‹——£‚ğ‘ª‚é
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//“G‚Æ‚Ì‹——£‚ª”š”­”¼ŒaˆÈ‰º‚È‚çc
				if (toEnemyVec.Length() < EXPLOSION_RADIUS) {

					toEnemyVec.Normalize();

					enemyData->SetMoveSpeed(toEnemyVec * EXPLOSION_IMPACT);

					enemyData->SetState(enemy::enEnemyDamage);

					enemyData->ReceiveDamage(EXPLOSION_DAMAGE);

					
				}
			}
		}
	}
}