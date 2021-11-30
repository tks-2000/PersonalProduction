#include "stdafx.h"
#include "EnemyGenerator.h"
#include <random>

namespace mainGame {
	namespace enemy {
		/// @brief 生成器から出現する座標までの距離
		const Vector3 TO_GENERATOR_POS[SPAWN_POS_NUM]{
			{1200.0f,0.0f,1200.0f},
			{1200.0f,0.0f,-1200.0f},
			{-1200.0f,0.0f,1200.0f},
			{-1200.0f,0.0f,-1200.0f},
			{0.0f,0.0f,1200.0f},
			{0.0f,0.0f,-1200.0f},
			{1200.0f,0.0f,0.0f},
			{-1200.0f,0.0f,0.0f}
		};

		/// @brief 出現する敵の種類
		const EnEnemyType SPAWN_ENEMY_TYPE[enEnemyTypeNum] = {
			enEnemyTypeNormal,
			enEnemyTypePowerful,
			enEnemyTypeFast
		};

		const float MAX_SPAWN_INTERVAL = 5.0f;

		const float MIN_SPAWN_INTERVAL = 1.0f;

		Generator::Generator()
		{
			
		}

		Generator::~Generator()
		{
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				m_enemys[enemyNum]->DeleteEnemy();
			}

			m_enemys.clear();
			
		}

		void Generator::Init(const Vector3& pos)
		{
			//初期化済みなら実行しない
			if (m_isInitd == true) {
				return;
			}

			//座標を設定
			m_position = pos;

			m_enemySum = 0;

			//敵生成器の中心座標から敵の出現位置を決める
			for (int posNum = 0; posNum < SPAWN_POS_NUM; posNum++) {
				m_spawnPos[posNum] = m_position + TO_GENERATOR_POS[posNum];
			}

			//初期配置
			/*CreateEnemy(enEnemyTypeNormal, m_spawnPos[0]);
			CreateEnemy(enEnemyTypePowerful, m_spawnPos[1]);
			CreateEnemy(enEnemyTypeNormal, m_spawnPos[3]);
			CreateEnemy(enEnemyTypeFast, m_spawnPos[2]);*/

			m_spawnInterval = MAX_SPAWN_INTERVAL;

			m_game = FindGO<Game>(GAME_NAME);

			//初期化完了
			m_isInitd = true;
		}

		void Generator::Execute()
		{
			//未初期化なら実行しない
			if (m_isInitd == false) {
				return;
			}

			if (m_game->GetGameState() != enGameInProgress) {
				for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
					m_enemys[enemyNum]->Execution();
				}
				return;
			}

			m_spawnTimer += g_gameTime->GetFrameDeltaTime();

			if (m_spawnTimer > m_spawnInterval) {
				std::random_device rnd;
				int num = rnd();
				int num2 = rnd();
				if (num < 0) {
					num *= -1;
					
				}
				if (num2 < 0) {
					num2 *= -1;
				}
				
				num %= enEnemyTypeNum;
				num2 %= SPAWN_POS_NUM;

				CreateEnemy(SPAWN_ENEMY_TYPE[num],m_spawnPos[num2]);

				m_spawnTimer = 0.0f;
			}


			if (m_spawnInterval < MIN_SPAWN_INTERVAL) {

				m_spawnInterval = MIN_SPAWN_INTERVAL;
			}
			else {
				m_spawnInterval -= g_gameTime->GetFrameDeltaTime() / 20.0f;
			}

			//出現している敵の数だけ実行する
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				m_enemys[enemyNum]->Execution();
			}
		}

		void Generator::DeleteEnemy(Enemy* enemy)
		{
			//イテレータを使って配列から探し出す
			std::vector<Enemy*>::iterator it;
			it = std::find(
				m_enemys.begin(),
				m_enemys.end(),
				enemy
			);

			//見つかったら…
			if (it != m_enemys.end()) {
				//出現フラグを消す
				m_isSpawn[enemy->GetNumber()] = false;
				//配列から削除
				m_enemys.erase(it);
				//敵の合計数を減らす
				m_enemySum--;
			}
		}

		void Generator::CreateEnemy(const EnEnemyType& type, const Vector3& pos)
		{
			//既に最大数まで出現している場合・引数が不正な値の場合は実行しない
			if (
				m_enemySum == MAX_ENEMY_NUM ||
				type >= enEnemyTypeNum
				) {
				return;
			}


			//敵を生成
			m_enemys.push_back(NewGO<Enemy>(PRIORITY_VERYLOW));

			//ランダムな数値から敵のパラメーターを決定
			std::random_device rnd;
			int num = rnd();
			int num2 = rnd();
			if (num < 0) {
				num *= -1;
			}
			if (num2 < 0) {
				num2 *= -1;
			}
			num %= enEnemyTypeNum;
			num2 %= SPAWN_POS_NUM;

			//敵の初期化情報を作成
			EnemyInitData enemyInitData;
			enemyInitData.enemyType = type;
			enemyInitData.enemyStartPos = pos;

			//初期化情報で敵を初期化
			m_enemys[m_enemySum]->Init(enemyInitData);

			//敵の最大数に加算
			m_enemySum++;

		}
	}
}