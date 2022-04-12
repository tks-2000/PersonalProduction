#include "stdafx.h"
#include "ItemGenerator.h"
#include <random>

namespace mainGame {
	namespace item {
		/// @brief アイテムの出現確率
		const int ITEM_SPAWN_PROBABILITY = 4;

		ItemGenerator::ItemGenerator()
		{
			m_isInitd = false;
		}

		ItemGenerator::~ItemGenerator()
		{
			//配列の中身を全て削除
			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				DeleteGO(m_items[itemNum]);
			}
			//配列をクリア
			m_items.clear();
		}

		void ItemGenerator::Init()
		{
			//使用する情報を持って来る
			m_game = FindGO<Game>(GAME_NAME);
			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);
			m_enemys = m_enemyGenerator->GetEnemys();

			//初期化完了
			m_isInitd = true;
		}

		void ItemGenerator::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//ゲーム中でない場合は実行しない
			if (m_game->GetGameState() != enGameInProgress) {
				return;
			}

			//出現判定を行う
			SpawnJudgement();

			//アイテムの数だけ処理を実行する
			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				m_items[itemNum]->Execution();
			}

		}

		void ItemGenerator::SpawnItem(const EnItemType& itemType, const Vector3& pos)
		{
			//アイテムの種類で処理を分ける
			switch (itemType)
			{
				//爆弾
			case enItemBomb: {
				//爆弾を作成
				m_items.push_back(NewGO<Bomb>(PRIORITY_VERYLOW));
			}break;
				//修理道具
			case enItemRepairTools: {
				//修理道具を作成
				m_items.push_back(NewGO<RepairTools>(PRIORITY_VERYLOW));
			}break;
				//栄養ドリンク
			case enItemNutritionDrink: {
				//栄養ドリンクを作成
				m_items.push_back(NewGO<NutritionDrink>(PRIORITY_VERYLOW));
			}break;
			default:{
				return;
			}break;
			}

			//作成したアイテムを初期化
			m_items[m_items.size() - 1]->Init(this,pos);

		}

		void ItemGenerator::DeleteItem(Item* item)
		{
			//アイテムのイテレータを用意する
			std::vector<Item*>::iterator it;

			//アイテムのアドレスから削除するアイテムのイテレータを見つける
			it = std::find(
				m_items.begin(),
				m_items.end(),
				item
			);
			//イテレータが最後尾でない場合…
			if (it != m_items.end()) {
				//イテレータを使って配列から削除
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
					//数値が0未満の場合…
					if (num < 0) {
						//-1を乗算し正の数にする
						num *= -1;
					}

					//出現確率で除算した余りが0のとき…
					if (num % ITEM_SPAWN_PROBABILITY == 0) {

						//アイテムの種類の数で除算した余りの数のアイテムを生成する
						switch (num % enItemTypeNum)
						{
							//爆弾
						case enItemBomb: {
							//爆弾を出現させる
							SpawnItem(enItemBomb, enemyData->GetPosition());
						}break;
							//修理道具
						case enItemRepairTools: {
							//修理道具を出現させる
							SpawnItem(enItemRepairTools, enemyData->GetPosition());
						}break;
							//栄養ドリンク
						case enItemNutritionDrink: {
							//栄養ドリンクを出現させる
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