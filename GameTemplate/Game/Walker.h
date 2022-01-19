#pragma once
#include "EnemyRouteMove.h"

namespace mainGame {
	namespace enemy {
		class Walker : public Enemy
		{
		public:
			void SetMoveSpeed(const Vector3& speed) { m_enemyRouteMove.SetMoveSpeed(speed); };

			const Vector3& GetMoveSpeed() const { return m_enemyRouteMove.GetMoveSpeed(); }

			const bool IsHitAttack() { return m_enemyAttack.IsHit(); }
		private:
			void InitData(const EnemyInitData& initData);

			void ExecuteBehavior();

			Attack m_enemyAttack;

			RouteMove m_enemyRouteMove;

			Animation m_enemyAnimation;
		};
	}
}
