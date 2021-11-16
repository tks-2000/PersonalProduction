#pragma once

namespace nsAI {
	class NaviMesh;
	class Path;
	class PathFinding;
}

namespace mainGame {

	namespace defensiveTarget {
		class DefensiveTarget;
	}

	namespace enemy {

		class Enemy;

		/// @brief �G�̌o�H�ړ����s���N���X
		class RouteMove
		{
		public:
			RouteMove();
			~RouteMove();

			void Init(Enemy* enemy);
			

			void RouteSearch();

			const Vector3& IdleExecution(Vector3& pos);

			const Vector3& MoveExecution(Vector3& pos);

			const Vector3& StopExecution(Vector3& pos);

			const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

		private:
			bool m_isInitd = false;
			/// @brief �ړ����x
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief ���x
			float m_moveVerocity = 0.0f;
			/// @brief �ړ��ڕW
			Vector3 m_moveTarget = g_vec3Zero;
			/// @brief �ړ��ڕW�ւ̃x�N�g��
			Vector3 m_toTarget = g_vec3Zero;
			/// @brief �ړ�����
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief �ړ��ڕW�Ƃ̋���
			float m_targetDistance = 0.0f;
			/// @brief �ړ��J�n����܂ł̎���
			float m_moveStartTimer = 0.0f;
			/// @brief �L�����N�^�[�R���g���[���[
			CharacterController m_charaCon;
			/// @brief �G�N���X
			Enemy* m_enemy = nullptr;

			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
			

			nsAI::NaviMesh m_naviMesh;
			nsAI::Path m_path;
			nsAI::PathFinding m_pathFinding;
		};
	}
}
