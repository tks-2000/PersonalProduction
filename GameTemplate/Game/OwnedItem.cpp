#include "stdafx.h"
#include "OwnedItem.h"

namespace mainGame {
	namespace ui {

		const Vector3 ITEM_SLOT_BASE_SPRITE_POS = { 400.0f,-200.0f,0.0f };

		const int ITEM_SLOT_BASE_FRAME_WIDTH = 600;

		const int ITEM_SLOT_BASE_FRAME_HEIGHT = 600;

		const int ITEM_SLOT_BASE_SPRITE_WIDTH = 625;

		const int ITEM_SLOT_BASE_SPRITE_HEIGHT = 640;

		const Vector3 ITEM_SLOT_SPRITE_POS[3] = {
			{ 300.0f,-250.0f,0.0f },
			{ 400.0f,-250.0f,0.0f },
			{ 500.0f,-250.0f,0.0f }
		};

		const int ITEM_SLOT_SPRITE_WIDTH = 75;

		const int ITEM_SLOT_SPRITE_HEIGHT = 75;


		const int ITEM_SPRITE_WIDTH = 70;

		const int ITEM_SPRITE_HEIGHT = 70;

		const int ITEM_SELECT_SPRITE_WIDTH = 90;

		const int ITEM_SELECT_SPRITE_HEIGHT = 90;

		OwnedItem::OwnedItem()
		{
			
			m_isInitd = false;
		}

		OwnedItem::~OwnedItem()
		{
			for (int slotNum = 0; slotNum < 3; slotNum++) {
				DeleteGO(m_itemSlotSprite[slotNum]);
			
				if (m_itemSpriteFlag[slotNum] == true) {
					DeleteGO(m_itemSprite[slotNum]);
				}
			}
			
			DeleteGO(m_selectSprite);
			DeleteGO(m_itemSlotBaseSprite);
			DeleteGO(m_itemSlotBaseFrame);
		}

		void OwnedItem::Init()
		{
			
			m_itemSlotBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_itemSlotBaseSprite->Init("Assets/Image/base_sprite_3.dds", ITEM_SLOT_BASE_SPRITE_WIDTH, ITEM_SLOT_BASE_SPRITE_HEIGHT);
			m_itemSlotBaseSprite->SetPosition(ITEM_SLOT_BASE_SPRITE_POS);
			m_itemSlotBaseSprite->SetColor({1.0f,1.0f,1.0f,0.5f});
			m_itemSlotBaseFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_itemSlotBaseFrame->Init("Assets/Image/base_sprite_4.dds", ITEM_SLOT_BASE_FRAME_WIDTH, ITEM_SLOT_BASE_FRAME_HEIGHT);
			m_itemSlotBaseFrame->SetPosition(ITEM_SLOT_BASE_SPRITE_POS);

			m_selectSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			m_selectSprite->Init("Assets/Image/WB.dds", ITEM_SELECT_SPRITE_WIDTH, ITEM_SELECT_SPRITE_HEIGHT);

			m_selectSprite->SetColor({1.0f,0.0f,0.0f,1.0f});

			for (int slotNum = 0; slotNum < 3; slotNum++) {
				m_itemSlotSprite[slotNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
				m_itemSlotSprite[slotNum]->Init("Assets/Image/WB.dds", ITEM_SLOT_SPRITE_WIDTH, ITEM_SLOT_SPRITE_HEIGHT);
				m_itemSlotSprite[slotNum]->SetPosition(ITEM_SLOT_SPRITE_POS[slotNum]);

				
			
			}

			

			//m_selectSprite->SetPivot({ 1.0f,0.0f });

			m_selectSpritePos = ITEM_SLOT_SPRITE_POS[0];

			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			m_isInitd = true;
		}

		void OwnedItem::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			m_itemSlotBaseFrame->Execute();
			m_itemSlotBaseSprite->Execute();

			for (int slotNum = 0; slotNum < 3; slotNum++) {

				if (m_player->IsOwnedItem(slotNum) == true) {
					if (m_itemSpriteFlag[slotNum] == false) {
						CreateItemSprite(slotNum);
						m_itemSpriteFlag[slotNum] = true;
					}
					else {
						m_itemSprite[slotNum]->Execute();
					}
					
				}
				else {
					if (m_itemSpriteFlag[slotNum] == true) {
						DeleteGO(m_itemSprite[slotNum]);
						m_itemSpriteFlag[slotNum] = false;
					}

					
				}
				m_itemSlotSprite[slotNum]->Execute();
				
				
			}

			m_selectSpritePos = ITEM_SLOT_SPRITE_POS[m_player->GetSelectSlotNum()];
			m_selectSprite->SetPosition(m_selectSpritePos);
			m_selectSprite->Execute();
		}

		void OwnedItem::CreateItemSprite(const int slotNum)
		{
			m_itemSprite[slotNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			switch (m_player->GetSlotItemType(slotNum))
			{
			case item::enItemBomb: {
				m_itemSprite[slotNum]->Init("Assets/Image/bomb.dds", ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
			case item::enItemRepairTools: {
				m_itemSprite[slotNum]->Init("Assets/Image/wrench.dds", ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
			case item::enItemNutritionDrink: {
				m_itemSprite[slotNum]->Init("Assets/Image/portion.dds", ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
			default:
				break;
			}
			m_itemSprite[slotNum]->SetPosition(ITEM_SLOT_SPRITE_POS[slotNum]);

			m_itemSprite[slotNum]->Execute();
		}
	}
}