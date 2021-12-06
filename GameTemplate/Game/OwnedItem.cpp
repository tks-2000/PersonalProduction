#include "stdafx.h"
#include "OwnedItem.h"

namespace mainGame {
	namespace ui {

		const Vector2 ITEM_SLOT_FONT_POS[3] = {
			{-550.0f,-250.0f},
			{-475.0f,-250.0f},
			{-400.0f,-250.0f}
		};

		const Vector3 SELECT_SPRITE_POS[3] = {
			{-537.5f,-270.0f,0.0f},
			{-462.5f,-270.0f,0.0f},
			{-387.5f,-270.0f,0.0f}
		};

		OwnedItem::OwnedItem()
		{
			
			m_isInitd = false;
		}

		OwnedItem::~OwnedItem()
		{
			for (int slotNum = 0; slotNum < 3; slotNum++) {
				DeleteGO(m_itemSlotFont[slotNum]);
			}

			DeleteGO(m_selectSprite);
		}

		void OwnedItem::Init()
		{
			for (int slotNum = 0; slotNum < 3; slotNum++) {
				m_itemSlotFont[slotNum] = NewGO<render::font::FontRender>(PRIORITY_VERYLOW);
				m_itemSlotFontPos[slotNum] = ITEM_SLOT_FONT_POS[slotNum];
				m_itemSlotFont[slotNum]->SetPosition(m_itemSlotFontPos[slotNum]);
				m_itemSlotFontColor[slotNum] = g_vec4White;
				std::wstring conversion;
				conversion = std::to_wstring(slotNum+1);
				m_itemSlotFont[slotNum]->Init(conversion.c_str());
			}

			m_selectSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_selectSprite->Init("Assets/Image/sight.dds", 100, 100);

			//m_selectSprite->SetPivot({ 1.0f,0.0f });

			m_selectSpritePos = SELECT_SPRITE_POS[0];

			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_isInitd = true;
		}

		void OwnedItem::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			for (int slotNum = 0; slotNum < 3; slotNum++) {

				if (m_player->IsOwnedItem(slotNum) == true) {
					m_itemSlotFontColor[slotNum] = g_vec4White;
				}
				else {
					m_itemSlotFontColor[slotNum] = g_vec4Black;
				}
				
				m_selectSpritePos = SELECT_SPRITE_POS[m_player->GetSelectSlotNum()];
				m_itemSlotFont[slotNum]->SetColor(m_itemSlotFontColor[slotNum]);
				m_itemSlotFont[slotNum]->Execution();
			}

			m_selectSprite->SetPosition(m_selectSpritePos);
			m_selectSprite->Execute();
		}
	}
}