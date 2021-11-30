#include "stdafx.h"
#include "EnemyGenerator.h"
#include <random>

namespace mainGame {
	namespace enemy {
		/// @brief �����킩��o��������W�܂ł̋���
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

		/// @brief �o������G�̎��
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
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//���W��ݒ�
			m_position = pos;

			m_enemySum = 0;

			//�G������̒��S���W����G�̏o���ʒu�����߂�
			for (int posNum = 0; posNum < SPAWN_POS_NUM; posNum++) {
				m_spawnPos[posNum] = m_position + TO_GENERATOR_POS[posNum];
			}

			//�����z�u
			/*CreateEnemy(enEnemyTypeNormal, m_spawnPos[0]);
			CreateEnemy(enEnemyTypePowerful, m_spawnPos[1]);
			CreateEnemy(enEnemyTypeNormal, m_spawnPos[3]);
			CreateEnemy(enEnemyTypeFast, m_spawnPos[2]);*/

			m_spawnInterval = MAX_SPAWN_INTERVAL;

			m_game = FindGO<Game>(GAME_NAME);

			//����������
			m_isInitd = true;
		}

		void Generator::Execute()
		{
			//���������Ȃ���s���Ȃ�
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

			//�o�����Ă���G�̐��������s����
			for (int enemyNum = 0; enemyNum < m_enemys.size(); enemyNum++) {
				m_enemys[enemyNum]->Execution();
			}
		}

		void Generator::DeleteEnemy(Enemy* enemy)
		{
			//�C�e���[�^���g���Ĕz�񂩂�T���o��
			std::vector<Enemy*>::iterator it;
			it = std::find(
				m_enemys.begin(),
				m_enemys.end(),
				enemy
			);

			//����������c
			if (it != m_enemys.end()) {
				//�o���t���O������
				m_isSpawn[enemy->GetNumber()] = false;
				//�z�񂩂�폜
				m_enemys.erase(it);
				//�G�̍��v�������炷
				m_enemySum--;
			}
		}

		void Generator::CreateEnemy(const EnEnemyType& type, const Vector3& pos)
		{
			//���ɍő吔�܂ŏo�����Ă���ꍇ�E�������s���Ȓl�̏ꍇ�͎��s���Ȃ�
			if (
				m_enemySum == MAX_ENEMY_NUM ||
				type >= enEnemyTypeNum
				) {
				return;
			}


			//�G�𐶐�
			m_enemys.push_back(NewGO<Enemy>(PRIORITY_VERYLOW));

			//�����_���Ȑ��l����G�̃p�����[�^�[������
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

			//�G�̏����������쐬
			EnemyInitData enemyInitData;
			enemyInitData.enemyType = type;
			enemyInitData.enemyStartPos = pos;

			//���������œG��������
			m_enemys[m_enemySum]->Init(enemyInitData);

			//�G�̍ő吔�ɉ��Z
			m_enemySum++;

		}
	}
}