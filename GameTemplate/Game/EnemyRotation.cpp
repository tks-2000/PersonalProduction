#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {

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
			//受け取った番号の敵クラス情報を入手
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

			if(m_enemy->GetState() == enEnemySeeTheSituation){
				ExecuteSeeTheSituation();
			}
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

			m_enemy->SetRotation(m_qRot);
		}

		void Rotation::StartSeeTheSituation()
		{
			m_oldDirection = m_direction;
			m_seeTheSituationDir = Cross(m_direction, Vector3::AxisY);
			m_reverseSeeTheSituationDir = m_seeTheSituationDir * -1.0f;
			m_seeTheSituationDir.Normalize();
			m_reverseSeeTheSituationDir.Normalize();
			m_seeTheSituationTimer = 0.0f;
		}

		void Rotation::EndSeeTheSituation()
		{
			m_seeTheSituationFlag = false;
			m_seeTheSituationTimer = 0.0f;
		}

		void Rotation::ExecuteSeeTheSituation()
		{
			m_seeTheSituationTimer += g_gameTime->GetFrameDeltaTime();

			

			if (m_seeTheSituationTimer <= 1.0f) {
				m_direction.Lerp(m_seeTheSituationTimer, m_oldDirection, m_seeTheSituationDir);
			}
			else if(1.0f< m_seeTheSituationTimer && m_seeTheSituationTimer <= 2.0f){
				float rate = m_seeTheSituationTimer-1.0f;
				
				m_direction.Lerp(rate, m_seeTheSituationDir,m_oldDirection);
			}
			else if (2.0f < m_seeTheSituationTimer && m_seeTheSituationTimer <= 3.0f) {
				float rate = m_seeTheSituationTimer - 2.0f;

				m_direction.Lerp(rate, m_oldDirection, m_reverseSeeTheSituationDir);
			}
			else if(3.0f < m_seeTheSituationTimer && m_seeTheSituationTimer <= SEE_THE_SITUATION_END_TIME){
				float rate = m_seeTheSituationTimer - 3.0f;

				m_direction.Lerp(rate, m_seeTheSituationDir * -1.0f,m_oldDirection);
			}
			else {
				m_enemy->SetState(enEnemyIdle);
			}

		}
	}
}