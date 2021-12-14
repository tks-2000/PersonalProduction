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

		/// @brief �A�C�e��������
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
			/// @brief �������t���O
			bool m_isInitd = false;
			/// @brief �o���t���O
			bool m_spawnFlag = false;
			/// @brief �o������܂ł̎���
			float m_spawnTime = 0.0f;
			/// @brief �o������܂ł̎��Ԃ��v��^�C�}�[
			float m_spawnTimer = 0.0f;
			/// @brief �o������ꏊ
			Vector3 m_spawnPos = g_vec3Zero;
			/// @brief �o�����Ă���A�C�e���̔z��
			std::vector<Item*> m_items;
			/// @brief �G������
			enemy::Generator* m_enemyGenerator = nullptr;
			/// @brief �A�C�e���𗎂Ƃ��G�̃|�C���^
			enemy::Enemy* m_dropEnemy = nullptr;
			/// @brief �G�̏����i�[����z��̃|�C���^
			std::vector<enemy::Enemy*>* m_enemys = nullptr;
		};
	}
}
