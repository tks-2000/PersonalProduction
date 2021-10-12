#pragma once
namespace mainGame{
	namespace enemy {

		class Enemy;

		/// @brief ìGÇÃà⁄ìÆÇêßå‰Ç∑ÇÈÉNÉâÉX
		class Move
		{
		public:
			Move();
			~Move();

			void Init(const Vector3& pos = g_vec3Zero);

			Vector3 MoveExecute(Vector3& pos);

			void IdleExecute();

			void SetMoveTarget(const Vector3& target) { m_moveTarget = target; }

			void SetPosition(const Vector3& pos) { m_position = pos; }

			void MoveStop();

		private:

			void MoveExecute();

			bool m_isInitd = false;

			Vector3 m_position = g_vec3Zero;

			Vector3 m_moveSpeed = g_vec3Zero;

			Vector3 m_moveTarget = g_vec3Zero;

			Vector3 m_toTarget = g_vec3Zero;

			Vector3 m_moveDirection = g_vec3Zero;

			float m_targetDistance = 0.0f;

			float m_moveStartTimer = 0.0f;

			Enemy* m_enemy = nullptr;
		};
	}
}
