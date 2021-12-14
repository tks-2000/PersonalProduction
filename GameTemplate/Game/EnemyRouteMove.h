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
			
			/// @brief ���[�g����
			void RouteSearch();
			/// @brief ���s
			void Execution();
			/// @brief �ҋ@
			void IdleExecution();
			/// @brief �ړ�
			/// @param moveVerocity 
			void MoveExecution(const float moveVerocity);

			void StopExecution();

			const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

			

		private:

			void ApplyGravity();

			bool m_isInitd = false;
			/// @brief �ړ����x
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief ���x
			float m_moveVerocity = 0.0f;
			/// @brief ���C��
			float m_friction = 0.0f;
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

			/// @brief �h�q�ڕW
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
			
			/// @brief �i�r���b�V��
			nsAI::NaviMesh m_naviMesh;
			/// @brief �p�X
			nsAI::Path m_path;
			/// @brief �p�X����
			nsAI::PathFinding m_pathFinding;
		};
	}
}
