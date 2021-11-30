#pragma once

namespace mainGame {
	namespace item {
		class Item;
	}

	namespace player {
		class ItemSlot
		{
		public:
			ItemSlot();
			~ItemSlot();

			void Init();

			void Execution();

			/// @brief �X���b�g�ɃA�C�e����ݒ�
			/// @param item �ݒ肷��A�C�e���̃A�h���X
			/// @return true�ŃX���b�g�ɐݒ�ł��� false�ŃX���b�g�ɐݒ�ł��Ȃ�����
			bool SetItem(item::Item* item);

			/// @brief �����Ă���A�C�e�����g��
			/// @param slotNo �g�p����A�C�e���X���b�g�ԍ�
			void UseItem(const int slotNo);
			
		private:

			void ItemSelect();

			bool m_isInitd = false;

			enum { 
				MIN_ITEM_NUM = 0,
				MAX_ITEM_NUM = 3 
			};
			
			/// @brief �I�����Ă���A�C�e���ԍ�
			int m_selectNo = 0;

			std::vector<item::Item*> m_items;
		};

	}
}
