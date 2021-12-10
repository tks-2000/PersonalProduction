#include "stdafx.h"
#include "Bomb.h"

namespace mainGame {
	namespace item {

		/// @brief �G�ƐڐG���鋗��
		const float ENEMY_COLLISION_DISTANCE = 100.0f;
		/// @brief �e�ۂƐڐG���鋗��
		const float BULLET_COLLISION_DISTANCE = 200.0f;
		/// @brief �������a
		const float EXPLOSION_RADIUS = 500.0f;
		/// @brief �����̏Ռ���
		const float EXPLOSION_IMPACT = 5000.0f;
		/// @brief �����̃_���[�W��
		const int EXPLOSION_DAMAGE = 10;
		/// @brief ���R���ł��鎞��
		const float DISAPPEARANCE_TIME = 10.0f;
		/// @brief �������Ă�����ł��鎞��
		const float EXPLOSION_DISAPPEARANCE_TIME = 3.0f;
		/// @brief �v���C���[�̋ߐڍU����������͈�
		const float PLAYER_MELEE_ATTACK_COLLISION_DISTANCE = 200.0f;
		/// @brief �v���C���[�̋ߐڍU����������p�x�̈�v��
		const float PLAYER_MELEE_ATTACK_COLLISION_DOT_RATE = 0.0f;
		/// @brief 
		const float NORMAL_MOVE_VEROCITY = 1000.0f;
		/// @brief 
		const float FAST_MOVE_SPEED = 2000.0f;

		const float SET_DISTANCE = 150.0f;

		const float SET_HEIGHT = 50.0f;

		Bomb::~Bomb()
		{
			if (m_modelFlag == true) {
				DeleteGO(m_itemModel);
			}
		}

		void Bomb::InitData()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);

			m_enemys = m_enemyGenerator->GetEnemys();

			m_bullets = m_player->GetBulletData();

			m_endTime = DISAPPEARANCE_TIME;
		}

		void Bomb::Activation()
		{
			m_isActivate = true;

			Vector3 setPos = m_player->GetPlayerDirection() * SET_DISTANCE;

			setPos = m_player->GetPlayerPosition() + setPos;

			setPos.y += SET_HEIGHT;

			m_position = setPos;

			CreateModel();
		}

		void Bomb::Efficacy()
		{
			if (m_modelFlag == true) {

				m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
				
				m_itemModel->SetPosition(m_position);
				m_itemModel->Execution();

				PlayerMeleeAttackCollision();

				EnemyCollision();

				BulletCollision();
			}
		}

		void Bomb::CreateModel()
		{
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->Init("Assets/modelData/sphere/sphere.tkm");

			m_modelFlag = true;
		}

		void Bomb::EnemyCollision()
		{
			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//�G�Ƃ̋������ڐG�����ȉ��Ȃ�c
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE) {

					//��������
					Explosion();
				}
			}
		}

		void Bomb::BulletCollision()
		{
			//�e�ۂ̐��������s����
			for (int bulletNum = 0; bulletNum < m_bullets->size(); bulletNum++) {
				//�e�ۂ̏������o��
				player::Bullet* bulletData = *(m_bullets->begin() + bulletNum);

				//�e�ۂ֐L�т�x�N�g�������߂�
				Vector3 toBulletVec = bulletData->GetPosition() - m_position;

				//�e�ۂƂ̋������ڐG�����ȉ���������c
				if (toBulletVec.Length() < BULLET_COLLISION_DISTANCE) {

					//��������
					Explosion();
				}

			}
		}

		void Bomb::PlayerMeleeAttackCollision()
		{
			//�v���C���[���U��������o���Ă��Ȃ�������c
			if (m_player->IsAttackJudgement() == false) {
				//�������I���
				return;
			}

			//�v���C���[�̈ʒu�Ǝ��g�̈ʒu����v���C���[���玩���ɐL�т�x�N�g�������߂�
			Vector3 playerToVec = m_position - m_player->GetPlayerPosition();
			//y�����̐���������
			playerToVec.y = 0.0f;

			
			//�v���C���[���玩�g�܂ł̋������ڐG�������������c
			if (playerToVec.Length() < PLAYER_MELEE_ATTACK_COLLISION_DISTANCE) {

				//���K�����đ傫��1�̃x�N�g���ɂ���
				playerToVec.Normalize();
				//�v���C���[���玩���ւ̃x�N�g���ƃv���C���[�̌����̓��ς����߂�
				float matchRate = Dot(m_player->GetPlayerDirection(), playerToVec);

				//�v���C���[���t���`���[�W��Ԃ�������c
				if (m_player->IsFollCharge() == true) {
					//�v���C���[���玩���ւ̃x�N�g���ő����ړ�����
					m_moveSpeed = playerToVec * FAST_MOVE_SPEED;
				}
				//�v���C���[���t���`���[�W��ԂłȂ��ꍇ
				else {
					//�p�x��v�����v���C���[�̍U���\�Ȋp�x��v����傫���ꍇ�c
					if (matchRate > m_player->GetAttackPossibleMatchRate()) {
						//�v���C���[���玩���ւ̃x�N�g���ňړ�����
						m_moveSpeed = playerToVec * NORMAL_MOVE_VEROCITY;
					}
				}
			}
		}

		void Bomb::Explosion()
		{
			//�A�C�e���̏��ł܂ł̎��Ԃ����ɖ߂�
			m_activateTimer = 0.0f;

			//���ł܂ł̎��Ԃ�V�����ݒ�
			m_endTime = EXPLOSION_DISAPPEARANCE_TIME;

			//�G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//�G�Ƃ̋������������a�ȉ��Ȃ�c
				if (toEnemyVec.Length() < EXPLOSION_RADIUS) {

					//�G�ւƐL�т�x�N�g���𐳋K��
					toEnemyVec.Normalize();

					//�G�ɏՌ���������
					enemyData->SetMoveSpeed(toEnemyVec * EXPLOSION_IMPACT);

					//�G���_���[�W��ԂɕύX
					enemyData->SetState(enemy::enEnemyDamage);

					//�G�ɔ����̃_���[�W��^����
					enemyData->ReceiveDamage(EXPLOSION_DAMAGE);
				}
			}

			//���f�����폜
			DeleteGO(m_itemModel);

			m_modelFlag = false;
		}
	}
}