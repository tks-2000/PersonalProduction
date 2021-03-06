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

			Chaser();
			~Chaser();

			void SetMoveSpeed(const Vector3& speed) { m_enemyRouteMove.SetMoveSpeed(speed); };

			const Vector3& GetMoveSpeed() const { return m_enemyRouteMove.GetMoveSpeed(); }

			const bool IsAttack();

			const bool IsHitAttack();
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

			sound::SoundPlayer* m_soundPlayer = nullptr;

			int m_discoverSoundID = 0;
		};
	}
}
