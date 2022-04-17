#include "stdafx.h"
#include "EnemyRotation.h"

namespace mainGame {
	namespace enemy {
		/// @brief ������������I��鎞��
		const float SEE_DIRECTION_END_TIME = 1.0f;
		/// @brief ���������ς��鎞��
		const float CHANGE_SEE_DIRECTION_TIME = 2.0f;
		/// @brief ��������̋t�̕��������I��鎞��
		const float SEE_REVERSE_DIRECTION_END_TIME = 3.0f;
		/// @brief �l�q�����I��鎞��
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
			//�g�p����������
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

			//�G�l�~�[���l�q�����Ă���ꍇ�c 
			if(m_enemy->GetState() == enEnemySeeTheSituation){
				//�l�q�����Ă���Ƃ��̏������s��
				ExecuteSeeTheSituation();
			}
			//�G�l�~�[���l�q�����Ă��Ȃ��ꍇ�c
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

			//��]�����f���ɐݒ�
			m_enemy->SetRotation(m_qRot);
		}

		void Rotation::StartSeeTheSituation()
		{
			//���݂̃x�N�g����ۑ�
			m_oldDirection = m_direction;
			//�O�ς��g���ėl�q��������������߂�
			m_seeTheSituationDir = Cross(m_direction, Vector3::AxisY);
			//�l�q����������̋t�����̃x�N�g�������߂�
			m_reverseSeeTheSituationDir = m_seeTheSituationDir * -1.0f;
			//���K�����ĕ����x�N�g���ɂ���
			m_seeTheSituationDir.Normalize();
			m_reverseSeeTheSituationDir.Normalize();
			//�l�q������^�C�}�[��0�ɂ���
			m_seeTheSituationTimer = 0.0f;
		}

		void Rotation::EndSeeTheSituation()
		{
			//�l�q������^�C�}�[��0�ɂ���
			m_seeTheSituationTimer = 0.0f;
		}

		void Rotation::ExecuteSeeTheSituation()
		{
			//�l�q������^�C�}�[�����Z
			m_seeTheSituationTimer += g_gameTime->GetFrameDeltaTime();
	
			//�l�q������^�C�}�[��������������I��鎞�Ԉȉ��̏ꍇ�c
			if (m_seeTheSituationTimer <= SEE_DIRECTION_END_TIME) {
				//�ȑO�̕����ƌ���������^�C�}�[�Ő��`�⊮���������ɂ���
				m_direction.Lerp(m_seeTheSituationTimer, m_oldDirection, m_seeTheSituationDir);
			}
			//�l�q������^�C�}�[��������������I��鎞�Ԃ𒴂��āA���������ς��鎞�Ԉȉ��̏ꍇ�c
			else if(SEE_DIRECTION_END_TIME< m_seeTheSituationTimer && m_seeTheSituationTimer <= CHANGE_SEE_DIRECTION_TIME){
				//�⊮�����^�C�}�[�Ɖ߂������Ԃ��狁�߂�
				float rate = m_seeTheSituationTimer - SEE_DIRECTION_END_TIME;
				//��������ƈȑO�̕�����⊮���Ő��`�⊮���������ɂ���
				m_direction.Lerp(rate, m_seeTheSituationDir,m_oldDirection);
			}
			//�l�q������^�C�}�[�����������ς��鎞�Ԃ𒴂��āA�t���������I��鎞�Ԉȉ��̏ꍇ�c
			else if (CHANGE_SEE_DIRECTION_TIME < m_seeTheSituationTimer && m_seeTheSituationTimer <= SEE_REVERSE_DIRECTION_END_TIME) {
				//�⊮�����^�C�}�[�Ɖ߂������Ԃ��狁�߂�
				float rate = m_seeTheSituationTimer - CHANGE_SEE_DIRECTION_TIME;
				//�ȑO�̕����ƌ�������̋t������⊮���Ő��`�⊮���������ɂ���
				m_direction.Lerp(rate, m_oldDirection, m_reverseSeeTheSituationDir);
			}
			///�l�q������^�C�}�[���t���������I��鎞�Ԃ𒴂��āA�l�q�����I��鎞�Ԉȉ��̏ꍇ�c
			else if(SEE_REVERSE_DIRECTION_END_TIME < m_seeTheSituationTimer && m_seeTheSituationTimer <= SEE_THE_SITUATION_END_TIME){
				//�⊮�����^�C�}�[�Ɖ߂������Ԃ��狁�߂�
				float rate = m_seeTheSituationTimer - SEE_REVERSE_DIRECTION_END_TIME;
				//��������̋t�����ƈȑO�̕�����⊮���Ő��`�⊮���������ɂ���
				m_direction.Lerp(rate, m_reverseSeeTheSituationDir,m_oldDirection);
			}
			//�l�q������^�C�}�[���l�q�����I��鎞�Ԃ𒴂����ꍇ�c
			else {
				//�G�l�~�[��ҋ@��Ԃɂ���
				m_enemy->SetState(enEnemyIdle);
			}

		}
	}
}