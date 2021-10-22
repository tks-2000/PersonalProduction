#pragma once

class SkinModelRender;

namespace mainGame {
	namespace player {

		class Attack;

		/// @brief プレイヤーの弾丸を制御するクラス
		class Bullet : public IGameObject
		{
		public:
			Bullet();
			~Bullet();
			void Init(Attack* plAttack, std::vector<enemy::Enemy*>* enemys,const Vector3& pos,const Vector3& target);
			void Execution();
		private:

			void MoveExecution();

			void EnemyCollision();

			void DeleteThis();

			bool m_isInitd = false;

			Vector3 m_startPos = g_vec3Zero;

			Vector3 m_position = g_vec3Zero;

			Vector3 m_target = g_vec3Zero;

			Vector3 m_moveDirection = g_vec3Zero;

			Vector3 m_moveSpeed = g_vec3Zero;

			render::model::SkinModelRender* m_bulletModel = nullptr;

			std::vector<enemy::Enemy*>* m_enemys = nullptr;

			Attack* m_playerAttack = nullptr;
		};
	}
}
