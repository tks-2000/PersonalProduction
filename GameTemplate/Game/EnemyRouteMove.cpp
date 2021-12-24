#include "stdafx.h"
#include "EnemyRouteMove.h"

namespace mainGame {
	namespace enemy {

		const float ENEMY_MOVE_START_TIME = 3.0f;
		/// @brief �G�̏Փ˔���̔��a
		const float ENEMY_COLLISION_RADIUS = 30.0f;
		/// @brief �G�̏Փ˔���̍���
		const float ENEMY_COLLISION_HEIGHT = 50.0f;
		/// @brief ���C��
		const float NORMAL_FRICTION = 0.1f;
		/// @brief ���x
		const float NORMAL_VEROCITY = 25.0f;

		const float GRAVITY = 100.0f;

		const float MOVE_STOP_DISTANCE = 200.0f;

		const float MOVE_STOP_ANGLE_MATCH_RATE = 0.0f;

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

			m_moveVerocity = NORMAL_VEROCITY;

			m_friction = NORMAL_FRICTION;

			m_moveStopDistance = MOVE_STOP_DISTANCE;

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
		}

		void RouteMove::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			switch (m_enemy->GetState())
			{
			case enEnemyIdle: {
				IdleExecution();
			}break;
			case enEnemyMove: {
				MoveExecution(m_moveVerocity);
			}break;
			case enEnemyAttack: {
				StopExecution();
			}break;
			case enEnemyDamage: {
				IdleExecution();
			}break;
			case enEnemySeeTheSituation: {
				StopExecution();
			}break;
			case enEnemyDown: {
				StopExecution();
			}break;
			default:
				break;
			}

			//m_moveVerocity += 0.01f;
		}

		void RouteMove::IdleExecution()
		{
			

			m_moveStartTimer += g_gameTime->GetFrameDeltaTime();

			if (m_moveStartTimer > ENEMY_MOVE_START_TIME) {
				RouteSearch();
				m_moveStartTimer = 0.0f;
				m_enemy->SetState(enEnemyMove);
				return;
			}

			m_moveSpeed -= m_moveSpeed * m_friction;

			ApplyGravity();

			m_enemy->SetPosition(m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime()));
		}

		void RouteMove::MoveExecution(const float moveVerocity)
		{
			Vector3 pos = m_enemy->GetPosition();

			m_toTarget = m_moveTarget - pos;

			m_targetDistance = m_toTarget.Length();

			if (m_targetDistance < m_moveStopDistance) {

				Vector3 targetDirection = m_toTarget;

				targetDirection.Normalize();

				float rate = Dot(targetDirection, m_enemy->GetDirection());

				if (rate >= MOVE_STOP_ANGLE_MATCH_RATE) {
					m_enemy->SetState(enEnemyAttack);
					return;
				}
			}

			bool isEnd = false;

			Vector3 movePos = m_path.Move(
				pos,
				moveVerocity * g_gameTime->GetFrameDeltaTime(),
				isEnd
			);
			
			
			Vector3 oldPos = pos;

			Vector3 moveSpeed = movePos - pos;

			moveSpeed.Normalize();

			m_moveSpeed += moveSpeed * moveVerocity;

			
			m_moveSpeed -= m_moveSpeed * m_friction;
			
			ApplyGravity();
			
			m_enemy->SetPosition(m_charaCon.Execute(m_moveSpeed,g_gameTime->GetFrameDeltaTime()));

			Vector3 toMovePos = pos - oldPos;

			if (toMovePos.Length() < 1.0f) {
				//RouteSearch();
			}
		}

		void RouteMove::StopExecution()
		{
			m_moveSpeed -= m_moveSpeed * m_friction;

			ApplyGravity();

			m_enemy->SetPosition(m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime()));
		}

		void RouteMove::ApplyGravity()
		{
			m_moveSpeed.y -= GRAVITY;
		}
	}
}