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

		void Enemy::Init(const int num, const EnEnemyType& type,const Vector3& pos)
		{
			if (m_isInitd == true || type == enEnemyTypeNum) {
				return;
			}

			m_enemyNum = num;

			m_enemyType = type;

			//�������W��ݒ�
			m_position = pos;
			//�̗�
			m_hp = MAX_HP;
			//�����o�N���X��������
			m_enemyMove.Init(num,type,m_position);
			m_enemyRotation.Init(num);
			m_enemyAttack.Init(type);
			m_enemyAnimation.Init(num);

			//���f�����A�j���[�V�����L��ŏ�����
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(
				ENEMY_MODEL_TKM_FILEPATH[type],
				ENEMY_MODEL_TKS_FILEPATH,
				m_enemyAnimation.GetAnimationClip(),
				m_enemyAnimation.GetAnimationNum(),
				enModelUpAxisY
			);

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
				m_position = m_enemyMove.MoveStop(m_position);
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
			m_deleteTimer += g_gameTime->GetFrameDeltaTime();

			if (m_deleteTimer > DELETE_TIME) {
				m_generator->DeleteEnemy(this,m_enemyNum);
				DeleteGO(this);
			}
		}
	}
}