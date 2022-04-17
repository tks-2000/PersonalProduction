#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {
		/// @brief 見る方向を見終わる時間
		const float SEE_DIRECTION_END_TIME = 1.0f;
		/// @brief 見る方向を変える時間
		const float CHANGE_SEE_DIRECTION_TIME = 2.0f;
		/// @brief 見る方向の逆の方向を見終わる時間
		const float SEE_REVERSE_DIRECTION_END_TIME = 3.0f;
		/// @brief 様子を見終わる時間
		const float SEE_THE_SITUATION_END_TIME = 4.0f;

		Rotation::Rotation()
		{
			//未初期化で開始
			m_isInitd = false;
		}

		Rotation::~Rotation()
		{

		}

		void Rotation::Init(Enemy* enemy)
		{
			//使用する情報を入手
			m_enemy = enemy;

			//初期化完了
			m_isInitd = true;
		}

		void Rotation::RotationExecute()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//エネミーが様子を見ている場合… 
			if(m_enemy->GetState() == enEnemySeeTheSituation){
				//様子を見ているときの処理を行う
				ExecuteSeeTheSituation();
			}
			//エネミーが様子を見ていない場合…
			else {
				//移動速度から方向を決める
				m_direction = m_enemy->GetMoveSpeed();
				
			}

			//移動していない場合…
			if (m_direction.Length() == 0.0f) {
				//実行せずに返す
				return;
			}

			//Y方向の移動成分を打ち消す
			m_direction.y = 0.0f;
			//正規化して方向ベクトルにする
			m_direction.Normalize();

			//移動方向から回転を求める
			m_angle = atan2(m_direction.x, m_direction.z);

			//Y軸方向で回転させる
			m_qRot.SetRotationY(m_angle);

			//回転をモデルに設定
			m_enemy->SetRotation(m_qRot);
		}

		void Rotation::StartSeeTheSituation()
		{
			//現在のベクトルを保存
			m_oldDirection = m_direction;
			//外積を使って様子を見る方向を決める
			m_seeTheSituationDir = Cross(m_direction, Vector3::AxisY);
			//様子を見る方向の逆向きのベクトルを求める
			m_reverseSeeTheSituationDir = m_seeTheSituationDir * -1.0f;
			//正規化して方向ベクトルにする
			m_seeTheSituationDir.Normalize();
			m_reverseSeeTheSituationDir.Normalize();
			//様子を見るタイマーを0にする
			m_seeTheSituationTimer = 0.0f;
		}

		void Rotation::EndSeeTheSituation()
		{
			//様子を見るタイマーを0にする
			m_seeTheSituationTimer = 0.0f;
		}

		void Rotation::ExecuteSeeTheSituation()
		{
			//様子を見るタイマーを加算
			m_seeTheSituationTimer += g_gameTime->GetFrameDeltaTime();
	
			//様子を見るタイマーが見る方向を見終わる時間以下の場合…
			if (m_seeTheSituationTimer <= SEE_DIRECTION_END_TIME) {
				//以前の方向と見る方向をタイマーで線形補完した方向にする
				m_direction.Lerp(m_seeTheSituationTimer, m_oldDirection, m_seeTheSituationDir);
			}
			//様子を見るタイマーが見る方向を見終わる時間を超えて、見る方向を変える時間以下の場合…
			else if(SEE_DIRECTION_END_TIME< m_seeTheSituationTimer && m_seeTheSituationTimer <= CHANGE_SEE_DIRECTION_TIME){
				//補完率をタイマーと過ぎた時間から求める
				float rate = m_seeTheSituationTimer - SEE_DIRECTION_END_TIME;
				//見る方向と以前の方向を補完率で線形補完した方向にする
				m_direction.Lerp(rate, m_seeTheSituationDir,m_oldDirection);
			}
			//様子を見るタイマーが見る方向を変える時間を超えて、逆方向を見終わる時間以下の場合…
			else if (CHANGE_SEE_DIRECTION_TIME < m_seeTheSituationTimer && m_seeTheSituationTimer <= SEE_REVERSE_DIRECTION_END_TIME) {
				//補完率をタイマーと過ぎた時間から求める
				float rate = m_seeTheSituationTimer - CHANGE_SEE_DIRECTION_TIME;
				//以前の方向と見る方向の逆方向を補完率で線形補完した方向にする
				m_direction.Lerp(rate, m_oldDirection, m_reverseSeeTheSituationDir);
			}
			///様子を見るタイマーが逆方向を見終わる時間を超えて、様子を見終わる時間以下の場合…
			else if(SEE_REVERSE_DIRECTION_END_TIME < m_seeTheSituationTimer && m_seeTheSituationTimer <= SEE_THE_SITUATION_END_TIME){
				//補完率をタイマーと過ぎた時間から求める
				float rate = m_seeTheSituationTimer - SEE_REVERSE_DIRECTION_END_TIME;
				//見る方向の逆方向と以前の方向を補完率で線形補完した方向にする
				m_direction.Lerp(rate, m_reverseSeeTheSituationDir,m_oldDirection);
			}
			//様子を見るタイマーが様子を見終わる時間を超えた場合…
			else {
				//エネミーを待機状態にする
				m_enemy->SetState(enEnemyIdle);
			}

		}
	}
}