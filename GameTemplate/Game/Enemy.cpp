#include "stdafx.h"
#include "Enemy.h"

namespace {
	
	
}

namespace mainGame {
	namespace enemy {

		/// @brief �G���f���̃t�@�C���p�X
		const char* ENEMY_MODEL_TKM_FILEPATH[enEnemyTypeNum] = {
			"Assets/modelData/unityChan/utc_green.tkm",
			"Assets/modelData/unityChan/utc_red.tkm",
			"Assets/modelData/unityChan/utc_blue.tkm"
		};


		/// @brief �G���f���̃X�P���g���t�@�C���p�X
		const char* ENEMY_MODEL_TKS_FILEPATH = "Assets/modelData/unityChan/unityChan.tks";
		/// @brief �G�̍ő�̗�
		const int MAX_HP = 3;
		/// @brief �A�j���[�V�����⊮��
		const float ANIMATION_COMPLEMENTARY_RATE = 0.2f;
		/// @brief �폜�����܂ł̎���
		const float DELETE_TIME = 5.0f;

		Enemy::Enemy()
		{
			//���������ŊJ�n
			m_isInitd = false;
		}

		Enemy::~Enemy()
		{
			m_player->DeleteEnemyData(this);
			DeleteGO(m_enemyModel);
		}

		void Enemy::Init(const EnemyInitData& initData)
		{
			//�������ς݁E��������񂪐������Ȃ��ꍇ���s���Ȃ�
			if (m_isInitd == true || initData.enemyNum == ENEMY_UNINITD_NUMBER || initData.enemyType == enEnemyTypeNum) {
				return;
			}

			//���g�̔ԍ���ݒ�
			m_enemyNum = initData.enemyNum;
			
			//���g�̃^�C�v��ݒ�
			m_enemyType = initData.enemyType;

			//�������W��ݒ�
			m_position = initData.enemyStartPos;

			//�̗�
			m_hp = MAX_HP;

			//�����o�N���X��������
			m_enemyMove.Init(this);
			m_enemyRotation.Init(this);
			m_enemyAttack.Init(this);
			m_enemyAnimation.Init(this);

			//���f�����A�j���[�V�����L��ŏ�����
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				ENEMY_MODEL_TKM_FILEPATH[initData.enemyType],
				ENEMY_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);

			//�G������̏������
			m_generator = FindGO<Generator>(ENEMY_GENERATOR_NAME);
			//�v���C���[�̏������
			m_player = FindGO<player::Player>(player::PLAYER_NAME);
			//�v���C���[�Ɏ����̏���ǉ�
			m_player->SetEnemyData(this);
			//�ҋ@���ŊJ�n
			m_state = enEnemyIdle;
			//����������
			m_isInitd = true;
		}

		void Enemy::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�����̃X�e�[�g�ɂ���ď����𕪂���
			switch (m_state)
			{
				//�ҋ@
			case enEnemyIdle: {
				m_position = m_enemyMove.IdleExecute(m_position);
			}break;
				//�ړ�
			case enEnemyMove: {
				m_position = m_enemyMove.MoveExecute(m_position);
			}break;
				//�U��
			case enEnemyAttack: {
				//m_position = m_enemyMove.MoveStop(m_position);
				m_enemyAttack.Execution();
			}break;
				//�_���[�W
			case enEnemyDamage: {
				m_position = m_enemyMove.IdleExecute(m_position);
			}break;
				//�_�E��
			case enEnemyDown: {
				m_position = m_enemyMove.MoveStop(m_position);
				DownExecution();
			}break;
			default:
				break;
			}

			//��]��K�p
			m_qRot = m_enemyRotation.RotationExecute(m_enemyMove.GetMoveSpeed());

			//�A�j���[�V������i�߂�
			m_enemyAnimation.AnimationUpdate();
			
			//���f���ɍX�V���ꂽ����`����
			m_enemyModel->SetPosition(m_position);

			m_enemyModel->SetRotation(m_qRot);

			m_enemyModel->PlayAnimation(m_enemyAnimation.GetAnimationState(), ANIMATION_COMPLEMENTARY_RATE);

			m_enemyModel->Execution();

			if (m_position.y < -1000.0f) {
				//������ɍ폜��`����
				m_generator->DeleteEnemy(this);
				//���g���폜
				DeleteGO(this);
			}
		}

		void Enemy::ReceiveDamage(const int damage)
		{
			//�_���[�W���󂯂�
			m_hp -= damage;

			//�̗͂�0�ȉ��ɂȂ�����
			if (m_hp <= 0) {
				//�_�E����ԂɈڍs
				m_state = enEnemyDown;
				m_hp = 0;
			}
		}

		void Enemy::DownExecution()
		{
			//�폜�܂ł̎��Ԃ�i�߂�
			m_deleteTimer += g_gameTime->GetFrameDeltaTime();

			//�폜���ԂɒB������c
			if (m_deleteTimer > DELETE_TIME) {
				//������ɍ폜��`����
				m_generator->DeleteEnemy(this);
				//���g���폜
				DeleteGO(this);
			}
		}
	}
}