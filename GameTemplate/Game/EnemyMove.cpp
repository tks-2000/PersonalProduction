#include "stdafx.h"
#include "EnemyMove.h"

namespace {
	const float MOVE_VEROCITY = 1.0f;

	const float MOVE_STOP_DISTANCE = 200.0f;

	const float MOVE_START_TIME = 3.0f;
}
namespace mainGame {
	namespace enemy {
		Move::Move()
		{

		}

		Move::~Move()
		{

		}

		void Move::Init(const Vector3& pos)
		{
			m_enemy = FindGO<Enemy>(ENEMY_NAME);
			m_position = pos;

			m_isInitd = true;
		}

		Vector3 Move::MoveExecute(Vector3& pos)
		{
			if (m_isInitd == false) {
				return pos;
			}

			m_moveDirection = m_toTarget = m_moveTarget - pos;

			m_targetDistance = m_toTarget.Length();

			m_moveDirection.Normalize();

			if (m_moveDirection.Length() == 0.0f ||
				m_targetDistance <= MOVE_STOP_DISTANCE) {
				m_enemy->SetState(enEnemyAttack);
				return pos;
			}

			m_moveSpeed = m_moveDirection * MOVE_VEROCITY;

			pos += m_moveSpeed;

			return pos;
		}

		void Move::IdleExecute()
		{
			if (m_isInitd == false) {
				return;
			}

			m_moveStartTimer += g_gameTime->GetFrameDeltaTime();

			if (m_moveStartTimer >= MOVE_START_TIME) {

				m_moveStartTimer = 0.0f;

				m_enemy->SetState(enEnemyMove);
			}
		}

		void Move::MoveStop()
		{
			m_moveSpeed = g_vec3Zero;
			m_moveDirection = g_vec3Zero;
			m_moveTarget = m_position;
		}

		void Move::MoveExecute()
		{
			
		}
	}
}