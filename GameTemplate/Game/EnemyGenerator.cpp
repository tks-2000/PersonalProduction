#include "stdafx.h"
#include "EnemyGenerator.h"
#include <random>

namespace mainGame {
	namespace enemy {

		const Vector3 SPAWN_POS[SPAWN_POS_NUM]{
			{100.0f,0.0f,100.0f},
			{100.0f,0.0f,-100.0f},
			{-100.0f,0.0f,100.0f},
			{-100.0f,0.0f,-100.0f}
		};

		const EnEnemyType SPAWN_ENEMY_TYPE[enEnemyTypeNum] = {
			enEnemyTypeNormal,
			enEnemyTypePowerful,
			enEnemyTypeFast
		};

		Generator::Generator()
		{
			
		}

		Generator::~Generator()
		{

		}

		void Generator::Init(const Vector3& pos)
		{
			if (m_isInitd == true) {
				return;
			}
			m_position = pos;
			for (int posNum = 0; posNum < SPAWN_POS_NUM; posNum++) {
				m_toGeneratorPos[posNum] = m_position + SPAWN_POS[posNum];
			}
			m_isInitd = true;
		}

		void Generator::Execute()
		{
			if (m_isInitd == false) {
				return;
			}

			if (g_pad[0]->IsTrigger(enButtonB)) {
				CreateEnemy();
			}

			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				m_enemys[enemyNum]->Execution();
			}
		}

		void Generator::DeleteEnemy(Enemy* enemy, const int num)
		{
			std::vector<Enemy*>::iterator it;
			it = std::find(
				m_enemys.begin(),
				m_enemys.end(),
				enemy
			);
			if (it != m_enemys.end()) {
				m_enemys.erase(it);
				m_isSpawn[num] = false;
				m_enemySum--;
			}
		}

		void Generator::CreateEnemy()
		{
			if (m_enemySum == MAX_ENEMY_NUM) {
				return;
			}
			for (int enemyNum = 0; enemyNum < MAX_ENEMY_NUM; enemyNum++) {
				if (m_isSpawn[enemyNum] == false) {
					m_enemys.push_back(NewGO<Enemy>(PRIORITY_VERYLOW, ENEMY_NAMES[enemyNum]));
					std::random_device rnd;
					int num = rnd();
					int num2 = rnd();
					if (num < 0) {
						num *= -1;
					}
					if (num2 < 0) {
						num2 *= -1;
					}
					num %= 3;
					num2 %= 4;
					m_enemys[m_enemySum]->Init(enemyNum, SPAWN_ENEMY_TYPE[num], m_toGeneratorPos[num2]);
					m_enemySum++;
					m_isSpawn[enemyNum] = true;
					break;
				}
			}
		}
	}
}