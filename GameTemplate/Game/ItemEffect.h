#pragma once

namespace mainGame {
	namespace item {
		/// @brief アイテムのエフェクト生成器
		class EffectGenerator
		{
		public:
			EffectGenerator();
			~EffectGenerator();
			/// @brief 初期化
			/// @param item アイテムのアドレス
			void Init(Item* item);
			/// @brief 実行
			void Execution();

		private:
			/// @brief 出現エフェクトの処理
			void PlaySpawnEffect();
			/// @brief 入手エフェクトの処理
			void PlayGetEffect();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 出現エフェクトの再生フラグ
			bool m_isSpawnEffectPlay = false;
			/// @brief 出現エフェクト
			render::effect::EffectRender* m_spawnEffect = nullptr;
			/// @brief 入手エフェクトの再生フラグ
			bool m_isGetEffectPlay = false;
			/// @brief 入手エフェクト
			render::effect::EffectRender* m_getEffect = nullptr;
			/// @brief 入手エフェクトの拡大率
			Vector3 m_getEffectScale = g_vec3Zero;
			/// @brief アイテム
			Item* m_item = nullptr;
		};
	}
}
