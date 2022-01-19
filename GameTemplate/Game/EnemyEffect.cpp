#include "stdafx.h"
#include "EnemyEffect.h"

namespace mainGame {
	namespace enemy {
		/// @brief ダメージエフェクトのファイルパス
		const char16_t* DAMAGE_EFFECT_FILEPATH = u"Assets/effect/damage.efk";
		/// @brief ダメージエフェクトを表示する高さ
		const float DAMAGE_EFFECT_HEIGHT = 50.0f;
		/// @brief ダメージエフェクトの拡大率
		const Vector3 DAMAGE_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief スタンエフェクトのファイルパス
		const char16_t* STAN_EFFECT_FILEPATH = u"Assets/effect/knockout.efk";
		/// @brief スタンエフェクトの拡大率
		const Vector3 STAN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief スタンエフェクトを表示する高さ
		const float STAN_EFFECT_HEIGHT = 100.0f;
		/// @brief 攻撃エフェクトのファイルパス
		const char16_t* ATTACK_EFFECT_FILEPATH = u"Assets/effect/kick.efk";
		/// @brief 攻撃エフェクトの拡大率
		const Vector3 ATTACK_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief 攻撃エフェクトを表示する高さ
		const float ATTACK_EFFECT_HEIGHT = 50.0f;
		/// @brief 死亡エフェクトのファイルパス
		const char16_t* DEATH_EFFECT_FILEPATH = u"Assets/effect/enemy_explosion.efk";
		/// @brief 死亡エフェクトの拡大率
		const Vector3 DEATH_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief 死亡エフェクトを表示する高さ
		const float DEATH_EFFECT_HEIGHT = 100.0f;
		/// @brief 出現エフェクトのファイルパス
		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/shot_mine_burst.efk";
		/// @brief 出現エフェクトの拡大率
		const Vector3 SPAWN_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		/// @brief 出現エフェクトを表示する高さ
		const float SPAWN_EFFECT_HEIGHT = 100.0f;

		EffectGenerator::EffectGenerator()
		{

		}

		EffectGenerator::~EffectGenerator()
		{

		}

		void EffectGenerator::Init(Enemy* enemy)
		{
			//初期化が必要な情報を初期化する
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
			//エフェクトのデータを適用する
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
			//敵がダメージ中のとき…
			if (m_enemy->GetState() == enEnemyDamage) {
				//エフェクトの座標と回転を設定
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DAMAGE_EFFECT_HEIGHT;
				m_damageEffect.pos = efkPos;
				m_damageEffect.qRot = m_enemy->GetRotation();
				efkPos = m_enemy->GetPosition();
				efkPos.y += STAN_EFFECT_HEIGHT;
				m_stanEffect.pos = efkPos;

				//ダメージエフェクトが再生されていなければ…
				if (m_damageEffect.playFlag == false) {

					m_damageEffect.effect.Play(true);
					m_damageEffect.playFlag = true;
				}
				//ダメージエフェクトが再生されていれば…
				else {
					//スタンエフェクトが再生されていなければ…
					if (m_stanEffect.playFlag == false) {
						//スタンエフェクトを再生
						m_stanEffect.effect.Play(false);
						m_stanEffect.playFlag = true;
					}
				}
			}
			//ダメージ中でない場合…
			else {
				//エフェクトの再生を止める
				m_damageEffect.playFlag = false;
				m_stanEffect.playFlag = false;
				m_stanEffect.effect.Stop();
			}

			//エフェクトを更新
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