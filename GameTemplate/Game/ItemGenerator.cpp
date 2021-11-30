#include "stdafx.h"
#include "ItemGenerator.h"

namespace mainGame {
	namespace item {
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
			SpawnItem({ 200.0f,50.0f,200.0f });
			SpawnItem({ -200.0f,50.0f,200.0f });
			SpawnItem({ 200.0f,50.0f,-200.0f });
			SpawnItem({ -200.0f,50.0f,-200.0f });
			m_isInitd = true;
		}

		void ItemGenerator::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			for (int itemNum = 0; itemNum < m_items.size(); itemNum++) {
				m_items[itemNum]->Execution();
			}

		}

		void ItemGenerator::SpawnItem(const Vector3& pos)
		{
			m_items.push_back(NewGO<Bomb>(PRIORITY_VERYLOW));

			m_items[m_items.size() - 1]->Init(this);

			m_items[m_items.size() - 1]->SetPosition(pos);
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
	}
}