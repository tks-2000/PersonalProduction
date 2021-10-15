#pragma once
#include "Enemy.h"


namespace mainGame {

	namespace defensiveTarget{

		class DefensiveTarget;
	}

	namespace enemy {

		/// @brief 敵の攻撃を制御するクラス
		class Attack
		{
		public:
			Attack();
			~Attack();
			/// @brief 初期化
			void Init(const EnEnemyType& type);
			/// @brief 実行
			void Execution();
		private:
			/// @brief 攻撃を実行
			void ExecuteAttack();

			/// @brief 初期化フラグ
			bool m_isInitd = false;
			/// @brief 攻撃力
			int m_attackPower = 0;
			/// @brief 攻撃するまでのタイマー
			float m_attackTimer = 0.0f;

			/// @brief 防衛対象のクラス
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
