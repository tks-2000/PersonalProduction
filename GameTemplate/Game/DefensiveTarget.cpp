#include "stdafx.h"
#include "DefensiveTarget.h"

namespace mainGame {
	namespace defensiveTarget {

		/// @brief 防衛対象のモデルファイルパス
		const char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/bg/house.tkm";
		/// @brief 防衛対象のミニマップモデルのファイルパス
		const char* MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/boxMapModel.tkm";
		/// @brief 防衛対象のミニマップモデルのシェーダーファイルパス
		const char* MINI_MAP_MODEL_SHADER_FILEPATH = "Assets/shader/mapModel.fx";
		/// @brief 防衛対象の座標
		const Vector3 DEFENSIVE_TARGET_POS = { 0.0f,0.0f,0.0f };
		/// @brief 防衛対象の拡大率
		const Vector3 DEFENSIVE_TARGET_SCALE = { 1.0f,1.0f,1.0f };
		/// @brief 防衛対象の最大耐久力
		const int MAX_HP = 200;
		/// @brief 防衛対象の耐久力が減る速度
		const float HP_DECREACE_VEROCITY = 10.0f;
		/// @brief 耐久力の低下が止まる速度
		const float DAMAGE_STOP_AMOUNT = 0.01f;
		/// @brief 攻撃ポイントの座標
		const Vector3 ATTACKPOINT_POSTION[ATTACKPOINT_NUM] = {
			{250.0f,0.0f,0.0f},
			{-250.0f,0.0f,0.0f},
			{0.0f,0.0f,250.0f},
			{0.0f,0.0f,-250.0f},
			{250.0f,0.0f,250.0f},
			{250.0f,0.0f,-250.0f},
			{-250.0f,0.0f,250.0f},
			{-250.0f,0.0f,-250.0f}
		};
		/// @brief 一つの攻撃ポイントに集まれる最大人数
		const int MAX_TARGETD_NUM = 3;

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

			//防衛対象のモデルを作成
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_defensiveTargetModel->InitDeferrd(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH,true);
			//マップモデルを作成
			m_miniMapdefensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapdefensiveTargetModel->SetFxFilePath(MINI_MAP_MODEL_SHADER_FILEPATH);
			m_miniMapdefensiveTargetModel->Init(MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);

			//メンバ変数を初期化
			m_defensiveTargetHp = MAX_HP;
			m_defensiveTargetMaxHp = MAX_HP;
			m_position = DEFENSIVE_TARGET_POS;
			m_scale = DEFENSIVE_TARGET_SCALE;
			m_isBreak = false;

			m_defensiveTargetModel->SetPosition(m_position);
			m_defensiveTargetModel->Execution();
			

			//モデルの情報から当たり判定を作成
			m_staticDefensiveTargetObject.CreateFromModel(m_defensiveTargetModel->GetModel(),m_defensiveTargetModel->GetModelWorldMatrix());

			//攻撃ポイントを初期化
			for (int num = 0; num < m_attackPoints.size(); num++) {
				m_attackPoints[num].Init(this);
				m_attackPoints[num].SetPositon(ATTACKPOINT_POSTION[num]);
			}
			
			//初期化完了
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

				//攻撃ポイントの処理を実行
				for (int num = 0; num < m_attackPoints.size(); num++) {
					m_attackPoints[num].Execution();
				}

				//デバッグコマンド
				if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonSelect)) {
					//m_defensiveTargetHp = 0;
				}

				//拡大率を設定
				m_defensiveTargetModel->SetScale(m_scale);
				//モデルの処理を実行
				m_defensiveTargetModel->Execution();

				//ダメージ状態なら…
				if (m_isDamage == true) {
					//ダメージを受ける処理を行う
					ApplyDamage();
				}

				//耐久力が0以下になったら…
				if (m_defensiveTargetHp <= 0.0f) {
					//破壊されたことにする
					m_isBreak = true;

					//モデルを削除
					DeleteGO(m_defensiveTargetModel);
					DeleteGO(m_miniMapdefensiveTargetModel);
				}
			}
		}

		void DefensiveTarget::ReceiveDamage(const float damage)
		{
			//現在耐久力と受けたダメージ量からダメージ後の耐久力を計算する
			m_afterDamageHp = m_defensiveTargetHp;
			m_afterDamageHp -= damage;

			//ダメージ後の耐久力が0未満になったら…
			if (m_afterDamageHp < 0.0f) {
				//ダメージ後の耐久力を0にする
				m_afterDamageHp = 0.0f;
			}
			//ダメージ後の耐久力が最大耐久力を超えたら…
			if (m_afterDamageHp > m_defensiveTargetMaxHp) {
				//ダメージ後の耐久力を最大耐久力にする
				m_afterDamageHp = m_defensiveTargetMaxHp;
			}

			//ダメージを受けている状態に変更
			m_isDamage = true;
		}

		AttackPoint* DefensiveTarget::GetNearestAttackPoint(const Vector3& pos)
		{
			//攻撃ポイントの数だけターゲット可能かどうかのフラグを用意する
			bool targetdFlag[ATTACKPOINT_NUM] = { false };

			//攻撃ポイントの数だけ実行する
			for (int atpNum = 0; atpNum < m_attackPoints.size(); atpNum++) {
				//攻撃ポイントのターゲットされている人数が最大値に達していたとき…
				if (m_attackPoints[atpNum].GetTargetedNum() >= MAX_TARGETD_NUM) {
					//ターゲット不可にする
					targetdFlag[atpNum] = false;
				}
				//攻撃ポイントのターゲットされている人数が最大値に達していないとき…
				else {
					//ターゲット可能にする
					targetdFlag[atpNum] = true;
				}
				
			}

			//最も近い攻撃ポイントの番号に範囲外の数値を設定する
			int nearestNum = ATTACKPOINT_NUM;

			//攻撃ポイントの数だけ実行する
			for (int atpNum = 0; atpNum < m_attackPoints.size(); atpNum++) {
				//ターゲット可能でない場合…
				if (targetdFlag[atpNum] == false) {
					//次の攻撃ポイントを調べる
					continue;
				}
				//ターゲット可能な場合
				else {
					//現在の番号を仮の最も近い攻撃ポイントの番号に仮設定する
					nearestNum = atpNum;
					//繰り返しを終わる
					break;
				}
			}

			//最も近い攻撃ポイントの番号が範囲外の値のままだった場合…
			if (nearestNum == ATTACKPOINT_NUM) {
				//攻撃ポイントの配列の先頭を返す
				return &m_attackPoints[0];
			}

			//攻撃ポイントの数だけ実行する
			for (int targetNum = 0; targetNum < m_attackPoints.size(); targetNum++) {
				//ターゲット不可能のな場合…
				if (targetdFlag[targetNum] == false) {
					//次の繰り返しへ
					continue;
				}
				//現在の攻撃ポイントへのベクトルと最も近い攻撃ポイントへのベクトルを計算する
				Vector3 toTarget = m_attackPoints[targetNum].GetPostion() - pos;
				Vector3 toNearest = m_attackPoints[nearestNum].GetPostion() - pos;

				//現在の攻撃ポイントとの距離が最も近い攻撃ポイントの距離よりも小さかったら…
				if (toTarget.Length() < toNearest.Length()) {
					//最も近い攻撃ポイントの番号を現在の番号に変更する
					nearestNum = targetNum;
				}

			}
			//最も近い攻撃ポイントにターゲットされたことを伝える
			m_attackPoints[nearestNum].SetTargeted();
			//最も近い攻撃ポイント返す
			return &m_attackPoints[nearestNum];
		}

		void DefensiveTarget::ApplyDamage()
		{
			//現在の耐久力とダメージ後の耐久力の差から耐久力の低下量を求める
			float difference = m_defensiveTargetHp - m_afterDamageHp;
			//耐久力を減らす
			m_defensiveTargetHp -= difference * g_gameTime->GetFrameDeltaTime() * HP_DECREACE_VEROCITY;

			//耐久力の低下量がダメージ停止量以下になったら…
			if ((difference * difference) <= DAMAGE_STOP_AMOUNT) {
				//現在の耐久力をダメージ後の耐久力に変更
				m_defensiveTargetHp = m_afterDamageHp;
				//ダメージ状態を終了する
				m_isDamage = false;
			}
		}
	}
}