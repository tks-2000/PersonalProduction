#include "stdafx.h"
#include "DefensiveTarget.h"

namespace {
	/// @brief 防衛対象のモデルファイルパス
	const  char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/box2.tkm";

	const char* MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/boxMapModel.tkm";
	/// @brief 防衛対象の座標
	const Vector3 DEFENSIVE_TARGET_POS = { 0.0f,0.0f,0.0f };
	/// @brief 防衛対象の最大耐久力
	const int MAX_HP = 100;
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
				DeleteGO(m_miniMapdefensiveTargetModel);
			}
		}

		void DefensiveTarget::Init()
		{

			//防衛対象のモデルを初期化
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(0);
			m_defensiveTargetModel->Init(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH);

			m_miniMapdefensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapdefensiveTargetModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapdefensiveTargetModel->Init(MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);

			//初期パラメーターを決定
			m_defensiveTargetHp = MAX_HP;
			m_position = DEFENSIVE_TARGET_POS;
			m_scale = { 1.0f,1.0f,1.0f };
			m_defensiveTargetModel->SetPosition(m_position);
			m_defensiveTargetModel->Execution();

			//モデルの情報から当たり判定を作成
			m_staticDefensiveTargetObject.CreateFromModel(m_defensiveTargetModel->GetModel(),m_defensiveTargetModel->GetModelWorldMatrix());
			m_isInitd = true;
			m_isBreak = false;
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
					DeleteGO(m_miniMapdefensiveTargetModel);
				}
			}
		}
	}
}