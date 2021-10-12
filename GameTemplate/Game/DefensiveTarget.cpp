#include "stdafx.h"
#include "DefensiveTarget.h"

namespace {
	/// @brief 防衛対象のモデルファイルパス
	const  char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/box2.tkm";
	/// @brief 防衛対象の最大耐久力
	const float MAX_HP = 100.0f;
}

namespace mainGame {
	namespace defensiveTarget {
		DefensiveTarget::DefensiveTarget()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		DefensiveTarget::~DefensiveTarget()
		{
			//破壊されていない場合…
			if (m_isBreak == false) {
				//モデルを削除
				DeleteGO(m_defensiveTargetModel);
			}
		}

		void DefensiveTarget::Init()
		{
			//防衛対象のモデルを初期化
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(0);
			m_defensiveTargetModel->Init(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH);

			//初期パラメーターを決定
			m_defensiveTargetHp = MAX_HP;
			m_scale = { 2.0f,2.0f,2.0f };
			m_isInitd = true;
		}


		void DefensiveTarget::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//破壊されていないとき…
			if (m_isBreak == false) {

				//拡大率を設定
				m_defensiveTargetModel->SetScale(m_scale);
				//モデルの処理を実行
				m_defensiveTargetModel->Execution();

				//耐久力が0以下になったら…
				if (m_defensiveTargetHp <= 0) {
					m_defensiveTargetHp = 0;
					//破壊されたことにする
					m_isBreak = true;

					//モデルを削除
					DeleteGO(m_defensiveTargetModel);
				}
			}
		}
	}
}