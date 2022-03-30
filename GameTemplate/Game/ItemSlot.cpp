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
			//プレイヤーの情報を設定
			m_player = player;

			//初期化完了
			m_isInitd = true;
		}

		void ItemSlot::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//プレイヤーがダメージ中は実行しない
			if (m_player->GetPlayerStatus() == enPlayerDamage) {
				return;
			}

			//アイテム選択の処理を実行
			ItemSelect();

			//プレイヤーがYボタンを押したら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonY)) {
				//アイテムを使用する
				UseItem(m_selectNo);
			}
		}

		bool ItemSlot::SetItem(item::Item* item)
		{
			//スロットを全て調べる
			for (int slotNum = 0; slotNum < MAX_ITEM_NUM; slotNum++) {
				//スロットに空きがあったら…
				if (m_items[slotNum] == nullptr) {
					//アイテムをスロットに入れる
					m_items[slotNum] = item;
					//アイテムを入れることが出来たので終了
					return true;
				}
			}

			//アイテムを入れることが出来なかったので終了
			return false;
		}

		void ItemSlot::UseItem(const int slotNo)
		{
			//スロット番号が不正なら実行しない
			if (slotNo < MIN_ITEM_NUM || slotNo >= MAX_ITEM_NUM) {
				return;
			}
			//選択しているスロットにアイテムが入っていない場合は実行しない
			if (m_items[slotNo] == nullptr) {
				return;
			}

			//選択しているスロット番号のアイテムの効果を発動させる
			m_items[slotNo]->Activation();
			//使用したのでスロットを空にする
			m_items[slotNo] = nullptr;
			
		}

		bool ItemSlot::IsOwnedItem(const int slotNum)const
		{
			//スロット番号が不正の場合…
			if (slotNum >= MAX_ITEM_NUM || slotNum < MIN_ITEM_NUM) {
				//持っていないと返す
				return false;
			}
			//スロットが空の場合…
			if (m_items[slotNum] == nullptr) {
				//持っていないと返す
				return false;
			}

			//スロットに入っているので持っていると返す
			return true;
		}

		const item::EnItemType& ItemSlot::GetItemType(const int slotNum)
		{
			//スロット番号が不正の場合…
			if (slotNum >= MAX_ITEM_NUM || slotNum < MIN_ITEM_NUM) {
				//アイテムの種類の数を返す
				return item::enItemTypeNum;
			}
			//受け取ったスロット番号のアイテムの種類を返す
			return m_items[slotNum]->GetItemType();
		}

		void ItemSlot::ItemSelect()
		{
			//プレイヤーの右ボタンが押されたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonRight)) {
				//選択しているスロット番号を増やす
				m_selectNo++;
				//スロット番号が最後尾を超えたら
				if (m_selectNo >= MAX_ITEM_NUM) {
					//最前列に戻す
					m_selectNo = MIN_ITEM_NUM;
				}
			}

			//プレイヤーの左ボタンが押されたら…
			if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonLeft)) {
				//選択しているスロット番号を減らす
				m_selectNo--;
				//スロット番号が最前列を下回ったら
				if (m_selectNo < MIN_ITEM_NUM) {
					//最後尾に設定する
					m_selectNo = MAX_ITEM_NUM - 1;
				}
			}
		}
		
	}
}