#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace enemy {

		class Enemy;

		/// @brief プレイヤーへの攻撃を制御するクラス
		class AttackThePlayer
		{
		public:
			AttackThePlayer();
			~AttackThePlayer();
			/// @brief 初期化
			/// @param enemy エネミーのアドレス
			void Init(Enemy* enemy);
			/// @brief 実行
			void Execution();
			/// @brief 攻撃目標を設定
			/// @param target 攻撃目標の座標
			void SetAttackTarget(const Vector3& target) { m_attackTarget = target; }
			/// @brief 攻撃を行ったか？
			/// @return trueで行った falseで行っていない
			const bool IsAttack() { return m_isAttack; }

			/// @brief 攻撃が当たったか？
			/// @return trueで当たった falseで当たっていない
			const bool IsHit() { return m_isHit; }

		private:
			/// @brief プレイヤーにダメージを与える
			void DamageThePlayer();
			/// @brief 初期化フラグ
			bool m_isInitd = false;

			Vector3 m_attackTarget = g_vec3Zero;

			float m_attackTimer = 0.0f;

			bool m_isAttack = false;

			bool m_isHit = false;

			Enemy* m_enemy = nullptr;

			player::Player* m_player = nullptr;

		};
	}
}
