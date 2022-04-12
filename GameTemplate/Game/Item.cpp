#include "stdafx.h"
#include "Item.h"

namespace mainGame {
	namespace item {
		/// @brief �A�C�e���̏o�����鎞��
		const float ITEM_SPAWN_TIME = 2.0f;
		/// @brief �A�C�e�������ł��鋗��
		const float ITEM_GET_DISTANCE = 100.0f;
		/// @brief ����s�^�C�}�[�̃��[�v����
		const float CANTGET_TIMER_LOOP_TIME = 1.0f;
		/// @brief ����s�̈ړ��J�n����
		const float CANTGET_MOVE_START_TIME = 0.4f;
		/// @brief ����s�̈ړ��I������
		const float CANTGET_MOVE_END_TIME = CANTGET_TIMER_LOOP_TIME - CANTGET_MOVE_START_TIME;
		/// @brief ���x
		const float VEROCITY = 200.0f;
		/// @brief �ړ����~���鋗��
		const float MOVE_STOP_LENGTH = 0.01f;

		Item::Item()
		{

		}

		Item::~Item()
		{
			//�v���C���[�ɓ��肳��Ă��Ȃ��ꍇ�c
			if (m_isPlayerGet == false) {
				//���f�����폜
				DeleteGO(m_itemModel);
			}
		}

		void Item::Init(ItemGenerator* itemGenerator, const Vector3& spawnPos)
		{
			//�g�p������������ė���
			m_player = FindGO<player::Player>(player::PLAYER_NAME);

			//�����o�ϐ���������
			m_itemGenerator = itemGenerator;
			m_isPlayerGet = false;
			m_isActivate = false;
			InitData();
			m_itemEffect.Init(this);
			m_itemSound.Init(this);
			m_spawnPos = spawnPos;
			m_position = spawnPos;

			//����������
			m_isInitd = true;
		}

		void Item::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�o�����Ă��Ȃ��ꍇ�c
			if (m_isSpawn == false) {
				//�o���^�C�}�[�����Z
				m_spawnTimer += g_gameTime->GetFrameDeltaTime();
				//�^�C�}�[���o�����Ԃ𒴂�����
				if (m_spawnTimer > ITEM_SPAWN_TIME) {
					//�o�����̏��������s
					Spawn();
					m_isSpawn = true;
				}
				//�o�����Ă��Ȃ��̂ŏ������I���
				return;
			}

			//�v���C���[�ɓ��肳��Ă��Ȃ��ꍇ�c
			if (m_isPlayerGet == false) {

				//����s���o�̈ړ����������s
				CantGetMove();
				
				//�A�C�e���̃��f�����X�V
				m_itemModel->SetPosition(m_position);
				m_itemModel->Execution();

				//�v���C���[�Ƃ̐ڐG������s��
				PlayerCollision();
			}

			//���ʔ������̏ꍇ�c
			if (m_isActivate == true) {
				//�������̏��������s
				Efficacy();

				//�������̃^�C�}�[�����Z
				m_activateTimer += g_gameTime->GetFrameDeltaTime();

				//�^�C�}�[���I�����ԂɒB������c
				if (m_activateTimer >= m_endTime) {
					//���g���폜
					m_itemGenerator->DeleteItem(this);
					DeleteEfficacy();
					DeleteGO(this);
				}
			}

			//�G�t�F�N�g�ƃT�E���h�����s
			m_itemEffect.Execution();
			m_itemSound.Execution();
		}

		void Item::InitData()
		{
			

			

		}

		void Item::Spawn()
		{
			
		}

		void Item::PlayerCollision()
		{
			//�v���C���[�Ƃ̋����𑪂�
			Vector3 toPlayerPos = m_player->GetPlayerPosition() - m_position;

			//�v���C���[�Ƃ̋��������苗�����̏ꍇ�c
			if (toPlayerPos.Length() < ITEM_GET_DISTANCE) {
				
				//�v���C���[�̃A�C�e���X���b�g�ɓ���邱�Ƃ��o�����ꍇ�c
				if (m_player->SetItemSlot(this) == true) {
					//�v���C���[�ɓ��肳�ꂽ�t���O�𗧂Ă�
					m_isPlayerGet = true;
					DeleteGO(m_itemModel);
					m_isCantGet = false;
				}
				//�v���C���[�̃A�C�e���X���b�g�ɓ���邱�Ƃ��o���Ȃ������ꍇ�c
				else {
					//����s�t���O�𗧂Ă�
					m_isCantGet = true;
				}

			}
			//�v���C���[�Ƃ̋��������苗���O�̏ꍇ�c
			else {
				//����s�t���O���~�낷
				m_isCantGet = false;
			}

		}

		void Item::CantGetMove()
		{
			//����s�t���O�������Ă���ꍇ�c
			if (m_isCantGet == true) {
				
				//����s�^�C�}�[�����Z
				m_cantGetTimer += g_gameTime->GetFrameDeltaTime();
				
				//�^�C�}�[���ړ��J�n���Ԃ𒴂��Ă��āA�ړ��I�����Ԗ����̏ꍇ�c
				if (m_cantGetTimer > CANTGET_MOVE_START_TIME && m_cantGetTimer < CANTGET_MOVE_END_TIME) {
					//�^�C�}�[�����[�v���Ԃ̔��������̏ꍇ�c
					if (m_cantGetTimer < CANTGET_TIMER_LOOP_TIME / 2.0f) {
						//y���W�����Z
						m_position.y += VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
					//�^�C�}�[�����[�v���Ԃ̔����𒴂��Ă���ꍇ�c
					else {
						//y���W�����Z
						m_position.y -= VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
				}
				//�^�C�}�[���ړ��J�n���Ԃ��O�A�ړ��I�����Ԃ𒴂��Ă���ꍇ�c
				else {
					//���݂̍��W����o�����̍��W�֐L�т�x�N�g�������
					Vector3 moveSpeed = m_spawnPos - m_position;

					//�o�����̍��W�Ƃ̋������ړ���~�������傫���ꍇ�c
					if (moveSpeed.Length() > MOVE_STOP_LENGTH) {
						//�o�����̈ʒu�Ɍ������Ĉړ�����
						moveSpeed.Normalize();
						m_position += moveSpeed * VEROCITY * g_gameTime->GetFrameDeltaTime();
					}
				}

				//�^�C�}�[�����[�v���Ԃ𒴂����ꍇ�c
				if (m_cantGetTimer > CANTGET_TIMER_LOOP_TIME) {
					//�^�C�}�[��0�ɖ߂�
					m_cantGetTimer = 0.0f;
				}
			}
			//����s�t���O�������Ă��Ȃ��ꍇ�c
			else {
				//���݂̍��W����o�����̍��W�֐L�т�x�N�g�������
				Vector3 moveSpeed = m_spawnPos - m_position;

				//�o�����̍��W�Ƃ̋������ړ���~�������傫���ꍇ�c
				if (moveSpeed.Length() > MOVE_STOP_LENGTH) {
					//�o�����̈ʒu�Ɍ������Ĉړ�����
					moveSpeed.Normalize();
					m_position += moveSpeed * VEROCITY * g_gameTime->GetFrameDeltaTime();
				}

				//����s�^�C�}�[��0�ɂ���
				m_cantGetTimer = 0.0f;
			}
		}

		void Item::Activation()
		{
			m_isActivate = true;
		}

		void Item::Efficacy()
		{
			
		}

		void Item::DeleteEfficacy()
		{
			
		}
		
	}
}