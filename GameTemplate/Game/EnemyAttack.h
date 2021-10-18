#pragma once
#include "Enemy.h"


namespace mainGame {

	namespace defensiveTarget{

		class DefensiveTarget;
	}

	namespace enemy {

		class Enemy;

		/// @brief 敵の攻撃を制御するクラス
		class Attack
		{
		public:
			Attack();
			~Attack();

			/// @brief 初期化
			/// @param enemy 処理を適用する敵のアドレス
			void Init(Enemy* enemy);

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

			/// @brief 敵クラス
			Enemy* m_enemy = nullptr;
			/// @brief 防衛対象のクラス
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
