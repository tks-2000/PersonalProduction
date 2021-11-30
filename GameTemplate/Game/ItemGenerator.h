#pragma once
namespace mainGame {
	namespace item {

		class Item;

		/// @brief ÉAÉCÉeÉÄê∂ê¨äÌ
		class ItemGenerator : public IGameObject
		{
		public:
			ItemGenerator();
			~ItemGenerator();

			void Init();

			void Execution();

			void SpawnItem(const Vector3& pos);

			void DeleteItem(Item* item);

		private:

			bool m_isInitd = false;

			std::vector<Item*> m_items;


		};
	}
}
