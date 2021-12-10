#include "stdafx.h"
#include "NutritionDrink.h"

namespace mainGame {

	namespace item {

		const float DISAPPEARANCE_TIME = 10.0f;

		const float ENEMY_COLLISION_DISTANCE = 150.0f;

		const float BODY_BLOW_IMPACT = 5000.0f;

		const int BODY_BLOW_DAMAGE = 100;

		const float ADD_MOVE_VEROCITY = 10.0f;

		NutritionDrink::~NutritionDrink()
		{
			m_player->SetAddVerocity(0.0f);
		}

		void NutritionDrink::Activation()
		{
			m_isActivate = true;
		}

		void NutritionDrink::InitData()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);

			m_enemys = m_enemyGenerator->GetEnemys();

			m_endTime = DISAPPEARANCE_TIME;
		}

		void NutritionDrink::Efficacy()
		{
			m_position = m_player->GetPlayerPosition();

			m_player->SetAddVerocity(ADD_MOVE_VEROCITY);

			EnemyCollision();
		}

		void NutritionDrink::EnemyCollision()
		{
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//“G‚Ìƒf[ƒ^‚ğæ‚èo‚·
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//“G‚Æ‚Ì‹——£‚ğ‘ª‚é
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//“G‚Æ‚Ì‹——£‚ªÚG‹——£ˆÈ‰º‚È‚çc
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					//“G‚Ö‚ÆL‚Ñ‚éƒxƒNƒgƒ‹‚ğ³‹K‰»
					toEnemyVec.Normalize();

					//“G‚ÉÕŒ‚‚ğ‰Á‚¦‚é
					enemyData->SetMoveSpeed(toEnemyVec * BODY_BLOW_IMPACT);

					//“G‚ğƒ_ƒ[ƒWó‘Ô‚É•ÏX
					enemyData->SetState(enemy::enEnemyDamage);

					//“G‚É”š”­‚Ìƒ_ƒ[ƒW‚ğ—^‚¦‚é
					enemyData->ReceiveDamage(BODY_BLOW_DAMAGE);
				}
			}
		}
	}
}