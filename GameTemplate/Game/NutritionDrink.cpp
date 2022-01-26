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
			m_itemType = enItemNutritionDrink;

			

			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);

			m_enemys = m_enemyGenerator->GetEnemys();

			m_endTime = DISAPPEARANCE_TIME;
		}

		void NutritionDrink::Spawn()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/item/item_speedup.tkm");
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
				//敵のデータを取り出す
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//敵との距離を測る
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//敵との距離が接触距離以下なら…
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					//敵へと伸びるベクトルを正規化
					toEnemyVec.Normalize();

					//敵に衝撃を加える
					enemyData->SetMoveSpeed(toEnemyVec * BODY_BLOW_IMPACT);

					//敵をダメージ状態に変更
					enemyData->SetState(enemy::enEnemyDamage);

					//敵に爆発のダメージを与える
					enemyData->ReceiveDamage(BODY_BLOW_DAMAGE);
				}
			}
		}
	}
}