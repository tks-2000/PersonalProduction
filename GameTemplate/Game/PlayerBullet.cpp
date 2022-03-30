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
		/// @brief �e�ۃG�t�F�N�g�̊g�嗦
		const Vector3 SHOT_EFFECT_SCALE = { 20.0f,20.0f,20.0f };
		/// @brief �e�ۃG�t�F�N�g�̃t�@�C���p�X
		const wchar_t* BULLET_SE_FILEPATH = L"Assets/sound/se/bullet.wav";
		/// @brief �e�ۂ̉����̑傫��
		const float BULLET_SE_VOLUME = 0.1f;

		Bullet::Bullet()
		{
			m_isInitd = false;
		}

		Bullet::~Bullet()
		{
			//�G�t�F�N�g���~���č폜
			m_shotEffect->Stop(true);
			DeleteGO(m_shotEffect);
		}

		void Bullet::Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos, const Vector3& target)
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//�f�[�^���󂯎��
			m_playerAttack = plAttack;
			m_enemys = enemys;

			//�󂯎�������W����ړ����������߂�
			m_startPos = pos;
			m_position = m_startPos;
			m_target = target;
			m_moveDirection = m_target - m_startPos;
			m_moveDirection.Normalize();

			//�e�ۃG�t�F�N�g���쐬
			m_shotEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_shotEffect->Init(u"Assets/effect/shot_pl1.efk");
			m_shotEffect->SetScale(SHOT_EFFECT_SCALE);
			m_shotEffect->Play(true);

			//������ݒ�
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_bulletSoundID = m_soundPlayer->SetSE(BULLET_SE_FILEPATH);
			m_soundPlayer->SetSEVolume(m_bulletSoundID, BULLET_SE_VOLUME);
			m_soundPlayer->PlaySE(m_bulletSoundID);

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

			Quaternion qRot = Quaternion::Identity;

			qRot.SetRotationY(atan2(m_moveDirection.x, m_moveDirection.z));

			//�X�V���������G�t�F�N�g�ɓK�p
			m_shotEffect->SetPosition(m_position);
			m_shotEffect->SetRotation(qRot);
			m_shotEffect->Execution();
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

				if (enemyData->GetState() == enemy::enEnemyDown) {
					continue;
				}

				//�G�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				float matchRate = Dot(toEnemyVec, m_moveDirection);

				//�G�Ƃ̋��������ȉ��Ȃ�c
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && matchRate > BULLET_COLLISION_MATCH_RATE) {

					//�G�ɏՌ���������
					toEnemyVec.Normalize();
					enemyData->SetMoveSpeed(toEnemyVec * BULLET_IMPACT_FORCE);

					//�G�Ƀ_���[�W��^����
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