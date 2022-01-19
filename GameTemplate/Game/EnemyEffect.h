#pragma once

namespace mainGame {
	namespace enemy {
		/// @brief エフェクトの情報をまとめた構造体
		struct EffectData
		{
			/// @brief エフェクト
			Effect effect;
			/// @brief 座標
			Vector3 pos = g_vec3Zero;
			/// @brief 回転
			Quaternion qRot = Quaternion::Identity;
			/// @brief 拡大率
			Vector3 scale = g_vec3One;
			/// @brief 任意で操作する再生フラグ
			bool playFlag = false;

		};

		/// @brief エフェクト発生器
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();

			/// @brief 初期化
			/// @param enemy 敵クラスのアドレス
			void Init(Enemy* enemy);

			/// @brief 実行
			void Execution();
		private:

			/// @brief 出現エフェクト処理の実行
			void SpawnEffectExecution();

			/// @brief ダメージエフェクト処理の実行
			void DamageEffectExecution();

			/// @brief 攻撃エフェクト処理の実行
			void AttackEffectExecution();

			/// @brief 死亡エフェクト処理の実行
			void DeathEffectExecution();

			/// @brief エフェクト情報を更新
			/// @param effectData 更新エフェクト情報
			void UpdateEffect(EffectData& effectData);
			
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 出現エフェクト
			EffectData m_spawnEffect;
			/// @brief ダメージエフェクト
			EffectData m_damageEffect;
			/// @brief スタンエフェクト
			EffectData m_stanEffect;
			/// @brief 攻撃エフェクト
			EffectData m_attackEffect;
			/// @brief 死亡エフェクト
			EffectData m_deathEffect;
			/// @brief 敵のデータ
			Enemy* m_enemy = nullptr;
		};
	}
}
