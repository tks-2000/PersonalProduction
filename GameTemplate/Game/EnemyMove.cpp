#include "stdafx.h"
#include "EnemyMove.h"

namespace {
	const float MOVE_VEROCITY = 5.0f;

	const float MOVE_STOP_DISTANCE = 200.0f;

	const float MOVE_START_TIME = 3.0f;

	/// @brief ñÄéCóÕ
	const float FRICTION = 0.03f;

	const float ENEMY_GRAVITY = 30.0f;

	/// @brief ìGÇÃè’ìÀîªíËÇÃîºåa
	const float ENEMY_COLLISION_RADIUS = 50.0f;
	/// @brief ìGÇÃè’ìÀîªíËÇÃçÇÇ≥
	const float ENEMY_COLLISION_HEIGHT = 100.0f;
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
			m_charaCon.Init(ENEMY_COLLISION_RADIUS, ENEMY_COLLISION_HEIGHT, m_position);

			m_isInitd = true;
		}

		const Vector3& Move::MoveExecute(Vector3& pos)
		{
			if (m_isInitd == false) {
				return pos;
			}

			m_moveDirection = m_toTarget = m_moveTarget - pos;

			m_targetDistance = m_toTarget.Length();

			m_moveDirection.y = 0.0f;

			m_moveDirection.Normalize();

			if (m_moveDirection.Length() == 0.0f ||
				m_targetDistance <= MOVE_STOP_DISTANCE) {
				m_enemy->SetState(enEnemyAttack);
				return pos;
			}

			m_moveSpeed += m_moveDirection * MOVE_VEROCITY;

			m_moveSpeed -= m_moveSpeed * FRICTION;

			m_moveSpeed.y -= ENEMY_GRAVITY;

			//pos += m_moveSpeed;

			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			return pos;
		}

		const Vector3& Move::IdleExecute(Vector3& pos)
		{
			if (m_isInitd == false) {
				return pos;
			}

			m_moveSpeed -= m_moveSpeed * FRICTION;

			m_moveSpeed.y -= ENEMY_GRAVITY;

			pos = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

			m_moveStartTimer += g_gameTime->GetFrameDeltaTime();

			if (m_moveStartTimer >= MOVE_START_TIME) {

				m_moveStartTimer = 0.0f;

				m_enemy->SetState(enEnemyMove);
			}

			return pos;
		}

		void Move::MoveStop()
		{
			m_moveSpeed = g_vec3Zero;
			m_moveDirection = g_vec3Zero;
			m_moveTarget = m_position;
		}
	}
}