#pragma once

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace enemy {

		class Enemy;

		class AttackThePlayer
		{
		public:
			AttackThePlayer();
			~AttackThePlayer();
			void Init(Enemy* enemy);
			void Execution();

			void SetAttackTarget(const Vector3& target) { m_attackTarget = target; }

			const bool IsHit() { return m_isHit; }

		private:

			void DamageThePlayer();

			bool m_isInitd = false;

			Vector3 m_attackTarget = g_vec3Zero;

			float m_attackTimer = 0.0f;

			bool m_isHit = false;

			Enemy* m_enemy = nullptr;

			player::Player* m_player = nullptr;

		};
	}
}
