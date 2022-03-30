#pragma once
#include "ItemResource.h"


namespace mainGame {
	namespace item {
		class Item;
	}

	namespace player {

		/// @brief �v���C���[�̎��A�C�e�����Ǘ�����N���X
		class ItemSlot
		{
		public:
			ItemSlot();
			~ItemSlot();

			/// @brief ������
			void Init(Player* player);

			/// @brief ���s
			void Execution();

			/// @brief �X���b�g�ɃA�C�e����ݒ�
			/// @param item �ݒ肷��A�C�e���̃A�h���X
			/// @return true�ŃX���b�g�ɐݒ�ł��� false�ŃX���b�g�ɐݒ�ł��Ȃ�����
			bool SetItem(item::Item* item);

			/// @brief �����Ă���A�C�e�����g��
			/// @param slotNo �g�p����A�C�e���X���b�g�ԍ�
			void UseItem(const int slotNo);

			/// @brief ���ݑI�����Ă���X���b�g�ԍ����擾
			/// @return �I�����Ă���A�C�e���X���b�g�ԍ�
			const int GetSelectSlotNum()const { return m_selectNo; }

			/// @brief �A�C�e���������Ă��邩�H
			/// @param slotNum �����Ă��邩���ׂ�X���b�g�ԍ�
			/// @return true�Ȃ玝���Ă��� false�Ȃ�����Ă��Ȃ�
			bool IsOwnedItem(const int slotNum)const;
			
			/// @brief �X���b�g�ɂ���A�C�e���̎�ނ��擾
			/// @param slotNum ���ׂ�X���b�g�ԍ�
			/// @return �A�C�e���̎��
			const item::EnItemType& GetItemType(const int slotNum);

		private:

			/// @brief �g�p����A�C�e���X���b�g�I�����s���֐�
			void ItemSelect();

			/// @brief �������t���O
			bool m_isInitd = false;

			enum {
				/// @brief �A�C�e���̍ŏ�������
				MIN_ITEM_NUM = 0,
				/// @brief �A�C�e���̍ő及����
				MAX_ITEM_NUM = 3 
			};
			
			/// @brief �I�����Ă���A�C�e���ԍ�
			int m_selectNo = 0;
			/// @brief �A�C�e��
			item::Item* m_items[MAX_ITEM_NUM] = { nullptr };
			/// @brief �v���C���[
			Player* m_player = nullptr;
		};

	}
}
