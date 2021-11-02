#include "stdafx.h"
#include "PlayerBullet.h"

namespace mainGame {
	namespace player {
		/// @brief �e�ۂ̑��x
		const float BULLET_VEROCITY = 3000.0f;
		/// @brief �G�ƐڐG���鋗��
		const float ENEMY_COLLISION_DISTANCE = 200.0f;
		/// @brief �폜�����ړ�����
		const float DELETE_MOVE_DISTANCE = 3000.0f;
		/// @brief �G�ɗ^����Ռ���
		const float BULLET_IMPACT_FORCE = 2000.0f;
		/// @brief �G�ɗ^����_���[�W
		const int BULLET_DAMAGE = 1;
		/// @brief �e�ۂ̐ڐG���������v��
		const float BULLET_COLLISION_MATCH_RATE = 0.0f;

		Bullet::Bullet()
		{
			m_isInitd = false;
		}

		Bullet::~Bullet()
		{
			DeleteGO(m_bulletModel);
		}

		void Bullet::Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos, const Vector3& target)
		{
			if (m_isInitd == true) {
				return;
			}

			//�f�[�^���󂯎��
			m_playerAttack = plAttack;
			m_enemys = enemys;

			//�e�ۂ̃��f����������
			m_bulletModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_bulletModel->Init("Assets/modelData/sphere/sphere.tkm");
			m_bulletModel->SetScale({ 0.7f,0.7f,0.7f });

			//�󂯎�������W����ړ����������߂�
			m_startPos = pos;
			m_position = m_startPos;
			m_target = target;
			m_moveDirection = m_target - m_startPos;
			m_moveDirection.Normalize();

			//����������
			m_isInitd = true;
		}

		void Bullet::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�ړ��ƐڐG��������s
			MoveExecution();
			EnemyCollision();

			//���f���ɍX�V�����f�[�^��K�p
			m_bulletModel->SetPosition(m_position);
			m_bulletModel->Execution();
		}

		void Bullet::MoveExecution()
		{
			//�ړ������Ƒ��x�ňړ����x�����߂�
			m_moveSpeed = m_moveDirection * BULLET_VEROCITY * g_gameTime->GetFrameDeltaTime();

			//���W�Ɉړ����x��������
			m_position += m_moveSpeed;

			//�������W���玩���̈ړ��x�N�g�������߂�
			Vector3 moveVec = m_position - m_startPos;

			//�ړ��x�N�g�������ȏ�Ȃ�c
			if (moveVec.Length() > DELETE_MOVE_DISTANCE) {
				//���g���폜
				DeleteThis();
			}
		}

		void Bullet::EnemyCollision()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				float matchRate = Dot(toEnemyVec, m_moveDirection);

				//�G�Ƃ̋��������ȉ��Ȃ�c
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && matchRate > BULLET_COLLISION_MATCH_RATE) {

					//�G�ɏՌ���������
					toEnemyVec.Normalize();
					enemyData->SetMoveSpeed(toEnemyVec * BULLET_IMPACT_FORCE);

					//�G�Ƀ_���[�W��^����
					enemyData->SetState(enemy::enEnemyDamage);
					enemyData->ReceiveDamage(BULLET_DAMAGE);

					//���g���폜
					DeleteThis();
				}
			}
		}

		void Bullet::DeleteThis()
		{
			//�v���C���[�̍U���𐧌䂷��N���X�Ɏ��g�̍폜��`����
			m_playerAttack->DeleteBullet(this);
			DeleteGO(this);
		}
	}
}