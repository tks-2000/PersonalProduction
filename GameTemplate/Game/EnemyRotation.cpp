#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {

		const float SEE_THE_SITUATION_END_TIME = 4.0f;

		Rotation::Rotation()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Rotation::~Rotation()
		{

		}

		void Rotation::Init(Enemy* enemy)
		{
			//�󂯎�����ԍ��̓G�N���X�������
			m_enemy = enemy;

			//����������
			m_isInitd = true;
		}

		void Rotation::RotationExecute()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			if(m_enemy->GetState() == enEnemySeeTheSituation){
				ExecuteSeeTheSituation();
			}
			else {
				//�ړ����x������������߂�
				m_direction = m_enemy->GetMoveSpeed();
				
			}

			//�ړ����Ă��Ȃ��ꍇ�c
			if (m_direction.Length() == 0.0f) {
				//���s�����ɕԂ�
				return;
			}

			//Y�����̈ړ�������ł�����
			m_direction.y = 0.0f;
			//���K�����ĕ����x�N�g���ɂ���
			m_direction.Normalize();

			//�ړ����������]�����߂�
			m_angle = atan2(m_direction.x, m_direction.z);

			//Y�������ŉ�]������
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