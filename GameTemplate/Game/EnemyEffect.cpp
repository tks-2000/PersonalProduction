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
		const char16_t* DEATH_EFFECT_FILEPATH = u"Assets/effect/enemy_explosion.efk";
		/// @brief ���S�G�t�F�N�g�̊g�嗦
		const Vector3 DEATH_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief ���S�G�t�F�N�g��\�����鍂��
		const float DEATH_EFFECT_HEIGHT = 100.0f;
		/// @brief �o���G�t�F�N�g�̃t�@�C���p�X
		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/shot_mine_burst.efk";
		/// @brief �o���G�t�F�N�g�̊g�嗦
		const Vector3 SPAWN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief �o���G�t�F�N�g��\�����鍂��
		const float SPAWN_EFFECT_HEIGHT = 100.0f;

		EffectGenerator::EffectGenerator()
		{
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_damageEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_stanEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_attackEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_deathEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
		}

		EffectGenerator::~EffectGenerator()
		{
			DeleteGO(m_spawnEffect);
			DeleteGO(m_damageEffect);
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

			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			SpawnEffectExecution();
			DamageEffectExecution();
			AttackEffectExecution();
			DeathEffectExecution();

		}

		

		void EffectGenerator::SpawnEffectExecution()
		{
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
			efkPos.y += DAMAGE_EFFECT_HEIGHT;
			m_damageEffect->SetPosition(efkPos);
			m_damageEffect->SetRotation(m_enemy->GetRotation());
			efkPos = m_enemy->GetPosition();
			efkPos.y += STAN_EFFECT_HEIGHT;
			m_stanEffect->SetPosition(efkPos);

			//�G���_���[�W���󂯂��Ƃ��c
			if (m_enemy->IsDamage() == true) {
				//�G�t�F�N�g���Đ�
				m_damageEffect->Play(false,true);
				m_stanEffect->Play(false);
			}

			//�_���[�W���łȂ��ꍇ�c
			if(m_enemy->GetState() != enEnemyDamage) {
				//�G�t�F�N�g�̍Đ����~�߂�
				//m_damageEffect->Stop(false);
				m_stanEffect->Stop(true);
			}

			//�G�t�F�N�g���X�V
			m_damageEffect->Execution();
			m_stanEffect->Execution();
		}

		void EffectGenerator::AttackEffectExecution()
		{
			if (m_enemy->IsHitAttack() == true) {
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += ATTACK_EFFECT_HEIGHT;
				m_attackEffect->SetPosition(efkPos);
				m_attackEffect->SetRotation(m_enemy->GetRotation());

				m_attackEffect->Play(false);
			}
			else {
				m_attackEffect->Stop(false);
			}

			m_attackEffect->Execution();
		}

		void EffectGenerator::DeathEffectExecution()
		{
			if (m_enemy->GetDeleteTimer() > m_enemy->GetDeleteTime() / 1.5f) {
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DEATH_EFFECT_HEIGHT;
				m_deathEffect->SetPosition(efkPos);
				m_deathEffect->SetRotation(m_enemy->GetRotation());

				m_deathEffect->Play(false);
			}

			m_deathEffect->Execution();
		}
	}
}