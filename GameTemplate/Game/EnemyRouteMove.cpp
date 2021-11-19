#include "stdafx.h"
#include "EnemyRouteMove.h"

namespace mainGame {
	namespace enemy {

		const float ENEMY_MOVE_START_TIME = 3.0f;
		/// @brief “G‚ÌÕ“Ë”»’è‚Ì”¼Œa
		const float ENEMY_COLLISION_RADIUS = 30.0f;
		/// @brief “G‚ÌÕ“Ë”»’è‚Ì‚‚³
		const float ENEMY_COLLISION_HEIGHT = 50.0f;


		RouteMove::RouteMove()
		{

		}

		RouteMove::~RouteMove()
		{

		}

		void RouteMove::Init(Enemy* enemy)
		{
			if (m_isInitd == true) {
				return;
			}
			m_enemy = enemy;

			m_naviMesh.Init("Assets/nvmData/stage3_2.tkn");

			m_charaCon.Init(ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_HEIGHT, m_enemy->GetPosition());

			m_defensiveTarget = FindGO<defensiveTarget::DefensiveTarget>(defensiveTarget::DEFENSIVE_TARGET_NAME);

			m_moveTarget = m_defensiveTarget->GetPosition();

			m_moveVerocity = 200.0f;

			m_isInitd = true;
		}

		void RouteMove::RouteSearch()
		{
			if (m_isInitd == false) {
				return;
			}
			m_pathFinding.Execute(
				m_path,
				m_naviMesh,
				m_enemy->GetPosition(),
				m_moveTarget,
				ENEMY_COLLISION_RADIUS,
				ENEMY_COLLISION_HEIGHT
			);

			m_enemy->SetState(enEnemyMove);
		}

		const Vector3& RouteMove::IdleExecution(Vector3& pos)
		{
			if (m_isInitd == false) {
				return pos;
			}

			m_moveStartTimer += g_gameTime->GetFrameDeltaTime();

			if (m_moveStartTimer > ENEMY_MOVE_START_TIME) {
				RouteSearch();
				m_moveStartTimer = 0.0f;
				return pos;
			}

			m_moveSpeed -= m_moveSpeed * 0.1f;

			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			return pos;
		}

		const Vector3& RouteMove::MoveExecution(Vector3& pos)
		{
			if (m_isInitd == false) {
				return pos;
			}

			m_toTarget = m_moveTarget - pos;

			m_targetDistance = m_toTarget.Length();

			if (m_targetDistance < 200.0f) {
				m_enemy->SetState(enEnemyAttack);
				return pos;
			}

			//RouteSearch(m_moveTarget);

			bool isEnd = false;

			Vector3 movePos = m_path.Move(
				pos,
				m_moveVerocity * g_gameTime->GetFrameDeltaTime(),
				isEnd
			);
			
			
			Vector3 oldPos = pos;

			Vector3 moveSpeed = movePos - pos;

			moveSpeed.Normalize();

			m_moveSpeed += moveSpeed * m_moveVerocity;

			
			m_moveSpeed -= m_moveSpeed * 0.5f;
			
			
			
			pos = m_charaCon.Execute(m_moveSpeed,g_gameTime->GetFrameDeltaTime());

			Vector3 toMovePos = pos - oldPos;

			if (toMovePos.Length() < 1.0f) {
				RouteSearch();
				return pos;
			}

			

			return pos;
		}

		const Vector3& RouteMove::StopExecution(Vector3& pos)
		{
			if (m_isInitd == false) {
				return pos;
			}

			m_moveSpeed -= m_moveSpeed * 0.1f;

			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			return pos;
		}
	}
}