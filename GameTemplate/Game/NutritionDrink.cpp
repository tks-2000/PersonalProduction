#include "stdafx.h"
#include "NutritionDrink.h"

namespace mainGame {

	namespace item {
		/// @brief �A�C�e�����f���̃t�@�C���p�X
		const char* DRINK_MODEL_FILEPATH = "Assets/modelData/item/item_speedup.tkm";
		/// @brief ���ʏI���܂ł̎���
		const float DISAPPEARANCE_TIME = 10.0f;
		/// @brief �G�l�~�[�ƐڐG���鋗��
		const float ENEMY_COLLISION_DISTANCE = 150.0f;
		/// @brief �̓�����̏Ռ���
		const float BODY_BLOW_IMPACT = 5000.0f;
		/// @brief �̓�����̃_���[�W
		const int BODY_BLOW_DAMAGE = 100;
		/// @brief ���Z���鑬�x
		const float ADD_MOVE_VEROCITY = 10.0f;
		/// @brief �p���[�A�b�v�G�t�F�N�g�̃t�@�C���p�X
		const char16_t* POWERUP_EFFECT_FILEPATH = u"Assets/effect/itembuff_attackup.efk";
		/// @brief �p���[�A�b�v�G�t�F�N�g�̊g�嗦
		const Vector3 POWERUP_EFFECT_SCALE = { 10.0f,10.0f,10.0f };

		NutritionDrink::~NutritionDrink()
		{
			//�G�t�F�N�g���~���폜
			m_powerUpEffect->Stop(true);
			DeleteGO(m_powerUpEffect);
		}

		void NutritionDrink::Activation()
		{
			//�G�t�F�N�g���Đ�
			m_powerUpEffect->Play(true);
			//���ʔ����t���O�𗧂Ă�
			m_isActivate = true;
		}

		void NutritionDrink::InitData()
		{
			//�ϐ���������
			m_itemType = enItemNutritionDrink;
			m_endTime = DISAPPEARANCE_TIME;

			//�g�p�������������
			m_enemyGenerator = FindGO<enemy::Generator>(enemy::ENEMY_GENERATOR_NAME);
			m_enemys = m_enemyGenerator->GetEnemys();

			//�G�t�F�N�g���쐬
			m_powerUpEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_powerUpEffect->Init(POWERUP_EFFECT_FILEPATH);
			m_powerUpEffect->SetScale(POWERUP_EFFECT_SCALE);
		}

		void NutritionDrink::Spawn()
		{
			//
			m_itemModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_itemModel->InitDeferrd(DRINK_MODEL_FILEPATH);
		}

		void NutritionDrink::Efficacy()
		{
			//���W���v���C���[�̍��W�ɐݒ肷��
			m_position = m_player->GetPlayerPosition();

			//�G�t�F�N�g�̏��������s
			m_powerUpEffect->SetPosition(m_position);
			m_powerUpEffect->Execution();

			//�v���C���[�̑��x�����Z
			m_player->SetAddVerocity(ADD_MOVE_VEROCITY);

			//�G�l�~�[�Ɠ����蔻������
			EnemyCollision();
		}

		void NutritionDrink::EnemyCollision()
		{
			//�G�l�~�[�̐��������s
			for (int enemyNum = 0; enemyNum < m_enemys->size(); enemyNum++) {
				//�G�l�~�[�̃f�[�^�����o��
				enemy::Enemy* enemyData = *(m_enemys->begin() + enemyNum);

				//�G�l�~�[�Ƃ̋����𑪂�
				Vector3 toEnemyVec = enemyData->GetPosition() - m_position;

				//�G�l�~�[�Ƃ̋������ڐG�����ȉ��Ȃ�c
				if (toEnemyVec.Length() < ENEMY_COLLISION_DISTANCE && enemyData->GetState() != enemy::enEnemyDown) {

					//�G�l�~�[�ւƐL�т�x�N�g���𐳋K��
					toEnemyVec.Normalize();

					//�G�l�~�[�ɏՌ���������
					enemyData->SetMoveSpeed(toEnemyVec * BODY_BLOW_IMPACT);

					//�G�l�~�[�ɐڐG�̃_���[�W��^����
					enemyData->ReceiveDamage(BODY_BLOW_DAMAGE);
				}
			}
		}

		void NutritionDrink::DeleteEfficacy()
		{
			//�v���C���[�ɉ��Z���鑬�x��0�ɂ���
			m_player->SetAddVerocity(0.0f);
		}
	}
}