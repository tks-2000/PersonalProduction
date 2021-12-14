#pragma once
namespace mainGame {

	namespace enemy {
		class Enemy;
	}


	namespace item {

		class Item;

		enum EnItemType {
			enItemBomb,
			enItemRepairTools,
			enItemNutritionDrink,
			enItemTypeNum
		};

		/// @brief アイテム生成器
		class ItemGenerator : public IGameObject
		{
		public:
			ItemGenerator();
			~ItemGenerator();

			void Init();

			void Execution();

			void SpawnItem(const EnItemType& itemType, const Vector3& pos);

			void DeleteItem(Item* item);

		private:

			void SpawnJudgement();
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 出現フラグ
			bool m_spawnFlag = false;
			/// @brief 出現するまでの時間
			float m_spawnTime = 0.0f;
			/// @brief 出現するまでの時間を計るタイマー
			float m_spawnTimer = 0.0f;
			/// @brief 出現する場所
			Vector3 m_spawnPos = g_vec3Zero;
			/// @brief 出現しているアイテムの配列
			std::vector<Item*> m_items;
			/// @brief 敵生成器
			enemy::Generator* m_enemyGenerator = nullptr;
			/// @brief アイテムを落とす敵のポインタ
			enemy::Enemy* m_dropEnemy = nullptr;
			/// @brief 敵の情報を格納する配列のポインタ
			std::vector<enemy::Enemy*>* m_enemys = nullptr;
		};
	}
}
