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

			/// @brief 攻撃を行っているか？
			/// @return 行っていれば true 行っていなければ false
			const bool IsAttack() { return m_isAttack; }

			/// @brief 攻撃がヒットしているか？
			/// @return ヒットしていればtrue そうでなければ false
			const bool IsHit() { return m_isHit; }

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
			/// @brief 攻撃を行ったかの判定
			bool m_isAttack = false;
			/// @brief 攻撃が当たっているかの判定
			bool m_isHit = false;

			/// @brief 敵クラス
			Enemy* m_enemy = nullptr;
			/// @brief 防衛対象のクラス
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
