#include "stdafx.h"
#include "Enemy.h"

namespace {
	const char* ENEMY_MODEL_TKM_FILEPATH = "Assets/modelData/unityChan/utc_red.tkm";

	
}

namespace mainGame {
	namespace enemy {
		Enemy::Enemy()
		{

		}

		Enemy::~Enemy()
		{

		}

		void Enemy::Init()
		{
			m_enemyModel = NewGO<render::model::SkinModelRender>(PRIORITY_VERYLOW);
			m_enemyModel->Init(ENEMY_MODEL_TKM_FILEPATH);
			m_position = { 0.0f,500.0f,1000.0f };

			m_enemyMove.Init(m_position);
			m_enemyAttack.Init();

			m_state = enEnemyIdle;
			m_isInitd = true;
		}

		void Enemy::Execution()
		{
			if (m_isInitd == false) {
				return;
			}

			switch (m_state)
			{
			case enEnemyIdle: {
				m_position = m_enemyMove.IdleExecute(m_position);
			}break;
			case enEnemyMove: {
				m_position = m_enemyMove.MoveExecute(m_position);
			}break;
			case enEnemyAttack: {
				m_enemyAttack.Execution();
			}break;
			case enEnemyStop: {

			}break;
			default:
				break;
			}

			m_enemyModel->Execution();
			
			m_enemyModel->SetPosition(m_position);
		}
	}
}