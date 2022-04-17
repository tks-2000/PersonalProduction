#pragma once

namespace mainGame {
	namespace enemy {
		

		/// @brief エネミーのエフェクト発生器
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();

			/// @brief 初期化
			/// @param enemy エネミークラスのアドレス
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
			
			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 出現エフェクト
			render::effect::EffectRender* m_spawnEffect = nullptr;
			/// @brief ダメージエフェクト
			render::effect::EffectRender* m_damageEffect = nullptr;
			/// @brief スタンエフェクト
			render::effect::EffectRender* m_stanEffect = nullptr;
			/// @brief 攻撃エフェクト
			render::effect::EffectRender* m_attackEffect = nullptr;
			/// @brief 死亡エフェクト
			render::effect::EffectRender* m_deathEffect = nullptr;
			/// @brief 敵のデータ
			Enemy* m_enemy = nullptr;
		};
	}
}
