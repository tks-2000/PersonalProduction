#include "stdafx.h"
#include "OwnedItem.h"

namespace mainGame {
	namespace ui {
		/// @brief �A�C�e���X���b�g�̉��n�摜�̃t�@�C���p�X
		const char* ITEM_SLOT_BASE_SPRITE_FILEPATH = "Assets/Image/base_sprite_3.dds";
		/// @brief �A�C�e���X���b�g�̉��n�摜�̉���
		const int ITEM_SLOT_BASE_SPRITE_WIDTH = 625;
		/// @brief �A�C�e���X���b�g�̉��n�摜�̏c��
		const int ITEM_SLOT_BASE_SPRITE_HEIGHT = 640;
		/// @brief �A�C�e���X���b�g�̉��n�摜�̍��W
		const Vector3 ITEM_SLOT_BASE_SPRITE_POS = { 400.0f,-200.0f,0.0f };
		/// @brief �A�C�e���X���b�g�̉��n�摜�̃J���[
		const Vector4 ITEM_SLOT_BASE_SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief �A�C�e���X���b�g�̉��n�̘g�摜�̃t�@�C���p�X
		const char* ITEM_SLOT_BASE_FRAME_FILEPATH = "Assets/Image/base_sprite_4.dds";
		/// @brief �A�C�e���X���b�g�̉��n�̘g�摜�̉���
		const int ITEM_SLOT_BASE_FRAME_WIDTH = 600;
		/// @brief �A�C�e���X���b�g�̉��n�̘g�摜�̏c��
		const int ITEM_SLOT_BASE_FRAME_HEIGHT = 600;
		/// @brief �A�C�e���X���b�g�̉摜�̍��W�̔z��
		const Vector3 ITEM_SLOT_SPRITE_POS[ITEM_SLOT_NUM] = {
			{ 300.0f,-250.0f,0.0f },
			{ 400.0f,-250.0f,0.0f },
			{ 500.0f,-250.0f,0.0f }
		};
		/// @brief �A�C�e���X���b�g�̉摜�̉���
		const int ITEM_SLOT_SPRITE_WIDTH = 75;
		/// @brief �A�C�e���X���b�g�̉摜�̏c��
		const int ITEM_SLOT_SPRITE_HEIGHT = 75;
		/// @brief �A�C�e���摜�̉���
		const int ITEM_SPRITE_WIDTH = 70;
		/// @brief �A�C�e���摜�̏c��
		const int ITEM_SPRITE_HEIGHT = 70;
		/// @brief �A�C�e���I���̉摜�̃t�@�C���p�X
		const char* ITEM_SELECT_SPRITE_FILEPATH = "Assets/Image/WB.dds";
		/// @brief �A�C�e���I���̉摜�̉���
		const int ITEM_SELECT_SPRITE_WIDTH = 90;
		/// @brief �A�C�e���I���̉摜�̏c��
		const int ITEM_SELECT_SPRITE_HEIGHT = 90;
		/// @brief �A�C�e���I���̉摜�̃J���[
		const Vector4 ITEM_SELECT_SPRITE_COLOR = { 1.0f,0.0f,0.0f,1.0f };
		/// @brief ���e�̉摜�̃t�@�C���p�X
		const char* BOMB_SPRITE_FILEPATH = "Assets/Image/bomb.dds";
		/// @brief �C������̉摜�̃t�@�C���p�X
		const char* REPAIRTOOLS_SPRITE_FILEPATH = "Assets/Image/wrench.dds";
		/// @brief �h�{�h�����N�̉摜�̃t�@�C���p�X
		const char* NUTRITIONDRINK_SPRITE_FILEPATH = "Assets/Image/portion.dds";

		OwnedItem::OwnedItem()
		{
			
			m_isInitd = false;
		}

		OwnedItem::~OwnedItem()
		{
			//�X���b�g�̐������J��Ԃ�
			for (int slotNum = 0; slotNum < ITEM_SLOT_NUM; slotNum++) {
				//�X���b�g�摜���폜
				DeleteGO(m_itemSlotSprite[slotNum]);
				//�\���t���O�������Ă���΁c
				if (m_itemSpriteFlag[slotNum] == true) {
					//�A�C�e���摜���폜
					DeleteGO(m_itemSprite[slotNum]);
				}
			}
			//�\�����Ă���摜���폜
			DeleteGO(m_selectSprite);
			DeleteGO(m_itemSlotBaseSprite);
			DeleteGO(m_itemSlotBaseFrame);
		}

		void OwnedItem::Init()
		{
			//�摜���쐬
			m_itemSlotBaseSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_itemSlotBaseSprite->Init(ITEM_SLOT_BASE_SPRITE_FILEPATH, ITEM_SLOT_BASE_SPRITE_WIDTH, ITEM_SLOT_BASE_SPRITE_HEIGHT);
			m_itemSlotBaseSprite->SetPosition(ITEM_SLOT_BASE_SPRITE_POS);
			m_itemSlotBaseSprite->SetColor(ITEM_SLOT_BASE_SPRITE_COLOR);

			m_itemSlotBaseFrame = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_itemSlotBaseFrame->Init(ITEM_SLOT_BASE_FRAME_FILEPATH, ITEM_SLOT_BASE_FRAME_WIDTH, ITEM_SLOT_BASE_FRAME_HEIGHT);
			m_itemSlotBaseFrame->SetPosition(ITEM_SLOT_BASE_SPRITE_POS);

			m_selectSprite = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
			m_selectSprite->Init(ITEM_SELECT_SPRITE_FILEPATH, ITEM_SELECT_SPRITE_WIDTH, ITEM_SELECT_SPRITE_HEIGHT);
			m_selectSprite->SetColor(ITEM_SELECT_SPRITE_COLOR);

			for (int slotNum = 0; slotNum < ITEM_SLOT_NUM; slotNum++) {
				m_itemSlotSprite[slotNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);
				m_itemSlotSprite[slotNum]->Init(ITEM_SELECT_SPRITE_FILEPATH, ITEM_SLOT_SPRITE_WIDTH, ITEM_SLOT_SPRITE_HEIGHT);
				m_itemSlotSprite[slotNum]->SetPosition(ITEM_SLOT_SPRITE_POS[slotNum]);
			}

			//�ϐ���������
			m_selectSpritePos = ITEM_SLOT_SPRITE_POS[0];

			//�g�p����������
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//����������
			m_isInitd = true;
		}

		void OwnedItem::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�A�C�e���̉��n�摜�̏��������s
			m_itemSlotBaseFrame->Execute();
			m_itemSlotBaseSprite->Execute();

			//�X���b�g�̐��������s
			for (int slotNum = 0; slotNum < ITEM_SLOT_NUM; slotNum++) {

				//�v���C���[���A�C�e���������Ă�����c
				if (m_player->IsOwnedItem(slotNum) == true) {
					//�A�C�e���摜�̕\���t���O�������Ă��Ȃ�������c
					if (m_itemSpriteFlag[slotNum] == false) {
						//�A�C�e���摜���쐬����
						CreateItemSprite(slotNum);
						m_itemSpriteFlag[slotNum] = true;
					}
					//�A�C�e���摜�̕\���t���O�������Ă�����c
					else {
						//�A�C�e���摜�̏��������s����
						m_itemSprite[slotNum]->Execute();
					}
				}
				//�v���C���[���A�C�e���������Ă��Ȃ�������c
				else {
					//�A�C�e���摜�̕\���t���O�������Ă�����c
					if (m_itemSpriteFlag[slotNum] == true) {
						//�A�C�e���摜���폜
						DeleteGO(m_itemSprite[slotNum]);
						m_itemSpriteFlag[slotNum] = false;
					}
				}
				//�A�C�e���X���b�g�̉摜�̏��������s
				m_itemSlotSprite[slotNum]->Execute();
			}

			//�A�C�e���I���̉摜�̈ʒu�����݃v���C���[���I�����Ă���X���b�g�̈ʒu�ɂ���
			m_selectSpritePos = ITEM_SLOT_SPRITE_POS[m_player->GetSelectSlotNum()];
			m_selectSprite->SetPosition(m_selectSpritePos);
			m_selectSprite->Execute();
		}

		void OwnedItem::HideUI()
		{
			//UI�̃J���[��S�ē����ɂ���
			m_itemSlotBaseSprite->SetColor(render::COLORLESS);

			m_itemSlotBaseFrame->SetColor(render::COLORLESS);
			for (int slotNum = 0; slotNum < ITEM_SLOT_NUM; slotNum++) {
				m_itemSlotSprite[slotNum]->SetColor(render::COLORLESS);
				if (m_itemSpriteFlag[slotNum] == true) {
					m_itemSprite[slotNum]->SetColor(render::COLORLESS);
				}
			}
			m_selectSprite->SetColor(render::COLORLESS);
		}

		void OwnedItem::CreateItemSprite(const int slotNum)
		{
			//�A�C�e���̉摜���쐬
			m_itemSprite[slotNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			//�v���C���[�̃A�C�e���X���b�g�ɓ����Ă���A�C�e���̎�ނŏo���摜�����߂�
			switch (m_player->GetSlotItemType(slotNum))
			{
				//���e
			case item::enItemBomb: {
				//���e�̉摜�ŏ�����
				m_itemSprite[slotNum]->Init(BOMB_SPRITE_FILEPATH, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
				//�C������
			case item::enItemRepairTools: {
				//�C������̉摜�ŏ�����
				m_itemSprite[slotNum]->Init(REPAIRTOOLS_SPRITE_FILEPATH, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
				//�h�{�h�����N
			case item::enItemNutritionDrink: {
				//�h�s�h�����N�̉摜�ŏ�����
				m_itemSprite[slotNum]->Init(NUTRITIONDRINK_SPRITE_FILEPATH, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
			default:
				break;
			}

			//�A�C�e���̉摜���X���b�g�̈ʒu�ɕ\��
			m_itemSprite[slotNum]->SetPosition(ITEM_SLOT_SPRITE_POS[slotNum]);
			m_itemSprite[slotNum]->Execute();
		}
	}
}