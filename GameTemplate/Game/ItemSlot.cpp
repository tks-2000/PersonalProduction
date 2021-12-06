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

			ItemSelect();

			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonY)) {
				UseItem(m_selectNo);
			}
		}

		bool ItemSlot::SetItem(item::Item* item)
		{
			
			for (int slotNum = 0; slotNum < MAX_ITEM_NUM; slotNum++) {
				if (m_items[slotNum] == nullptr) {
					m_items[slotNum] = item;
					return true;
				}
			}

			return false;
		}

		void ItemSlot::UseItem(const int slotNo)
		{
			if (slotNo < MIN_ITEM_NUM || slotNo >= MAX_ITEM_NUM) {
				return;
			}

			if (m_items[slotNo] == nullptr) {
				return;
			}

			m_items[slotNo]->Activation();

			m_items[slotNo] = nullptr;
			
		}

		bool ItemSlot::IsOwnedItem(const int slotNum)const
		{
			if (slotNum >= MAX_ITEM_NUM || slotNum < MIN_ITEM_NUM) {
				return false;
			}

			if (m_items[slotNum] == nullptr) {
				return false;
			}

			return true;
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