#include "stdafx.h"
#include "EnemyEffect.h"

namespace mainGame {
	namespace enemy {
		/// @brief �_���[�W�G�t�F�N�g�̃t�@�C���p�X
		const char16_t* DAMAGE_EFFECT_FILEPATH = u"Assets/effect/damage.efk";
		/// @brief �_���[�W�G�t�F�N�g��\�����鍂��
		const float DAMAGE_EFFECT_HEIGHT = 50.0f;
		/// @brief �_���[�W�G�t�F�N�g�̊g�嗦
		const Vector3 DAMAGE_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief �X�^���G�t�F�N�g�̃t�@�C���p�X
		const char16_t* STAN_EFFECT_FILEPATH = u"Assets/effect/knockout.efk";
		/// @brief �X�^���G�t�F�N�g�̊g�嗦
		const Vector3 STAN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief �X�^���G�t�F�N�g��\�����鍂��
		const float STAN_EFFECT_HEIGHT = 100.0f;
		/// @brief �U���G�t�F�N�g�̃t�@�C���p�X
		const char16_t* ATTACK_EFFECT_FILEPATH = u"Assets/effect/kick.efk";
		/// @brief �U���G�t�F�N�g�̊g�嗦
		const Vector3 ATTACK_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief �U���G�t�F�N�g��\�����鍂��
		const float ATTACK_EFFECT_HEIGHT = 50.0f;
		/// @brief ���S�G�t�F�N�g�̃t�@�C���p�X
		const char16_t* DEATH_EFFECT_FILEPATH = u"Assets/effect/Simple_Sprite_BillBoard.efk";
		/// @brief ���S�G�t�F�N�g�̊g�嗦
		const Vector3 DEATH_EFFECT_SCALE = { 20.0f,20.0f,20.0f };
		/// @brief ���S�G�t�F�N�g��\�����鍂��
		const float DEATH_EFFECT_HEIGHT = 50.0f;
		/// @brief ���S�G�t�F�N�g��\�����鎞�Ԃ̊���
		const float DEATH_EFFECT_PLAY_TAME_RATE = 0.99;
		/// @brief �o���G�t�F�N�g�̃t�@�C���p�X
		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/enemy_explosion.efk";
		/// @brief �o���G�t�F�N�g�̊g�嗦
		const Vector3 SPAWN_EFFECT_SCALE = { 20.0f,20.0f,20.0f };
		/// @brief �o���G�t�F�N�g��\�����鍂��
		const float SPAWN_EFFECT_HEIGHT = 100.0f;

		EffectGenerator::EffectGenerator()
		{
			//�G�t�F�N�g���쐬
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_damageEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_stanEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_attackEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_deathEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
		}

		EffectGenerator::~EffectGenerator()
		{
			//�G�t�F�N�g���폜
			DeleteGO(m_spawnEffect);
			DeleteGO(m_damageEffect);
			m_stanEffect->Stop(true);
			DeleteGO(m_stanEffect);
			DeleteGO(m_attackEffect);
			DeleteGO(m_deathEffect);
		}

		void EffectGenerator::Init(Enemy* enemy)
		{
			//���������K�v�ȏ�������������
			m_spawnEffect->Init(SPAWN_EFFECT_FILEPATH);
			m_spawnEffect->SetScale(SPAWN_EFFECT_SCALE);
			m_damageEffect->Init(DAMAGE_EFFECT_FILEPATH);
			m_damageEffect->SetScale(DAMAGE_EFFECT_SCALE);
			m_stanEffect->Init(STAN_EFFECT_FILEPATH);
			m_stanEffect->SetScale(STAN_EFFECT_SCALE);
			m_attackEffect->Init(ATTACK_EFFECT_FILEPATH);
			m_attackEffect->SetScale(ATTACK_EFFECT_SCALE);
			m_deathEffect->Init(DEATH_EFFECT_FILEPATH);
			m_deathEffect->SetScale(DEATH_EFFECT_SCALE);
			m_enemy = enemy;

			m_spawnEffect->Play(false);

			//����������
			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			//�S�ẴG�t�F�N�g�̏��������s
			SpawnEffectExecution();
			DamageEffectExecution();
			AttackEffectExecution();
			DeathEffectExecution();
		}

		

		void EffectGenerator::SpawnEffectExecution()
		{
			//�G�l�~�[�̈ʒu�ɃG�t�F�N�g�𔭐�������
			Vector3 efkPos = m_enemy->GetPosition();
			efkPos.y += SPAWN_EFFECT_HEIGHT;
			m_spawnEffect->SetPosition(efkPos);
			m_spawnEffect->SetRotation(m_enemy->GetRotation());
			m_spawnEffect->Execution();
		}

		void EffectGenerator::DamageEffectExecution()
		{
			//�G�t�F�N�g�̍��W�Ɖ�]��ݒ�
			Vector3 efkPos = m_enemy->GetPosition();
			efkPos.y += STAN_EFFECT_HEIGHT;
			m_stanEffect->SetPosition(efkPos);

			//�G�l�~�[���_���[�W���󂯂��Ƃ��c
			if (m_enemy->IsDamage() == true) {
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DAMAGE_EFFECT_HEIGHT;
				m_damageEffect->SetPosition(efkPos);
				m_damageEffect->SetRotation(m_enemy->GetRotation());
				//�G�t�F�N�g���Đ�
				m_damageEffect->Play(false,true);
				m_stanEffect->Play(false);
			}

			//�_���[�W���łȂ��ꍇ�c
			if(m_enemy->GetState() != enEnemyDamage) {
				//�G�t�F�N�g�̍Đ����~�߂�
				m_stanEffect->Stop(true);
			}

			//�G�t�F�N�g�̏��������s
			m_damageEffect->Execution();
			m_stanEffect->Execution();
		}

		void EffectGenerator::AttackEffectExecution()
		{
			//�U��������������c
			if (m_enemy->IsHitAttack() == true) {
				//�q�b�g�G�t�F�N�g���Đ�
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += ATTACK_EFFECT_HEIGHT;
				m_attackEffect->SetPosition(efkPos);
				m_attackEffect->SetRotation(m_enemy->GetRotation());
				m_attackEffect->Play(false);
			}
			//�U�����������Ă��Ȃ��ꍇ
			else {
				//�G�t�F�N�g���~�߂�
				m_attackEffect->Stop(false);
			}

			//�G�t�F�N�g�����s
			m_attackEffect->Execution();
		}

		void EffectGenerator::DeathEffectExecution()
		{
			//�G�l�~�[�̍폜�^�C�}�[�����S�G�t�F�N�g�̍Đ����Ԃ𒴂����ꍇ�c
			if (m_enemy->GetDeleteTimer() > m_enemy->GetDeleteTime() * DEATH_EFFECT_PLAY_TAME_RATE) {
				//���S�G�t�F�N�g���Đ�
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DEATH_EFFECT_HEIGHT;
				m_deathEffect->SetPosition(efkPos);
				m_deathEffect->SetRotation(m_enemy->GetRotation());
				m_deathEffect->Play(false);
			}

			//�G�t�F�N�g�̏��������s
			m_deathEffect->Execution();
		}
	}
}