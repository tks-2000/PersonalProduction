#include "stdafx.h"
#include "RepairTools.h"

namespace mainGame {
	namespace item {
		/// @brief アイテムモデルのファイルパス
		const char* TOOLS_MODEL_FILEPATH = "Assets/modelData/item/item_guardup.tkm";
		/// @brief 効果発動から終了までの時間
		const float DISAPPEARANCE_TIME = 3.0f;
		/// @brief 回復ダメージ
		const float RECOVERY_DAMAGE = -50.0f;

		void RepairTools::Activation()
		{
			//拠点に負のダメージを与えて回復させる
			m_defensiveTarget->ReceiveDamage(RECOVERY_DAMAGE);

			//効果発動フラグを立てる
			m_isActivate = true;
		}

		void RepairTools::InitData()
		{
			//変数を初期化
			m_itemType = enItemRepairTools;
			m_endTime = DISAPPEARANCE_TIME;

			//使用する情報を取得
			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);
		}

		void RepairTools::Spawn()
		{
			//モデルを作成
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->InitDeferrd(TOOLS_MODEL_FILEPATH);
		}

		void RepairTools::Efficacy()
		{

		}
	}
}