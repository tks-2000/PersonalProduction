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

		}

		EffectGenerator::~EffectGenerator()
		{

		}

		void EffectGenerator::Init(Enemy* enemy)
		{
			//���������K�v�ȏ�������������
			m_spawnEffect.effect.Init(SPAWN_EFFECT_FILEPATH);
			m_spawnEffect.scale = SPAWN_EFFECT_SCALE;
			m_damageEffect.effect.Init(DAMAGE_EFFECT_FILEPATH);
			m_damageEffect.scale = DAMAGE_EFFECT_SCALE;
			m_stanEffect.effect.Init(STAN_EFFECT_FILEPATH);
			m_stanEffect.scale = STAN_EFFECT_SCALE;
			m_attackEffect.effect.Init(ATTACK_EFFECT_FILEPATH);
			m_attackEffect.scale = ATTACK_EFFECT_SCALE;
			m_deathEffect.effect.Init(DEATH_EFFECT_FILEPATH);
			m_deathEffect.scale = DEATH_EFFECT_SCALE;
			m_enemy = enemy;

			m_spawnEffect.effect.Play(true);

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

		void EffectGenerator::UpdateEffect(EffectData& effectData)
		{
			//�G�t�F�N�g�̃f�[�^��K�p����
			effectData.effect.SetPosition(effectData.pos);
			effectData.effect.SetRotation(effectData.qRot);
			effectData.effect.SetScale(effectData.scale);
			effectData.effect.Update();
		}

		void EffectGenerator::SpawnEffectExecution()
		{
			if (m_spawnEffect.effect.IsPlay() == false) {
				return;
			}

			Vector3 efkPos = m_enemy->GetPosition();
			efkPos.y += SPAWN_EFFECT_HEIGHT;
			m_spawnEffect.pos = efkPos;
			m_spawnEffect.qRot = m_enemy->GetRotation();

			UpdateEffect(m_spawnEffect);
		}

		void EffectGenerator::DamageEffectExecution()
		{
			//�G���_���[�W���̂Ƃ��c
			if (m_enemy->GetState() == enEnemyDamage) {
				//�G�t�F�N�g�̍��W�Ɖ�]��ݒ�
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DAMAGE_EFFECT_HEIGHT;
				m_damageEffect.pos = efkPos;
				m_damageEffect.qRot = m_enemy->GetRotation();
				efkPos = m_enemy->GetPosition();
				efkPos.y += STAN_EFFECT_HEIGHT;
				m_stanEffect.pos = efkPos;

				//�_���[�W�G�t�F�N�g���Đ�����Ă��Ȃ���΁c
				if (m_damageEffect.playFlag == false) {

					m_damageEffect.effect.Play(true);
					m_damageEffect.playFlag = true;
				}
				//�_���[�W�G�t�F�N�g���Đ�����Ă���΁c
				else {
					//�X�^���G�t�F�N�g���Đ�����Ă��Ȃ���΁c
					if (m_stanEffect.playFlag == false) {
						//�X�^���G�t�F�N�g���Đ�
						m_stanEffect.effect.Play(false);
						m_stanEffect.playFlag = true;
					}
				}
			}
			//�_���[�W���łȂ��ꍇ�c
			else {
				//�G�t�F�N�g�̍Đ����~�߂�
				m_damageEffect.playFlag = false;
				m_stanEffect.playFlag = false;
				m_stanEffect.effect.Stop();
			}

			//�G�t�F�N�g���X�V
			UpdateEffect(m_damageEffect);
			UpdateEffect(m_stanEffect);
		}

		void EffectGenerator::AttackEffectExecution()
		{
			if (m_enemy->IsHitAttack() == true) {
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += ATTACK_EFFECT_HEIGHT;
				m_attackEffect.pos = efkPos;
				m_attackEffect.qRot = m_enemy->GetRotation();

				if (m_attackEffect.effect.IsPlay() == false) {
					m_attackEffect.effect.Play(true);
				}
			}

			UpdateEffect(m_attackEffect);
		}

		void EffectGenerator::DeathEffectExecution()
		{
			if (m_enemy->GetDeleteTimer() > m_enemy->GetDeleteTime() / 1.5f) {
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DEATH_EFFECT_HEIGHT;
				m_deathEffect.pos = efkPos;
				m_deathEffect.qRot = m_enemy->GetRotation();

				if (m_deathEffect.effect.IsPlay() == false) {
					m_deathEffect.effect.Play(true);
				}
			}

			UpdateEffect(m_deathEffect);
		}
	}
}