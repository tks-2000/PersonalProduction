#include "stdafx.h"
#include "EnemySpawnPoint.h"

namespace mainGame {
	namespace enemy {

		const float START_SPAWN_INTERVAL = 10.0f;

		SpawnPoint::SpawnPoint()
		{

		}

		SpawnPoint::~SpawnPoint()
		{

		}

		void SpawnPoint::Init(Generator* generator, const Vector3& pos)
		{
			m_enemyGenerator = generator;
			m_position = pos;
			m_model = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_model->InitDeferrd("Assets/modelData/box/box2.tkm");
			m_model->SetPosition(m_position);
			m_spawnIntreval = START_SPAWN_INTERVAL;

			m_isInitd = true;
		}

		void SpawnPoint::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			m_spawnTimer += g_gameTime->GetFrameDeltaTime();

			if (m_spawnTimer > m_spawnIntreval) {
				m_spawnTimer = 0.0f;
			}

			m_model->Execution();
		}

		void SpawnPoint::SpawnEnemy()
		{
			m_enemyGenerator->CreateEnemy(m_position);
		}
	}
}