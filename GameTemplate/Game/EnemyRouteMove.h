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

		/// @brief 敵の経路移動を行うクラス
		class RouteMove
		{
		public:
			RouteMove();
			~RouteMove();

			void Init(Enemy* enemy);
			
			/// @brief ルート検索
			void RouteSearch();
			/// @brief 実行
			void Execution();
			/// @brief 待機
			void IdleExecution();
			/// @brief 移動
			/// @param moveVerocity 
			void MoveExecution(const float moveVerocity);

			void StopExecution();

			const Vector3& GetMoveSpeed() const { return m_moveSpeed; }

			void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

			

		private:

			void ApplyGravity();

			bool m_isInitd = false;
			/// @brief 移動速度
			Vector3 m_moveSpeed = g_vec3Zero;
			/// @brief 速度
			float m_moveVerocity = 0.0f;
			/// @brief 摩擦力
			float m_friction = 0.0f;
			/// @brief 移動目標
			Vector3 m_moveTarget = g_vec3Zero;
			/// @brief 移動目標へのベクトル
			Vector3 m_toTarget = g_vec3Zero;
			/// @brief 移動方向
			Vector3 m_moveDirection = g_vec3Zero;
			/// @brief 移動目標との距離
			float m_targetDistance = 0.0f;
			/// @brief 移動開始するまでの時間
			float m_moveStartTimer = 0.0f;
			/// @brief キャラクターコントローラー
			CharacterController m_charaCon;
			/// @brief 敵クラス
			Enemy* m_enemy = nullptr;

			/// @brief 防衛目標
			defensiveTarget::DefensiveTarget* m_defensiveTarget = nullptr;
			
			/// @brief ナビメッシュ
			nsAI::NaviMesh m_naviMesh;
			/// @brief パス
			nsAI::Path m_path;
			/// @brief パス検索
			nsAI::PathFinding m_pathFinding;
		};
	}
}
