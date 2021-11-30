#include "stdafx.h"
#include "ItemSlot.h"

namespace mainGame {
	namespace player {

		ItemSlot::ItemSlot()
		{

		}

		ItemSlot::~ItemSlot()
		{

		}

		void ItemSlot::Init()
		{
			m_isInitd = true;
		}

		void ItemSlot::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonY)) {
				UseItem(m_selectNo);
			}
		}

		bool ItemSlot::SetItem(item::Item* item)
		{
			if (m_items.size() >= MAX_ITEM_NUM) {
				return false;
			}

			m_items.push_back(item);
			return true;
		}

		void ItemSlot::UseItem(const int slotNo)
		{
			if (slotNo < MIN_ITEM_NUM || slotNo > MAX_ITEM_NUM || m_items.size() <= slotNo) {
				return;
			}

			m_items[slotNo]->Activation();

			std::vector<item::Item*>::iterator it;

			it = std::find(
				m_items.begin(),
				m_items.end(),
				m_items[slotNo]
			);

			if (it != m_items.end()) {
				m_items.erase(it);
			}
			
		}

		void ItemSlot::ItemSelect()
		{
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRight)) {
				m_selectNo++;
				if (m_selectNo >= MAX_ITEM_NUM) {
					m_selectNo = MIN_ITEM_NUM;
				}
			}
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonLeft)) {
				m_selectNo--;
				if (m_selectNo < MIN_ITEM_NUM) {
					m_selectNo = MAX_ITEM_NUM - 1;
				}
			}
		}
		
	}
}