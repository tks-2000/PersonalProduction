#include "stdafx.h"
#include "EnemyGenerator.h"
#include <random>

namespace mainGame {
	namespace enemy {
		/// @brief �����킩��o��������W�܂ł̋���
		const Vector3 TO_GENERATOR_POS[SPAWN_POS_NUM]{
			{100.0f,0.0f,100.0f},
			{100.0f,0.0f,-100.0f},
			{-100.0f,0.0f,100.0f},
			{-100.0f,0.0f,-100.0f}
		};

		/// @brief �o������G�̎��
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
			//�������ς݂Ȃ���s���Ȃ�
			if (m_isInitd == true) {
				return;
			}

			//���W��ݒ�
			m_position = pos;

			//�G������̒��S���W����G�̏o���ʒu�����߂�
			for (int posNum = 0; posNum < SPAWN_POS_NUM; posNum++) {
				m_spawnPos[posNum] = m_position + TO_GENERATOR_POS[posNum];
			}

			//����������
			m_isInitd = true;
		}

		void Generator::Execute()
		{
			//���������Ȃ���s���Ȃ�
			if (m_isInitd == false) {
				return;
			}

			if (g_pad[0]->IsTrigger(enButtonB)) {
				CreateEnemy();
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

		void Generator::CreateEnemy()
		{
			//���ɍő吔�܂ŏo�����Ă���ꍇ���s���Ȃ�
			if (m_enemySum == MAX_ENEMY_NUM) {
				return;
			}

			//�o���\�ő吔�������s����
			for (int enemyNum = 0; enemyNum < MAX_ENEMY_NUM; enemyNum++) {
				//�o���t���O�������Ă��Ȃ��ꍇ�c
				if (m_isSpawn[enemyNum] == false) {
					//�G�𐶐�
					m_enemys.push_back(NewGO<Enemy>(PRIORITY_VERYLOW, ENEMY_NAMES[enemyNum]));

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
					enemyInitData.enemyNum = enemyNum;
					enemyInitData.enemyType = SPAWN_ENEMY_TYPE[num];
					enemyInitData.enemyStartPos = m_spawnPos[num2];

					//���������œG��������
					m_enemys[m_enemySum]->Init(enemyInitData);
					
					//�G�̍ő吔�ɉ��Z
					m_enemySum++;

					//�o���t���O�𗧂Ă�
					m_isSpawn[enemyNum] = true;

					//�J��Ԃ����甲����
					break;
				}
			}
		}
	}
}