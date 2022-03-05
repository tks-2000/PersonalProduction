#pragma once
#include"EnemyResource.h"
#include "EnemySpawnPoint.h"

namespace mainGame {
	namespace enemy {

		

		/// @brief �G���Ăяo���N���X
		class Generator : public IGameObject
		{
		public:
			Generator();
			~Generator();

			/// @brief ������
			/// @param pos �G������̒��S���W
			void Init(const Vector3& pos);

			/// @brief ���s
			void Execute();

			/// @brief �G���o��������
			bool CreateEnemy(const Vector3& pos);

			/// @brief �o�����Ă���G���폜
			/// @param enemy �폜����G�̃A�h���X
			void DeleteEnemy(Enemy* enemy);

			void DeleteAllEnemy();

			/// @brief �S�Ă̓G�̏������
			/// @return �G�̔z��̃A�h���X
			std::vector<Enemy*>* GetEnemys(){ return &m_enemys; }

		private:

			

			/// @brief �������t���O
			bool m_isInitd = false;

			/// @brief �o�����Ă���G�̍��v��
			int m_enemySum = 0;
			/// @brief �G������̍��W
			Vector3 m_position = g_vec3Zero;

			/// @brief �o������G�̔z��
			std::vector<Enemy*> m_enemys;

			/// @brief �����킩��o��������W
			Vector3 m_spawnPos[SPAWN_POS_NUM] = {
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero,
				g_vec3Zero
			};

			GameScene* m_gameScene = nullptr;

			/// @brief �o���Ԋu
			float m_spawnInterval = 0.0f;

			/// @brief �o���Ԋu�𑪂�^�C�}�[
			float m_spawnTimer = 0.0f;

			SpawnPoint m_spawnPoint[SPAWN_POS_NUM];

			bool m_isSpawn = false;
		};
	}
}
