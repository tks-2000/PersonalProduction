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
		const char16_t* DEATH_EFFECT_FILEPATH = u"Assets/effect/Simple_Sprite_BillBoard.efk";
		/// @brief 死亡エフェクトの拡大率
		const Vector3 DEATH_EFFECT_SCALE = { 20.0f,20.0f,20.0f };
		/// @brief 死亡エフェクトを表示する高さ
		const float DEATH_EFFECT_HEIGHT = 50.0f;
		/// @brief 死亡エフェクトを表示する時間の割合
		const float DEATH_EFFECT_PLAY_TAME_RATE = 0.99;
		/// @brief 出現エフェクトのファイルパス
		const char16_t* SPAWN_EFFECT_FILEPATH = u"Assets/effect/enemy_explosion.efk";
		/// @brief 出現エフェクトの拡大率
		const Vector3 SPAWN_EFFECT_SCALE = { 20.0f,20.0f,20.0f };
		/// @brief 出現エフェクトを表示する高さ
		const float SPAWN_EFFECT_HEIGHT = 100.0f;

		EffectGenerator::EffectGenerator()
		{
			//エフェクトを作成
			m_spawnEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_damageEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_stanEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_attackEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
			m_deathEffect = NewGO<render::effect::EffectRender>(PRIORITY_VERYLOW);
		}

		EffectGenerator::~EffectGenerator()
		{
			//エフェクトを削除
			DeleteGO(m_spawnEffect);
			DeleteGO(m_damageEffect);
			m_stanEffect->Stop(true);
			DeleteGO(m_stanEffect);
			DeleteGO(m_attackEffect);
			DeleteGO(m_deathEffect);
		}

		void EffectGenerator::Init(Enemy* enemy)
		{
			//初期化が必要な情報を初期化する
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

			//初期化完了
			m_isInitd = true;
		}

		void EffectGenerator::Execution()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			//全てのエフェクトの処理を実行
			SpawnEffectExecution();
			DamageEffectExecution();
			AttackEffectExecution();
			DeathEffectExecution();
		}

		

		void EffectGenerator::SpawnEffectExecution()
		{
			//エネミーの位置にエフェクトを発生させる
			Vector3 efkPos = m_enemy->GetPosition();
			efkPos.y += SPAWN_EFFECT_HEIGHT;
			m_spawnEffect->SetPosition(efkPos);
			m_spawnEffect->SetRotation(m_enemy->GetRotation());
			m_spawnEffect->Execution();
		}

		void EffectGenerator::DamageEffectExecution()
		{
			//エフェクトの座標と回転を設定
			Vector3 efkPos = m_enemy->GetPosition();
			efkPos.y += STAN_EFFECT_HEIGHT;
			m_stanEffect->SetPosition(efkPos);

			//エネミーがダメージを受けたとき…
			if (m_enemy->IsDamage() == true) {
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DAMAGE_EFFECT_HEIGHT;
				m_damageEffect->SetPosition(efkPos);
				m_damageEffect->SetRotation(m_enemy->GetRotation());
				//エフェクトを再生
				m_damageEffect->Play(false,true);
				m_stanEffect->Play(false);
			}

			//ダメージ中でない場合…
			if(m_enemy->GetState() != enEnemyDamage) {
				//エフェクトの再生を止める
				m_stanEffect->Stop(true);
			}

			//エフェクトの処理を実行
			m_damageEffect->Execution();
			m_stanEffect->Execution();
		}

		void EffectGenerator::AttackEffectExecution()
		{
			//攻撃が命中したら…
			if (m_enemy->IsHitAttack() == true) {
				//ヒットエフェクトを再生
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += ATTACK_EFFECT_HEIGHT;
				m_attackEffect->SetPosition(efkPos);
				m_attackEffect->SetRotation(m_enemy->GetRotation());
				m_attackEffect->Play(false);
			}
			//攻撃が命中していない場合
			else {
				//エフェクトを止める
				m_attackEffect->Stop(false);
			}

			//エフェクトを実行
			m_attackEffect->Execution();
		}

		void EffectGenerator::DeathEffectExecution()
		{
			//エネミーの削除タイマーが死亡エフェクトの再生時間を超えた場合…
			if (m_enemy->GetDeleteTimer() > m_enemy->GetDeleteTime() * DEATH_EFFECT_PLAY_TAME_RATE) {
				//死亡エフェクトを再生
				Vector3 efkPos = m_enemy->GetPosition();
				efkPos.y += DEATH_EFFECT_HEIGHT;
				m_deathEffect->SetPosition(efkPos);
				m_deathEffect->SetRotation(m_enemy->GetRotation());
				m_deathEffect->Play(false);
			}

			//エフェクトの処理を実行
			m_deathEffect->Execution();
		}
	}
}