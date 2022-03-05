#pragma once

namespace mainGame {
	namespace enemy {

		class SpawnPoint
		{
		public:
			SpawnPoint();
			~SpawnPoint();
			void Init(Generator* generator,const Vector3& pos);
			void Execution();
			void SpawnEnemy();
		private:
			


			bool m_isInitd = false;

			bool m_isActive = true;

			float m_reActiveTimer = 0.0f;

			Vector3 m_position = g_vec3Zero;

			float m_spawnIntreval = 0.0f;

			float m_spawnTimer = 0.0f;

			Generator* m_enemyGenerator = nullptr;

			render::model::SkinModelRender* m_model = nullptr;
		};
	}
}
