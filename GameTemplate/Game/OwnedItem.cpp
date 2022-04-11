#include "stdafx.h"
#include "OwnedItem.h"

namespace mainGame {
	namespace ui {
		/// @brief アイテムスロットの下地画像のファイルパス
		const char* ITEM_SLOT_BASE_SPRITE_FILEPATH = "Assets/Image/base_sprite_3.dds";
		/// @brief アイテムスロットの下地画像の横幅
		const int ITEM_SLOT_BASE_SPRITE_WIDTH = 625;
		/// @brief アイテムスロットの下地画像の縦幅
		const int ITEM_SLOT_BASE_SPRITE_HEIGHT = 640;
		/// @brief アイテムスロットの下地画像の座標
		const Vector3 ITEM_SLOT_BASE_SPRITE_POS = { 400.0f,-200.0f,0.0f };
		/// @brief アイテムスロットの下地画像のカラー
		const Vector4 ITEM_SLOT_BASE_SPRITE_COLOR = { 1.0f,1.0f,1.0f,0.5f };
		/// @brief アイテムスロットの下地の枠画像のファイルパス
		const char* ITEM_SLOT_BASE_FRAME_FILEPATH = "Assets/Image/base_sprite_4.dds";
		/// @brief アイテムスロットの下地の枠画像の横幅
		const int ITEM_SLOT_BASE_FRAME_WIDTH = 600;
		/// @brief アイテムスロットの下地の枠画像の縦幅
		const int ITEM_SLOT_BASE_FRAME_HEIGHT = 600;
		/// @brief アイテムスロットの画像の座標の配列
		const Vector3 ITEM_SLOT_SPRITE_POS[ITEM_SLOT_NUM] = {
			{ 300.0f,-250.0f,0.0f },
			{ 400.0f,-250.0f,0.0f },
			{ 500.0f,-250.0f,0.0f }
		};
		/// @brief アイテムスロットの画像の横幅
		const int ITEM_SLOT_SPRITE_WIDTH = 75;
		/// @brief アイテムスロットの画像の縦幅
		const int ITEM_SLOT_SPRITE_HEIGHT = 75;
		/// @brief アイテム画像の横幅
		const int ITEM_SPRITE_WIDTH = 70;
		/// @brief アイテム画像の縦幅
		const int ITEM_SPRITE_HEIGHT = 70;
		/// @brief アイテム選択の画像のファイルパス
		const char* ITEM_SELECT_SPRITE_FILEPATH = "Assets/Image/WB.dds";
		/// @brief アイテム選択の画像の横幅
		const int ITEM_SELECT_SPRITE_WIDTH = 90;
		/// @brief アイテム選択の画像の縦幅
		const int ITEM_SELECT_SPRITE_HEIGHT = 90;
		/// @brief アイテム選択の画像のカラー
		const Vector4 ITEM_SELECT_SPRITE_COLOR = { 1.0f,0.0f,0.0f,1.0f };
		/// @brief 爆弾の画像のファイルパス
		const char* BOMB_SPRITE_FILEPATH = "Assets/Image/bomb.dds";
		/// @brief 修理道具の画像のファイルパス
		const char* REPAIRTOOLS_SPRITE_FILEPATH = "Assets/Image/wrench.dds";
		/// @brief 栄養ドリンクの画像のファイルパス
		const char* NUTRITIONDRINK_SPRITE_FILEPATH = "Assets/Image/portion.dds";

		OwnedItem::OwnedItem()
		{
			
			m_isInitd = false;
		}

		OwnedItem::~OwnedItem()
		{
			//スロットの数だけ繰り返す
			for (int slotNum = 0; slotNum < ITEM_SLOT_NUM; slotNum++) {
				//スロット画像を削除
				DeleteGO(m_itemSlotSprite[slotNum]);
				//表示フラグが立っていれば…
				if (m_itemSpriteFlag[slotNum] == true) {
					//アイテム画像を削除
					DeleteGO(m_itemSprite[slotNum]);
				}
			}
			//表示している画像を削除
			DeleteGO(m_selectSprite);
			DeleteGO(m_itemSlotBaseSprite);
			DeleteGO(m_itemSlotBaseFrame);
		}

		void OwnedItem::Init()
		{
			//画像を作成
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

			//変数を初期化
			m_selectSpritePos = ITEM_SLOT_SPRITE_POS[0];

			//使用する情報を入手
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void OwnedItem::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//アイテムの下地画像の処理を実行
			m_itemSlotBaseFrame->Execute();
			m_itemSlotBaseSprite->Execute();

			//スロットの数だけ実行
			for (int slotNum = 0; slotNum < ITEM_SLOT_NUM; slotNum++) {

				//プレイヤーがアイテムを持っていたら…
				if (m_player->IsOwnedItem(slotNum) == true) {
					//アイテム画像の表示フラグが立っていなかったら…
					if (m_itemSpriteFlag[slotNum] == false) {
						//アイテム画像を作成する
						CreateItemSprite(slotNum);
						m_itemSpriteFlag[slotNum] = true;
					}
					//アイテム画像の表示フラグが立っていたら…
					else {
						//アイテム画像の処理を実行する
						m_itemSprite[slotNum]->Execute();
					}
				}
				//プレイヤーがアイテムを持っていなかったら…
				else {
					//アイテム画像の表示フラグが立っていたら…
					if (m_itemSpriteFlag[slotNum] == true) {
						//アイテム画像を削除
						DeleteGO(m_itemSprite[slotNum]);
						m_itemSpriteFlag[slotNum] = false;
					}
				}
				//アイテムスロットの画像の処理を実行
				m_itemSlotSprite[slotNum]->Execute();
			}

			//アイテム選択の画像の位置を現在プレイヤーが選択しているスロットの位置にする
			m_selectSpritePos = ITEM_SLOT_SPRITE_POS[m_player->GetSelectSlotNum()];
			m_selectSprite->SetPosition(m_selectSpritePos);
			m_selectSprite->Execute();
		}

		void OwnedItem::HideUI()
		{
			//UIのカラーを全て透明にする
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
			//アイテムの画像を作成
			m_itemSprite[slotNum] = NewGO<render::sprite::SpriteRender>(PRIORITY_VERYLOW);

			//プレイヤーのアイテムスロットに入っているアイテムの種類で出す画像を決める
			switch (m_player->GetSlotItemType(slotNum))
			{
				//爆弾
			case item::enItemBomb: {
				//爆弾の画像で初期化
				m_itemSprite[slotNum]->Init(BOMB_SPRITE_FILEPATH, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
				//修理道具
			case item::enItemRepairTools: {
				//修理道具の画像で初期化
				m_itemSprite[slotNum]->Init(REPAIRTOOLS_SPRITE_FILEPATH, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
				//栄養ドリンク
			case item::enItemNutritionDrink: {
				//栄耀ドリンクの画像で初期化
				m_itemSprite[slotNum]->Init(NUTRITIONDRINK_SPRITE_FILEPATH, ITEM_SPRITE_WIDTH, ITEM_SPRITE_HEIGHT);
			}break;
			default:
				break;
			}

			//アイテムの画像をスロットの位置に表示
			m_itemSprite[slotNum]->SetPosition(ITEM_SLOT_SPRITE_POS[slotNum]);
			m_itemSprite[slotNum]->Execute();
		}
	}
}