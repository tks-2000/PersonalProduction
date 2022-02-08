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
				//�G�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//�G�Ƃ̋������ڐG�����ȉ��Ȃ�c
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && enemyData->GetState() != enemy::enEnemyDown) {

					//�G�ւƐL�т�x�N�g���𐳋K��
					toEnemyVec.Normalize();

					//�G�ɏՌ���������
					enemyData->SetMoveSpeed(toEnemyVec * BODY_BLOW_IMPACT);

					//�G�ɔ����̃_���[�W��^����
					enemyData->ReceiveDamage(BODY_BLOW_DAMAGE);
				}
			}
		}

		void NutritionDrink::DeleteEfficacy()
		{
			m_player->SetAddVerocity(0.0f);
		}
	}
}