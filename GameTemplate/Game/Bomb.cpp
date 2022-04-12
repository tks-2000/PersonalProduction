#include "stdafx.h"
#include "Bomb.h"

namespace mainGame {
	namespace item {
		/// @brief �A�C�e���̃��f���̃t�@�C���p�X
		const char* ITEM_MODEL_FILEPATH = "Assets/modelData/item/item_attackup.tkm";
		/// @brief ���e�̃��f���̃t�@�C���p�X
		const char* BOMB_MODEL_FILEPATH = "Assets/modelData/sphere/sphere.tkm";
		/// @brief �G�ƐڐG���鋗��
		const float ENEMY_COLLISION_DISTANCE = 100.0f;
		/// @brief �e�ۂƐڐG���鋗��
		const float BULLET_COLLISION_DISTANCE = 200.0f;
		/// @brief �������a
		const float EXPLOSION_RADIUS = 500.0f;
		/// @brief �����̏Ռ���
		const float EXPLOSION_IMPACT = 5000.0f;
		/// @brief �����̃_���[�W��
		const int EXPLOSION_DAMAGE = 1;
		/// @brief ���R���ł��鎞��
		const float DISAPPEARANCE_TIME = 10.0f;
		/// @brief �������Ă�����ł��鎞��
		const float EXPLOSION_DISAPPEARANCE_TIME = 3.0f;
		/// @brief �v���C���[�̋ߐڍU����������͈�
		const float PLAYER_MELEE_ATTACK_COLLISION_DISTANCE = 200.0f;
		/// @brief �v���C���[�̋ߐڍU����������p�x�̈�v��
		const float PLAYER_MELEE_ATTACK_COLLISION_DOT_RATE = 0.0f;
		/// @brief �ʏ�̈ړ����x
		const float NORMAL_MOVE_VEROCITY = 1000.0f;
		/// @brief �����ړ����x
		const float FAST_MOVE_SPEED = 2000.0f;
		/// @brief �Z�b�g���鋗��
		const float SET_DISTANCE = 150.0f;
		/// @brief �Z�b�g���鍂��
		const float SET_HEIGHT = 50.0f;
		/// @brief �����܂ł̎���
		const float EXPLOSION_TIME = 5.0f;
		/// @brief �����G�t�F�N�g�̃t�@�C���p�X
		const char16_t* EXPLOSION_EFFECT_FILEPATH = u"Assets/effect/CosmicMist.efk";
		/// @brief �����G�t�F�N�g�̊g�嗦
		const Vector3 EXPLOSION_EFFECT_SCALE = { 15.0f,15.0f,15.0f };
		/// @brief ����SE�̃t�@�C���p�X
		const wchar_t* EXPLOSION_SE_FILEPATH = L"Assets/sound/se/explosion.wav";
		/// @brief ����SE�̑傫��
		const float EXPLOSION_SE_VOLUME = 0.1f;

		Bomb::~Bomb()
		{
			//���f���̏o���t���O�������Ă���ꍇ
			if (m_modelFlag == true) {
				//���f�����폜
				DeleteGO(m_itemModel);
			}
			//�G�t�F�N�g���폜
			DeleteGO(m_explosion);
		}

		void Bomb::InitData()
		{
			//�ϐ���������
			m_itemType = enItemBomb;
			m_endTime = DISAPPEARANCE_TIME;

			//�g�p������������ė���
			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);
			m_soundPlayer = FindGO<sound::SoundPlayer>(sound::SOUND_PLAYER_NAME);
			m_enemys = m_enemyGenerator->GetEnemys();
			m_bullets = m_player->GetBulletData();

			//�G�t�F�N�g���쐬
			m_explosion = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_explosion->Init(EXPLOSION_EFFECT_FILEPATH);
			m_explosion->SetScale(EXPLOSION_EFFECT_SCALE);

			//�T�E���h���쐬
			m_explosionSoundID = m_soundPlayer->SetSE(EXPLOSION_SE_FILEPATH);
		}

		void Bomb::Spawn()
		{
			//�A�C�e���̃��f�����쐬
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->InitDeferrd(ITEM_MODEL_FILEPATH);
		}

		void Bomb::Activation()
		{
			//�A�C�e���̌��ʂ̔����t���O�𗧂Ă�
			m_isActivate = true;

			//�v���C���[�̖ڂ̑O�ɍ��W��ݒ�
			Vector3 setPos = m_player->GetPlayerDirection() * SET_DISTANCE;
			setPos = m_player->GetPlayerPosition() + setPos;
			setPos.y += SET_HEIGHT;
			m_position = setPos;

			//���f�����쐬
			CreateModel();
		}

		void Bomb::Efficacy()
		{
			//���f�����o�����Ă���ꍇ�c
			if (m_modelFlag == true) {

				//�ړ����x�������ă��f���ɔ��f������
				m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
				m_itemModel->SetPosition(m_position);
				m_itemModel->Execution();

				//�v���C���[�̍U����G�l�~�[�Ƃ̓����蔻������
				PlayerMeleeAttackCollision();
				EnemyCollision();
				BulletCollision();

				//���ʔ������Ԃ��������Ԃ𒴂�����c
				if (m_activateTimer > EXPLOSION_TIME) {
					//��������
					Explosion();
				}
			}

			//�G�t�F�N�g���X�V
			m_explosion->SetPosition(m_position);
			m_explosion->Execution();
		}

		void Bomb::DeleteEfficacy()
		{
			
		}

		void Bomb::CreateModel()
		{
			//���f���𐶐�
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->InitDeferrd(BOMB_MODEL_FILEPATH);

			//���f�������t���O�𗧂Ă�
			m_modelFlag = true;
		}

		void Bomb::EnemyCollision()
		{
			//�G�l�~�[�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�l�~�[�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�l�~�[�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//�G�l�~�[�Ƃ̋������ڐG�����ȉ��Ȃ�c
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

			//�G�l�~�[�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�l�~�[�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�l�~�[�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//�G�l�~�[�Ƃ̋������������a�ȉ��Ȃ�c
				if (toEnemyVec.Length() < EXPLOSION_RADIUS) {

					//�G�l�~�[�ւƐL�т�x�N�g���𐳋K��
					toEnemyVec.Normalize();

					//�G�l�~�[�ɏՌ���������
					enemyData->SetMoveSpeed(toEnemyVec * EXPLOSION_IMPACT);

					//�G�l�~�[�ɔ����̃_���[�W��^����
					enemyData->ReceiveDamage(EXPLOSION_DAMAGE);
				}
			}

			//�G�t�F�N�g���Đ�
			m_explosion->Play(false);

			//�����̃T�E���h���Đ�
			m_soundPlayer->SetSEVolume(m_explosionSoundID, EXPLOSION_SE_VOLUME);
			m_soundPlayer->PlaySE(m_explosionSoundID);


			//���f�����폜
			DeleteGO(m_itemModel);
			
			//���f���̏o���t���O���~�낷
			m_modelFlag = false;
		}
	}
}