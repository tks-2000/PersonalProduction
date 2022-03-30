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

		void ItemSlot::Init(Player* player)
		{
			//�v���C���[�̏���ݒ�
			m_player = player;

			//����������
			m_isInitd = true;
		}

		void ItemSlot::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�v���C���[���_���[�W���͎��s���Ȃ�
			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				return;
			}

			//�A�C�e���I���̏��������s
			ItemSelect();

			//�v���C���[��Y�{�^������������c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonY)) {
				//�A�C�e�����g�p����
				UseItem(m_selectNo);
			}
		}

		bool ItemSlot::SetItem(item::Item* item)
		{
			//�X���b�g��S�Ē��ׂ�
			for (int slotNum = 0; slotNum < MAX_ITEM_NUM; slotNum++) {
				//�X���b�g�ɋ󂫂���������c
				if (m_items[slotNum] == nullptr) {
					//�A�C�e�����X���b�g�ɓ����
					m_items[slotNum] = item;
					//�A�C�e�������邱�Ƃ��o�����̂ŏI��
					return true;
				}
			}

			//�A�C�e�������邱�Ƃ��o���Ȃ������̂ŏI��
			return false;
		}

		void ItemSlot::UseItem(const int slotNo)
		{
			//�X���b�g�ԍ����s���Ȃ���s���Ȃ�
			if (slotNo < MIN_ITEM_NUM || slotNo >= MAX_ITEM_NUM) {
				return;
			}
			//�I�����Ă���X���b�g�ɃA�C�e���������Ă��Ȃ��ꍇ�͎��s���Ȃ�
			if (m_items[slotNo] == nullptr) {
				return;
			}

			//�I�����Ă���X���b�g�ԍ��̃A�C�e���̌��ʂ𔭓�������
			m_items[slotNo]->Activation();
			//�g�p�����̂ŃX���b�g����ɂ���
			m_items[slotNo] = nullptr;
			
		}

		bool ItemSlot::IsOwnedItem(const int slotNum)const
		{
			//�X���b�g�ԍ����s���̏ꍇ�c
			if (slotNum >= MAX_ITEM_NUM || slotNum < MIN_ITEM_NUM) {
				//�����Ă��Ȃ��ƕԂ�
				return false;
			}
			//�X���b�g����̏ꍇ�c
			if (m_items[slotNum] == nullptr) {
				//�����Ă��Ȃ��ƕԂ�
				return false;
			}

			//�X���b�g�ɓ����Ă���̂Ŏ����Ă���ƕԂ�
			return true;
		}

		const item::EnItemType& ItemSlot::GetItemType(const int slotNum)
		{
			//�X���b�g�ԍ����s���̏ꍇ�c
			if (slotNum >= MAX_ITEM_NUM || slotNum < MIN_ITEM_NUM) {
				//�A�C�e���̎�ނ̐���Ԃ�
				return item::enItemTypeNum;
			}
			//�󂯎�����X���b�g�ԍ��̃A�C�e���̎�ނ�Ԃ�
			return m_items[slotNum]->GetItemType();
		}

		void ItemSlot::ItemSelect()
		{
			//�v���C���[�̉E�{�^���������ꂽ��c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRight)) {
				//�I�����Ă���X���b�g�ԍ��𑝂₷
				m_selectNo++;
				//�X���b�g�ԍ����Ō���𒴂�����
				if (m_selectNo >= MAX_ITEM_NUM) {
					//�őO��ɖ߂�
					m_selectNo = MIN_ITEM_NUM;
				}
			}

			//�v���C���[�̍��{�^���������ꂽ��c
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonLeft)) {
				//�I�����Ă���X���b�g�ԍ������炷
				m_selectNo--;
				//�X���b�g�ԍ����őO������������
				if (m_selectNo < MIN_ITEM_NUM) {
					//�Ō���ɐݒ肷��
					m_selectNo = MAX_ITEM_NUM - 1;
				}
			}
		}
		
	}
}