#include "stdafx.h"
#include "DefensiveTarget.h"

namespace mainGame {
	namespace defensiveTarget {

		/// @brief �h�q�Ώۂ̃��f���t�@�C���p�X
		const char* DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/bg/house.tkm";
		/// @brief �h�q�Ώۂ̃~�j�}�b�v���f���̃t�@�C���p�X
		const char* MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH = "Assets/modelData/box/boxMapModel.tkm";
		/// @brief �h�q�Ώۂ̃~�j�}�b�v���f���̃V�F�[�_�[�t�@�C���p�X
		const char* MINI_MAP_MODEL_SHADER_FILEPATH = "Assets/shader/mapModel.fx";
		/// @brief �h�q�Ώۂ̍��W
		const Vector3 DEFENSIVE_TARGET_POS = { 0.0f,0.0f,0.0f };
		/// @brief �h�q�Ώۂ̊g�嗦
		const Vector3 DEFENSIVE_TARGET_SCALE = { 1.0f,1.0f,1.0f };
		/// @brief �h�q�Ώۂ̍ő�ϋv��
		const int MAX_HP = 200;
		/// @brief �h�q�Ώۂ̑ϋv�͂����鑬�x
		const float HP_DECREACE_VEROCITY = 10.0f;
		/// @brief �ϋv�͂̒ቺ���~�܂鑬�x
		const float DAMAGE_STOP_AMOUNT = 0.01f;
		/// @brief �U���|�C���g�̍��W
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
		/// @brief ��̍U���|�C���g�ɏW�܂��ő�l��
		const int MAX_TARGETD_NUM = 3;

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

			//�h�q�Ώۂ̃��f�����쐬
			m_defensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_defensiveTargetModel->InitDeferrd(DEFENSIVE_TARGET_MODEL_TKM_FILEPATH,true);
			//�}�b�v���f�����쐬
			m_miniMapdefensiveTargetModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_miniMapdefensiveTargetModel->SetFxFilePath(MINI_MAP_MODEL_SHADER_FILEPATH);
			m_miniMapdefensiveTargetModel->Init(MINI_MAP_DEFENSIVE_TARGET_MODEL_TKM_FILEPATH, render::model::enExpandModelGroup1);

			//�����o�ϐ���������
			m_defensiveTargetHp = MAX_HP;
			m_defensiveTargetMaxHp = MAX_HP;
			m_position = DEFENSIVE_TARGET_POS;
			m_scale = DEFENSIVE_TARGET_SCALE;
			m_isBreak = false;

			m_defensiveTargetModel->SetPosition(m_position);
			m_defensiveTargetModel->Execution();
			

			//���f���̏�񂩂瓖���蔻����쐬
			m_staticDefensiveTargetObject.CreateFromModel(m_defensiveTargetModel->GetModel(),m_defensiveTargetModel->GetModelWorldMatrix());

			//�U���|�C���g��������
			for (int num = 0; num < m_attackPoints.size(); num++) {
				m_attackPoints[num].Init(this);
				m_attackPoints[num].SetPositon(ATTACKPOINT_POSTION[num]);
			}
			
			//����������
			m_isInitd = true;
		}


		void DefensiveTarget::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�j�󂳂�Ă��Ȃ��Ƃ��c
			if (m_isBreak == false) {

				//�U���|�C���g�̏��������s
				for (int num = 0; num < m_attackPoints.size(); num++) {
					m_attackPoints[num].Execution();
				}

				//�f�o�b�O�R�}���h
				if (g_pad[PLAYER1_CONTROLLER_NUM]->IsTrigger(enButtonSelect)) {
					//m_defensiveTargetHp = 0;
				}

				//�g�嗦��ݒ�
				m_defensiveTargetModel->SetScale(m_scale);
				//���f���̏��������s
				m_defensiveTargetModel->Execution();

				//�_���[�W��ԂȂ�c
				if (m_isDamage == true) {
					//�_���[�W���󂯂鏈�����s��
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
			//�U���|�C���g�̐������^�[�Q�b�g�\���ǂ����̃t���O��p�ӂ���
			bool targetdFlag[ATTACKPOINT_NUM] = { false };

			//�U���|�C���g�̐��������s����
			for (int atpNum = 0; atpNum < m_attackPoints.size(); atpNum++) {
				//�U���|�C���g�̃^�[�Q�b�g����Ă���l�����ő�l�ɒB���Ă����Ƃ��c
				if (m_attackPoints[atpNum].GetTargetedNum() >= MAX_TARGETD_NUM) {
					//�^�[�Q�b�g�s�ɂ���
					targetdFlag[atpNum] = false;
				}
				//�U���|�C���g�̃^�[�Q�b�g����Ă���l�����ő�l�ɒB���Ă��Ȃ��Ƃ��c
				else {
					//�^�[�Q�b�g�\�ɂ���
					targetdFlag[atpNum] = true;
				}
				
			}

			//�ł��߂��U���|�C���g�̔ԍ��ɔ͈͊O�̐��l��ݒ肷��
			int nearestNum = ATTACKPOINT_NUM;

			//�U���|�C���g�̐��������s����
			for (int atpNum = 0; atpNum < m_attackPoints.size(); atpNum++) {
				//�^�[�Q�b�g�\�łȂ��ꍇ�c
				if (targetdFlag[atpNum] == false) {
					//���̍U���|�C���g�𒲂ׂ�
					continue;
				}
				//�^�[�Q�b�g�\�ȏꍇ
				else {
					//���݂̔ԍ������̍ł��߂��U���|�C���g�̔ԍ��ɉ��ݒ肷��
					nearestNum = atpNum;
					//�J��Ԃ����I���
					break;
				}
			}

			//�ł��߂��U���|�C���g�̔ԍ����͈͊O�̒l�̂܂܂������ꍇ�c
			if (nearestNum == ATTACKPOINT_NUM) {
				//�U���|�C���g�̔z��̐擪��Ԃ�
				return &m_attackPoints[0];
			}

			//�U���|�C���g�̐��������s����
			for (int targetNum = 0; targetNum < m_attackPoints.size(); targetNum++) {
				//�^�[�Q�b�g�s�\�̂ȏꍇ�c
				if (targetdFlag[targetNum] == false) {
					//���̌J��Ԃ���
					continue;
				}
				//���݂̍U���|�C���g�ւ̃x�N�g���ƍł��߂��U���|�C���g�ւ̃x�N�g�����v�Z����
				Vector3 toTarget = m_attackPoints[targetNum].GetPostion() - pos;
				Vector3 toNearest = m_attackPoints[nearestNum].GetPostion() - pos;

				//���݂̍U���|�C���g�Ƃ̋������ł��߂��U���|�C���g�̋�������������������c
				if (toTarget.Length() < toNearest.Length()) {
					//�ł��߂��U���|�C���g�̔ԍ������݂̔ԍ��ɕύX����
					nearestNum = targetNum;
				}

			}
			//�ł��߂��U���|�C���g�Ƀ^�[�Q�b�g���ꂽ���Ƃ�`����
			m_attackPoints[nearestNum].SetTargeted();
			//�ł��߂��U���|�C���g�Ԃ�
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
		}
	}
}