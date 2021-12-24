#pragma once
#include "Enemy.h"
#include "EnemyAttackThePlayer.h"

namespace mainGame {

	namespace player {
		class Player;
	}

	namespace enemy {
		class Chaser : public Enemy
		{
		public:
			void SetMoveSpeed(const Vector3& speed) { m_enemyRouteMove.SetMoveSpeed(speed); };

			const Vector3& GetMoveSpeed() const { return m_enemyRouteMove.GetMoveSpeed(); }
		private:
			void InitData(const EnemyInitData& initData);

			void ExecuteBehavior();

			void PlayerSearch();

			bool m_seeTheSituationFlag = false;

			bool m_chaseMode = false;

			float m_chaseTimer = 0.0f;

			AttackThePlayer m_enemyAttackThePlayer;

			Attack m_enemyAttack;

			RouteMove m_enemyRouteMove;

			Animation m_enemyAnimation;

			player::Player* m_player = nullptr;

			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
		};
	}
}
