#include "stdafx.h"
#include "ItemGenerator.h"
#include <random>

namespace mainGame {
	namespace item {

		const int ITEM_SPAWN_PROBABILITY = 1;

		ItemGenerator::ItemGenerator()
		{
			m_isInitd = false;
		}

		ItemGenerator::~ItemGenerator()
		{
			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				DeleteGO(m_items[itemNum]);
			}

			m_items.clear();
		}

		void ItemGenerator::Init()
		{
			SpawnItem(enItemBomb,{ 200.0f,50.0f,200.0f });
			SpawnItem(enItemRepairTools,{ -200.0f,50.0f,200.0f });
			SpawnItem(enItemNutritionDrink,{ 200.0f,50.0f,-200.0f });

			m_game = FindGO<Game>(GAME_NAME);
			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);

			m_enemys = m_enemyGenerator->GetEnemys();

			m_isInitd = true;
		}

		void ItemGenerator::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			
			if (m_game->GetGameState() != enGameInProgress) {
				return;
			}

			SpawnJudgement();


			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				m_items[itemNum]->Execution();
			}

		}

		void ItemGenerator::SpawnItem(const EnItemType& itemType, const Vector3& pos)
		{
			switch (itemType)
			{
			case enItemBomb: {
				m_items.push_back(NewGO<Bomb>(PRIORITY_VERYLOW));
			}break;
			case enItemRepairTools: {
				m_items.push_back(NewGO<RepairTools>(PRIORITY_VERYLOW));
			}break;
			case enItemNutritionDrink: {
				m_items.push_back(NewGO<NutritionDrink>(PRIORITY_VERYLOW));
			}break;
			default:{
				return;
			}break;
			}

			m_items[m_items.size() - 1]->Init(this,pos);

			//m_items[m_items.size() - 1]->SetPosition(pos);
		}

		void ItemGenerator::DeleteItem(Item* item)
		{
			std::vector<Item*>::iterator it;

			it = std::find(
				m_items.begin(),
				m_items.end(),
				item
			);
			if (it != m_items.end()) {
				m_items.erase(it);
			}
		}

		void ItemGenerator::SpawnJudgement()
		{
			//敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//敵のデータを取り出す
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//敵が撃破されていたら…
				if (enemyData->IsDefeat() == true) {
					//ランダムな数値を生成する
					std::random_device rnd;
					int num = rnd();
					if (num < 0) {
						num *= -1;
					}

					//出現確率で
					if (num % ITEM_SPAWN_PROBABILITY == 0) {

						switch (num % enItemTypeNum)
						{
						case enItemBomb: {
							SpawnItem(enItemBomb, enemyData->GetPosition());
						}break;
						case enItemRepairTools: {
							SpawnItem(enItemRepairTools, enemyData->GetPosition());
						}break;
						case enItemNutritionDrink: {
							SpawnItem(enItemNutritionDrink, enemyData->GetPosition());
						}
						default:
							break;
						}
						
					}
				}
			}
		}
	}
}