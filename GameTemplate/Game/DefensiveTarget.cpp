#include "stdafx.h"
#include "DefensiveTarget.h"

namespace mainGame {
	namespace defensiveTarget {

		/// @brief �h�q�Ώۂ̃��f���t�@�C���p�X
		const  char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/bg/house.tkm";

		const char* MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/boxMapModel.tkm";
		/// @brief �h�q�Ώۂ̍��W
		const Vector3 DEFENSIVE_TARGET_POS = { 0.0f,0.0f,0.0f };
		/// @brief �h�q�Ώۂ̍ő�ϋv��
		const int MAX_HP = 10000;

		const float HP_DECREACE_VEROCITY = 10.0f;

		const float DAMAGE_STOP_AMOUNT = 0.01f;

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

		DefensiveTarget::DefensiveTarget()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		DefensiveTarget::~DefensiveTarget()
		{
			//�j�󂳂�Ă��Ȃ��ꍇ�c
			if (m_isBreak == false) {
				//���f�����폜
				DeleteGO(m_defensiveTargetModel);
				DeleteGO(m_miniMapdefensiveTargetModel);
			}
		}

		void DefensiveTarget::Init()
		{

			//�h�q�Ώۂ̃��f����������
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(0);
			m_defensiveTargetModel->InitDeferrd(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH,true);

			m_miniMapdefensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapdefensiveTargetModel->SetFxFilePath("Assets/shader/mapModel.fx");
			m_miniMapdefensiveTargetModel->Init(MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);

			//�����p�����[�^�[������
			m_defensiveTargetHp = MAX_HP;
			m_defensiveTargetMaxHp = MAX_HP;
			m_position = DEFENSIVE_TARGET_POS;
			m_scale = { 1.0f,1.0f,1.0f };
			m_defensiveTargetModel->SetPosition(m_position);
			m_defensiveTargetModel->Execution();

			//���f���̏�񂩂瓖���蔻����쐬
			m_staticDefensiveTargetObject.CreateFromModel(m_defensiveTargetModel->GetModel(),m_defensiveTargetModel->GetModelWorldMatrix());


			for (int num = 0; num < m_attackPoints.size(); num++) {
				m_attackPoints[num].Init(this);
				m_attackPoints[num].SetPositon(ATTACKPOINT_POSTION[num]);
			}

			m_isInitd = true;
			m_isBreak = false;
		}


		void DefensiveTarget::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�j�󂳂�Ă��Ȃ��Ƃ��c
			if (m_isBreak == false) {
				for (int num = 0; num < m_attackPoints.size(); num++) {
					m_attackPoints[num].Execution();
				}
				if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonSelect)) {
					m_defensiveTargetHp = 0;
				}

				//�g�嗦��ݒ�
				m_defensiveTargetModel->SetScale(m_scale);
				//���f���̏��������s
				m_defensiveTargetModel->Execution();

				if (m_isDamage == true) {
					ApplyDamage();
				}

				//�ϋv�͂�0�ȉ��ɂȂ�����c
				if (m_defensiveTargetHp <= 0.0f) {
					//�j�󂳂ꂽ���Ƃɂ���
					m_isBreak = true;

					//���f�����폜
					DeleteGO(m_defensiveTargetModel);
					DeleteGO(m_miniMapdefensiveTargetModel);
				}
			}
		}

		void DefensiveTarget::ReceiveDamage(const float damage)
		{
			//���ݑϋv�͂Ǝ󂯂��_���[�W�ʂ���_���[�W��̑ϋv�͂��v�Z����
			m_afterDamageHp = m_defensiveTargetHp;
			m_afterDamageHp -= damage;

			//�_���[�W��̑ϋv�͂�0�����ɂȂ�����c
			if (m_afterDamageHp < 0.0f) {
				//�_���[�W��̑ϋv�͂�0�ɂ���
				m_afterDamageHp = 0.0f;
			}
			//�_���[�W��̑ϋv�͂��ő�ϋv�͂𒴂�����c
			if (m_afterDamageHp > m_defensiveTargetMaxHp) {
				//�_���[�W��̑ϋv�͂��ő�ϋv�͂ɂ���
				m_afterDamageHp = m_defensiveTargetMaxHp;
			}

			//�_���[�W���󂯂Ă����ԂɕύX
			m_isDamage = true;
		}

		AttackPoint* DefensiveTarget::GetNearestAttackPoint(const Vector3& pos)
		{

			bool targetdFlag[ATTACKPOINT_NUM] = { false };

			for (int atpNum = 0; atpNum < m_attackPoints.size(); atpNum++) {
				if (m_attackPoints[atpNum].GetTargetedNum() > 2) {
					targetdFlag[atpNum] = false;
				}
				else {
					targetdFlag[atpNum] = true;
				}
				
			}

			int nearestNum = ATTACKPOINT_NUM;

			for (int atpNum = 0; atpNum < m_attackPoints.size(); atpNum++) {
				if (targetdFlag[atpNum] == false) {
					continue;
				}
				else {
					nearestNum = atpNum;
					break;
				}
			}

			if (nearestNum == ATTACKPOINT_NUM) {
				return &m_attackPoints[0];
			}

			for (int targetNum = 0; targetNum < m_attackPoints.size(); targetNum++) {
				if (targetdFlag[targetNum] == false) {
					continue;
				}
				Vector3 toTarget = m_attackPoints[targetNum].GetPostion() - pos;
				Vector3 toNearest = m_attackPoints[nearestNum].GetPostion() - pos;

				if (toTarget.Length() < toNearest.Length()) {
					nearestNum = targetNum;
				}

			}
			m_attackPoints[nearestNum].SetTargeted();
			return &m_attackPoints[nearestNum];
		}

		void DefensiveTarget::ApplyDamage()
		{
			//���݂̑ϋv�͂ƃ_���[�W��̑ϋv�͂̍�����ϋv�͂̒ቺ�ʂ����߂�
			float difference = m_defensiveTargetHp - m_afterDamageHp;
			//�ϋv�͂����炷
			m_defensiveTargetHp -= difference * g_gameTime->GetFrameDeltaTime() * HP_DECREACE_VEROCITY;

			//�ϋv�͂̒ቺ�ʂ��_���[�W��~�ʈȉ��ɂȂ�����c
			if ((difference * difference) <= DAMAGE_STOP_AMOUNT) {
				//���݂̑ϋv�͂��_���[�W��̑ϋv�͂ɕύX
				m_defensiveTargetHp = m_afterDamageHp;
				//�_���[�W��Ԃ��I������
				m_isDamage = false;
			}

			/*if (m_defensiveTargetHp <= 0.0f) {
				m_defensiveTargetHp = 0.0f;
			}
			if (m_defensiveTargetHp > m_defensiveTargetMaxHp) {
				m_defensiveTargetHp = m_defensiveTargetMaxHp;
			}*/

		}
	}
}